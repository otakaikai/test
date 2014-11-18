#include "CMyPrime.h"
#include "assert.h"
using namespace Prime;

bool Prime::createSide( const int fromIndex, const int toIndex, const int value, SSide& side )
{
	SNode* nodeFrom = createNode( fromIndex );
	SNode* nodeTo = createNode( toIndex );
	if( !nodeTo || !nodeFrom )
	{
		assert( nodeFrom && nodeTo );
		return false;
	}	

	side.nodeFrom = nodeFrom;
	side.nodeTo = nodeTo;
	side.value = value;
	return true;
}

bool Prime::createSide( const int fromIndex, const int toIndex, const int value, VecSides& vecSides )
{
	SSide side;
	if( Prime::createSide( fromIndex, toIndex, value, side ) )
	{
		vecSides.push_back( side );
		return true;
	}

	return false;
}

bool Prime::createSide( SNode* nodeFrom, SNode* nodeTo, const int value, VecSides& vecSides )
{
	SSide side;
	side.nodeFrom = nodeFrom;
	side.nodeTo = nodeTo;
	side.value = value;
	vecSides.push_back( side );

	return true;
}

void Prime::makeConnection( MapNodeSides& mapNodeSides, const SSide& side )
{
	mapNodeSides[ side.nodeFrom ].push_back( side );
	mapNodeSides[ side.nodeTo ].push_back( side );
}

void Prime::makeConnection( MapNodeSides& mapNodeSides, const VecSides& vecSide )
{
	for( VecSides::const_iterator it = vecSide.begin(); it != vecSide.end(); ++it )
	{
		Prime::makeConnection( mapNodeSides, *it );
	}
}

SNode* Prime::createNode( const int index )
{
	SNode* node = new SNode( index );
	return node;
}