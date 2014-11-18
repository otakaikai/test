#include "CAStarWayFind.h"
#include "assert.h"
#include <complex>
#include <map>

SPoint* CAStarWayFindHelper::findExceptPointPtr( const std::map<SPoint*, int>& mapPoint, const int x, const int y )
{
	for( std::map< SPoint*, int>::const_iterator it = mapPoint.begin(); it != mapPoint.end(); ++it )
	{
		if( it->first && x == it->first->_x && y == it->first->_y )
		{
			return it->first;
		}
	}

	return NULL;
}

bool CAStarWayFindHelper::findAndDealNearPoints( const MapNode& mapNode,
										 SPoint* paramPoint,
										 const SPoint* endPoint,
										 std::map<SPoint*,int>& mapExceptPoint,
										 PrioritySeqPonit& openPoints,
										 SeqPoint& closePoints )
{
	int arrX[3] = { paramPoint->_x-1, paramPoint->_x, paramPoint->_x+1 };
	int arrY[3] = { paramPoint->_y-1, paramPoint->_y, paramPoint->_y+1 };

	std::multimap<int, int> mapXY;
	for( int i = 0; i < 3; ++i )
	{
		for( int j = 0; j < 3; ++j )
		{
			mapXY.insert( std::make_pair( arrX[i], arrY[j] ) );
		}
	}

	int maxX = mapNode.size();
	int maxY = mapNode[0].size();
	for( std::multimap<int, int>::const_iterator it = mapXY.begin(); it != mapXY.end(); ++it )
	{
		if( it->first < 0 || it->first >= maxX || it->second < 0 || it->second >= maxY )
		{
			//出界点
			continue;
		}

		if( EPointForbid == mapNode[ it->first ][ it->second ] )
		{
			//不可移动的点
			continue;
		}

		SPoint* effectPoint = findExceptPointPtr( mapExceptPoint, it->first, it->second );
		if( effectPoint )
		{
			//纠正g值
			const double g = paramPoint->_g;
			const double g1 = effectPoint->_g + calPointsMinDistance( paramPoint, effectPoint );
			if( g > g1 )
			{
				paramPoint->_g = g1;
				paramPoint->_fromPoint = effectPoint;

				if( EPointPosOpen == mapExceptPoint[ effectPoint ] )
				{
					//对open队列的点这里应该要重新纠正优先顺序
				}
				else
				{
					//如果是close队列中的点，考虑把点移到open队列
				}
			}

			//排除点
			continue;
		}

		//构建相邻点并加入open队列
		SPoint* point = new SPoint( it->first, it->second );
		const double g = paramPoint->_g + calPointsMinDistance( paramPoint, point );	//两点直线距离做为实际值
		const int h = calPointsMaxDistance( point, endPoint );							//两点边界距离做为估计值（考虑优化）
		point->_g = g;
		point->_h = h;
		point->_fromPoint = paramPoint;
		openPoints.push( point );

		//加入排除点
		mapExceptPoint[ point ] = EPointPosOpen;
	}
	return true;
}

int CAStarWayFindHelper::calPointsMaxDistance( const SPoint* fromPoint, const SPoint* toPoint )
{
	const int distancX = abs( fromPoint->_x - toPoint->_x ) * X_SIZE;
	const int distancY = abs( fromPoint->_y - toPoint->_y ) * Y_SIZE;

	return distancX + distancY;
}

double CAStarWayFindHelper::calPointsMinDistance( const SPoint* fromPoint, const SPoint* toPoint )
{
	const int distancX = abs( fromPoint->_x - toPoint->_x ) * X_SIZE;
	const int distancY = abs( fromPoint->_y - toPoint->_y ) * Y_SIZE;

	return sqrt( double( distancX * distancX + distancY * distancY ) );
}

bool CAStarWayFindHelper::isSamePointPos( const SPoint* pointA, const SPoint* pointB )
{
	if( pointA->_x == pointB->_x && pointA->_y == pointB->_y )
	{
		return true;
	}
	return false;
}