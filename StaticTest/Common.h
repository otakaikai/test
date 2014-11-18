#ifndef MY_TEST_COMMON_H_H_H
#define MY_TEST_COMMON_H_H_H

#include <vector>
#include <queue>
#include <map>
#include <stack>

namespace Common
{
	#define X_SIZE 1
	#define Y_SIZE 1

	typedef std::vector< std::vector< int > >  MapNode;

	enum EPoint
	{
		EPointForbid = 0,		//���ε�
		EPointPass = 1,			//��ͨ��
		EPointBegin = 2,		//���
		EPointEnd = 3,			//�յ�
		EPointHadCheck = 100,	//�Ѽ����ĵ�
		EPointHadCheckEx = 101	//�Ѽ����ĵ�
	};

	enum EPointPosType
	{
		EPointPosOpen = 1,
		EPointPosClose = 2
	};

	struct SNode
	{
		SNode( int x=0, int y=0 )
		{
			_x = x;
			_y = y;
		}

		bool operator == ( const SNode& b )
		{
			return ( _x == b._x && _y == b._y );
		}

		void operator = ( const SNode& b )
		{
			_x = b._x;
			_y = b._y;
		}

		int _x;
		int _y;
	};

	struct SPoint
	{
	public:
		SPoint( int x=0, int y=0, double g=0.0, int h=0, SPoint* fromPoint = NULL )
		{
			_x = x;
			_y = y;
			_g = g;
			_h = h;
			_fromPoint = fromPoint;
		}
	public:
		int _x;
		int _y;
		double _g;			//��㵽N���ʵ�ʾ���
		int _h;				//N�㵽�յ�Ĺ��ƾ���
		SPoint* _fromPoint;

		//bool operator () ( const SPoint* a, const SPoint* b )
		//{
		//	// <:�󶥶�   >:С���� 
		//	return a->_g + a->_h > b->_g + b->_h;
		//}
	};

	class COp
	{
	public:
		bool operator () ( const SPoint* a, const SPoint* b )
		{
			// <:�󶥶�   >:С���� 
			return a->_g + a->_h > b->_g + b->_h;
		}
	};

	typedef std::priority_queue< SPoint*, std::vector<SPoint*>, COp > PrioritySeqPonit;	//�Ż���map���Щ(open�б�)
	//typedef std::priority_queue< SPoint* > PrioritySeqPonit;
	typedef std::vector< SPoint* > SeqPoint;	//close�б�

	int randNumbers( int lower=0, int upper=0 );
}


#endif