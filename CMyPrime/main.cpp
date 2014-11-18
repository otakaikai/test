#include "CMyPrime.h"
#include <queue>
#include <iostream>
using namespace Prime;

//prime ��С������ �����ͨͼ
int main()
{
	MapNodeSides mapNodeSides;
	VecSides vecSides;

	//������
	SNode* node1 = createNode( 1 );
	SNode* node2 = createNode( 2 );
	SNode* node3 = createNode( 3 );
	SNode* node4 = createNode( 4 );
	SNode* node5 = createNode( 5 );
	SNode* node6 = createNode( 6 );

	//������
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

	//�ѱ�����ͼ
	makeConnection( mapNodeSides, vecSides );

	SetSide setNearestSides;	//��̱߼���
	std::set<int> exceptNodes;	//����Ѱ���ĵ�
	std::priority_queue< SSide, std::vector<SSide>, COp > seq;	//���ȶ��У�ɸѡ�����·��

	SNode* targetNode = NULL;
	if( !mapNodeSides.empty() )
	{
		//�ҵ���ʼ��
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
			//���е㶼���꣬�˳�ѭ��
			break;
		}

		VecSides vecSide = mapNodeSides[ targetNode ];
		for( VecSides::const_iterator it = vecSide.begin(); it != vecSide.end(); ++it )
		{
			//�ҵ�Ŀ���ָ������бߣ��������Ѵ���ıߣ�
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
		targetSide = seq.top();	//�ҵ�·����̵ı�
		seq.pop();

		//�ҵ���һ��Ŀ���
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
	
	//��ӡ·��
	for( SetSide::const_iterator it = setNearestSides.begin(); it != setNearestSides.end(); ++it )
	{
		std::cout<< (*it).nodeFrom->index << "," << (*it).nodeTo->index << std::endl;
	}

	//�ͷ��ڴ�
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