#include "CMyPrime.h"
#include <queue>
#include <iostream>
using namespace Prime;

//prime 最小生成树 最短连通图
int main()
{
	MapNodeSides mapNodeSides;
	VecSides vecSides;

	//创建点
	SNode* node1 = createNode( 1 );
	SNode* node2 = createNode( 2 );
	SNode* node3 = createNode( 3 );
	SNode* node4 = createNode( 4 );
	SNode* node5 = createNode( 5 );
	SNode* node6 = createNode( 6 );

	//创建边
	createSide( node1, node2, 6, vecSides );
	createSide( node1, node3, 1, vecSides );
	createSide( node1, node4, 5, vecSides );
	createSide( node2, node3, 5, vecSides );
	createSide( node2, node5, 3, vecSides );
	createSide( node3, node4, 5, vecSides );
	createSide( node3, node5, 6, vecSides );
	createSide( node3, node6, 4, vecSides );
	createSide( node4, node6, 2, vecSides );
	createSide( node5, node6, 6, vecSides );

	//把边连成图
	makeConnection( mapNodeSides, vecSides );

	SetSide setNearestSides;	//最短边集合
	std::set<int> exceptNodes;	//已搜寻过的点
	std::priority_queue< SSide, std::vector<SSide>, COp > seq;	//优先队列，筛选出最短路径

	SNode* targetNode = NULL;
	if( !mapNodeSides.empty() )
	{
		//找到初始点
		MapNodeSides::iterator it = mapNodeSides.begin();
		targetNode = it->first;
		exceptNodes.insert( targetNode->index );
	}
	while( true )
	{
		if( !targetNode )
		{
			break;
		}

		if( mapNodeSides.find( targetNode ) == mapNodeSides.end() )
		{
			break;
		}

		if( mapNodeSides.size() == exceptNodes.size() )
		{
			//所有点都找完，退出循环
			break;
		}

		VecSides vecSide = mapNodeSides[ targetNode ];
		for( VecSides::const_iterator it = vecSide.begin(); it != vecSide.end(); ++it )
		{
			//找到目标点指向的所有边（不包括已处理的边）
			if( setNearestSides.end() == setNearestSides.find( *it ) )
			{
				seq.push( *it );
			}
		}
		if( seq.empty() )
		{
			break;
		}

		SSide targetSide;
		targetSide = seq.top();	//找到路径最短的边
		seq.pop();

		//找到下一个目标点
		if( exceptNodes.find( targetSide.nodeFrom->index ) == exceptNodes.end() )
		{
			targetNode = targetSide.nodeFrom;
		}
		else
		{
			targetNode = targetSide.nodeTo;
		}

		setNearestSides.insert( targetSide );
		exceptNodes.insert( targetNode->index );	

	}
	
	//打印路径
	for( SetSide::const_iterator it = setNearestSides.begin(); it != setNearestSides.end(); ++it )
	{
		std::cout<< (*it).nodeFrom->index << "," << (*it).nodeTo->index << std::endl;
	}

	//释放内存
	for( MapNodeSides::iterator it = mapNodeSides.begin(); it != mapNodeSides.end(); ++it )
	{
		if( it->first )
		{
			delete it->first;
		}
	}

	getchar();

	return 0;
};