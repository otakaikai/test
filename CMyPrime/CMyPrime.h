#include <vector>
#include <map>
#include <set>

namespace Prime
{
	struct SNode
	{
		SNode( int param = 0 )
		{
			index = param;
		}
		int index;
	};

	struct SSide
	{
		SNode* nodeFrom;
		SNode* nodeTo;
		int value;

		//bool operator < ( const SSide& a ) const
		//{
		//	// <:´ó¶¥¶Ñ   >:Ð¡¶¥¶Ñ 
		//	return value > a.value;
		//}
	};

	class COp
	{
	public:
		bool operator () ( const SSide& a, const SSide& b ) const
		{
			// <:´ó¶¥¶Ñ   >:Ð¡¶¥¶Ñ 
			return a.value > b.value;
		}
	};

	typedef std::vector< SSide > VecSides; 
	typedef std::map< SNode*, VecSides > MapNodeSides;
	typedef std::set< SSide, COp > SetSide;

	SNode* createNode( const int index );

	bool createSide( const int fromIndex, const int toIndex, const int value, SSide& side );
	bool createSide( const int fromIndex, const int toIndex, const int value, VecSides& vecSides );

	bool createSide( SNode* nodeFrom, SNode* nodeTo, const int value, VecSides& vecSides );

	void makeConnection( MapNodeSides& mapNodeSides, const SSide& side );
	void makeConnection( MapNodeSides& mapNodeSides, const VecSides& vecSide );
}



