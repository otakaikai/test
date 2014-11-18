#include "CMapCreate.h"
#include <iostream>
using namespace std;

void CMapCreateHelper::createMap( MapNode& mapNode, const int xSize, const int ySize, bool isAutoBeginEndPoint /* = true */ )
{
	//��ʼ����ͼ��
	for( int x = 0; x < xSize; ++x )
	{
		std::vector<int> vecYNode;
		for( int y = 0; y < ySize; ++y )
		{
			vecYNode.push_back( EPointForbid );
		}
		mapNode.push_back( vecYNode );
	}

	//���������յ�
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

	//�ѳ�ʼ��Ѱ�����ջ��
	std::stack<SNode> stackBegin,stackEnd;
	SNode nodeBegin( beginX, beginY );
	SNode nodeEnd( endX, endY );
	stackBegin.push( nodeBegin );
	stackEnd.push( nodeEnd );

	MapNode tempMapNode = mapNode;	//��ͼ�������Ϣ
	while( true )
	{
		if( stackBegin.empty() || stackEnd.empty() )
		{
			//��ջ
			break;
		}

		if( isMapWayComplete( tempMapNode, stackBegin, stackEnd ) )
		{
			//��ͼ·�ߴ�ͨ���˳�ѭ��
			break;
		}

		//����㿪ʼ������·��
		dealMapWays( stackBegin, tempMapNode );

		//���յ㿪ʼ������·��
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
		//Ѱ·��������
		stackNode.pop();
	}
	else
	{
		//�������
		int randNum = randNumbers( 0, size - 1 );
		SNode nextNode = vecNeighbour[ randNum ];
		stackNode.push( nextNode );

		//��ǵ�ǰ��Ϊ����Ѱ״̬
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
	//������ѡ�㼯
	std::vector<SNode> vecNodes;
	getNeighbourNodes( targetNode, vecNodes );

	const int maxX = mapNodes.size() - 1;
	const int maxY = mapNodes[ 0 ].size() - 1;
	const int stackType = mapNodes[ targetNode._x ][ targetNode._y ];
	for( std::vector<SNode>::const_iterator it = vecNodes.begin(); it != vecNodes.end(); ++it )
	{
		if( it->_x < 0 || it->_y < 0 || it->_x > maxX || it->_y > maxY )
		{
			//�����ֵ�Ϸ����ж�
			continue;
		}

		if( stackType == mapNodes[ it->_x ][ it->_y ] )
		{
			//��Ѱ���ĵ�
			continue;
		}

		//���ڵ��ж�
		std::vector<SNode> nodes;
		getNeighbourNodes( *it, nodes );
		bool isContinue = false;
		for( std::vector<SNode>::const_iterator itNeibour = nodes.begin(); itNeibour != nodes.end(); ++itNeibour )
		{
			if( itNeibour->_x < 0 || itNeibour->_y < 0 || itNeibour->_x > maxX || itNeibour->_y > maxY )
			{
				//�����ֵ�Ϸ����ж�
				continue;
			}
			if( targetNode._x == itNeibour->_x && targetNode._y == itNeibour->_y )
			{
				//Ŀ������ڵ��ǵ�ǰջ����
				continue;
			}
			if( stackType == mapNodes[ itNeibour->_x ][ itNeibour->_y ] )
			{
				//Ŀ�������ڵ�������Ѱ��
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
		//������ջ�Ƿ���ͨ
		if( EPointEnd == mapNodes[ it->_x ][ it->_y ] )
		{
			return true;
		}
	}

	vecNodes.clear();
	getLegalNeighbourNodes( nodeEnd, mapNodes, vecNodes );
	for( std::vector<SNode>::const_iterator it = vecNodes.begin(); it != vecNodes.end(); ++it )
	{
		//����յ�ջ�Ƿ���ͨ
		if( EPointBegin == mapNodes[ it->_x ][ it->_y ] )
		{
			return true;
		}
	}

	return false;
}