#include "Common.h"

using namespace Common;

class CMapCreateHelper
{
public:
	static void createMap( MapNode& mapNode, const int xSize, const int ySize, bool isAutoBeginEndPoint = true );

	static void showMap( const MapNode& mapNode );

	static bool getMapTypePoint( const MapNode& mapNode, const int pointType, SPoint* point );
private:
	static bool isNeighbourNode( const SNode& nodeLeft, const SNode& nodeRight );

	static bool getNeighbourNodes( const SNode& targetNode, std::vector<SNode>& neighbourNodes );

	static bool getLegalNeighbourNodes( const SNode& targetNode, const MapNode& mapNodes, std::vector<SNode>& neighbourNodes );

	static void dealMapWays( std::stack<SNode>& stackNode, MapNode& mapNodes );

	static bool isMapWayComplete( const MapNode& mapNodes, const std::stack<SNode>& stackBegin, const std::stack<SNode>& stackEnd );
};
