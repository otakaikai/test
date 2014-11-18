#include "CMapCreate.h"
#include <iostream>
using namespace std;

void CMapCreateHelper::createMap( MapNode& mapNode, const int xSize, const int ySize, bool isAutoBeginEndPoint /* = true */ )
{
	//初始化地图点
	for( int x = 0; x < xSize; ++x )
	{
		std::vector<int> vecYNode;
		for( int y = 0; y < ySize; ++y )
		{
			vecYNode.push_back( EPointForbid );
		}
		mapNode.push_back( vecYNode );
	}

	//设置起点和终点
	int beginX = 0;
	int beginY = 0;
	int endX = 0;
	int endY = 0;
	if( isAutoBeginEndPoint )
	{
		beginX = 0;
		beginY = 0;
		endX = xSize - 1;
		endY = ySize -1;
	}
	mapNode[ beginX ][ beginY ] = EPointBegin;
	mapNode[ endX ][ endY ] = EPointEnd;

	//把初始搜寻点放入栈中
	std::stack<SNode> stackBegin,stackEnd;
	SNode nodeBegin( beginX, beginY );
	SNode nodeEnd( endX, endY );
	stackBegin.push( nodeBegin );
	stackEnd.push( nodeEnd );

	MapNode tempMapNode = mapNode;	//地图坐标点信息
	while( true )
	{
		if( stackBegin.empty() || stackEnd.empty() )
		{
			//空栈
			break;
		}

		if( isMapWayComplete( tempMapNode, stackBegin, stackEnd ) )
		{
			//地图路线打通，退出循环
			break;
		}

		//从起点开始搜索的路线
		dealMapWays( stackBegin, tempMapNode );

		//从终点开始搜索的路线
		dealMapWays( stackEnd, tempMapNode );
	}

	while( stackBegin.size() )
	{
		SNode node = stackBegin.top();
		mapNode[ node._x ][ node._y ] = EPointPass;
		stackBegin.pop();
	}

	while( stackEnd.size() )
	{
		SNode node = stackEnd.top();
		mapNode[ node._x ][ node._y ] = EPointPass;
		stackEnd.pop();
	}
	mapNode[ beginX ][ beginY ] = EPointBegin;
	mapNode[ endX ][ endY ] = EPointEnd;
}

void CMapCreateHelper::showMap( const MapNode& mapNode )
{
	const int maxX = mapNode.size();
	const int maxY = mapNode[0].size();
	for( int i = 0; i < maxX; ++i )
	{
		for( int j = 0; j < maxY; ++j )
		{
			cout<< mapNode[ i ][ j ] << " ";
		}
		cout << endl;
	}
	cout<<endl;
}

bool CMapCreateHelper::getMapTypePoint( const MapNode& mapNode, const int pointType, SPoint* point )
{
	const int maxX = mapNode.size();
	const int maxY = mapNode[0].size();
	for( int i = 0; i < maxX; ++i )
	{
		for( int j = 0; j < maxY; ++j )
		{
			if( pointType == mapNode[ i ][ j ] )
			{
				point->_x = i;
				point->_y = j;
				return true;
			}
		}
	}

	return false;
}

void CMapCreateHelper::dealMapWays( std::stack<SNode>& stackNode, MapNode& tempMapNode )
{
	if( stackNode.empty() )
	{
		return;
	}

	SNode targetNode = stackNode.top();
	const int stackType = tempMapNode[ targetNode._x ][ targetNode._y ];
	std::vector<SNode> vecNeighbour;
	getLegalNeighbourNodes( targetNode, tempMapNode, vecNeighbour );
	int size = vecNeighbour.size();
	if( 0 == size )
	{
		//寻路到了死角
		stackNode.pop();
	}
	else
	{
		//随机方向
		int randNum = randNumbers( 0, size - 1 );
		SNode nextNode = vecNeighbour[ randNum ];
		stackNode.push( nextNode );

		//标记当前点为已搜寻状态
		tempMapNode[ nextNode._x ][ nextNode._y ] = stackType;
	}
}

bool CMapCreateHelper::isNeighbourNode( const SNode& nodeLeft, const SNode& nodeRight )
{
	if( nodeLeft._x == nodeRight._x && nodeLeft._y == nodeRight._y )
	{
		return true;
	}
	else if( nodeLeft._x == nodeRight._x && ( nodeLeft._y - 1 == nodeRight._y || nodeLeft._y + 1 == nodeRight._y ) )
	{
		return true;
	}
	else if( nodeLeft._y == nodeRight._y  && ( nodeLeft._x - 1 == nodeRight._x || nodeLeft._x + 1 == nodeRight._x ) )
	{
		return true;
	}

	return false;
}

bool CMapCreateHelper::getNeighbourNodes( const SNode& targetNode, std::vector<SNode>& neighbourNodes )
{
	std::multimap<int,int> tempNodes;
	//tempNodes.insert( std::make_pair( targetNode._x, targetNode._y + 1 ) );
	//tempNodes.insert( std::make_pair( targetNode._x, targetNode._y - 1 ) );
	//tempNodes.insert( std::make_pair( targetNode._x + 1, targetNode._y ) );
	//tempNodes.insert( std::make_pair( targetNode._x - 1, targetNode._y ) );
	int arrX[3] = { targetNode._x-1, targetNode._x, targetNode._x+1 };
	int arrY[3] = { targetNode._y-1, targetNode._y, targetNode._y+1 };
	for( int i = 0; i < 3; ++i )
	{
		for( int j = 0; j < 3; ++j )
		{
			tempNodes.insert( std::make_pair( arrX[i], arrY[j] ) );
		}
	}

	for( std::multimap<int,int>::const_iterator it = tempNodes.begin(); it != tempNodes.end(); ++it )
	{
		if( targetNode._x == it->first && targetNode._y == it->second )
		{
			continue;
		}
		SNode node;
		node._x = it->first;
		node._y = it->second;
		neighbourNodes.push_back( node );
	}

	return true;
}

bool CMapCreateHelper::getLegalNeighbourNodes( const SNode& targetNode, const MapNode& mapNodes, std::vector<SNode>& neighbourNodes )
{
	//构建候选点集
	std::vector<SNode> vecNodes;
	getNeighbourNodes( targetNode, vecNodes );

	const int maxX = mapNodes.size() - 1;
	const int maxY = mapNodes[ 0 ].size() - 1;
	const int stackType = mapNodes[ targetNode._x ][ targetNode._y ];
	for( std::vector<SNode>::const_iterator it = vecNodes.begin(); it != vecNodes.end(); ++it )
	{
		if( it->_x < 0 || it->_y < 0 || it->_x > maxX || it->_y > maxY )
		{
			//坐标点值合法性判断
			continue;
		}

		if( stackType == mapNodes[ it->_x ][ it->_y ] )
		{
			//搜寻过的点
			continue;
		}

		//相邻点判断
		std::vector<SNode> nodes;
		getNeighbourNodes( *it, nodes );
		bool isContinue = false;
		for( std::vector<SNode>::const_iterator itNeibour = nodes.begin(); itNeibour != nodes.end(); ++itNeibour )
		{
			if( itNeibour->_x < 0 || itNeibour->_y < 0 || itNeibour->_x > maxX || itNeibour->_y > maxY )
			{
				//坐标点值合法性判断
				continue;
			}
			if( targetNode._x == itNeibour->_x && targetNode._y == itNeibour->_y )
			{
				//目标点相邻点是当前栈顶点
				continue;
			}
			if( stackType == mapNodes[ itNeibour->_x ][ itNeibour->_y ] )
			{
				//目标点的相邻点有已搜寻点
				isContinue = true;
				break;
			}
		}
		if( isContinue )
		{
			continue;
		}

		neighbourNodes.push_back( *it );
	}

	return true;
}

bool CMapCreateHelper::isMapWayComplete( const MapNode& mapNodes, const std::stack<SNode>& stackBegin, const std::stack<SNode>& stackEnd )
{
	SNode nodeBegin = stackBegin.top();
	SNode nodeEnd = stackEnd.top();

	if( isNeighbourNode( nodeBegin, nodeEnd ) )
	{
		return true;
	}

	std::vector<SNode> vecNodes;
	getLegalNeighbourNodes( nodeBegin, mapNodes, vecNodes );
	for( std::vector<SNode>::const_iterator it = vecNodes.begin(); it != vecNodes.end(); ++it )
	{
		//检查起点栈是否连通
		if( EPointEnd == mapNodes[ it->_x ][ it->_y ] )
		{
			return true;
		}
	}

	vecNodes.clear();
	getLegalNeighbourNodes( nodeEnd, mapNodes, vecNodes );
	for( std::vector<SNode>::const_iterator it = vecNodes.begin(); it != vecNodes.end(); ++it )
	{
		//检查终点栈是否连通
		if( EPointBegin == mapNodes[ it->_x ][ it->_y ] )
		{
			return true;
		}
	}

	return false;
}