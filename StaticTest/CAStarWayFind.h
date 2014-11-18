#include "Common.h"

using namespace Common;

class CAStarWayFindHelper
{
public:
	static bool findAndDealNearPoints( const MapNode& mspNode,
								SPoint* paramPoint,
								const SPoint* endPoint,
								std::map<SPoint*,int>& exceptPoint,
								PrioritySeqPonit& openPoints,
								SeqPoint& closePoints );

	static bool isSamePointPos( const SPoint* pointA, const SPoint* pointB );

	static double calPointsMinDistance( const SPoint* fromPoint, const SPoint* toPoint );

	static int calPointsMaxDistance( const SPoint* fromPoint, const SPoint* toPoint );

private:
	static SPoint* findExceptPointPtr( const std::map<SPoint*, int>& mapPoint, const int x, const int y );

};