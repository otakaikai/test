#include <string>
#include <vector>

void overlayFunc( const std::string& str, std::vector< int >& vecOverlay )
{
	const int size = str.size();	//字符串长度
	int index = 0;					//当前匹配的子串下标
	vecOverlay.resize( size, 0 );

	for( int i = 1; i < size; ++i )
	{
		if( str[ index ] == str[ i ] )
		{
			vecOverlay[ i ] = vecOverlay[ i - 1 ] + 1;
			++index;
		}
		else if( index > 0 )
		{
			int flag = i;
			while( true )
			{
				if( flag <= 0 )
				{
					vecOverlay[ i ] = 0;
					index = 0;
					break;
				}
				else if( str[ vecOverlay[ --flag ] ] == str[ i ] )
				{
					vecOverlay[ i ] = vecOverlay[ flag ] + 1;
					index = vecOverlay[ i ];
					break;
				}
			}
		}
	}
}

int myKMP( const std::string& target, const std::string& partion )
{
	std::vector<int> overlay;
	overlayFunc( partion, overlay );

	const int targetLen = target.size();
	const int partionLen = partion.size();

	int targetIndex = 0;
	int partionIndex = 0;

	while( targetIndex <= targetLen )
	{
		if( target[ targetIndex ] == partion[ partionIndex ] )
		{
			++targetIndex;
			++partionIndex;
		}
		else if( 0 == partionIndex )
		{
			++targetIndex;
			continue;
		}
		else
		{
			partionIndex = overlay[ partionIndex - 1 ];
		}

		if( partionIndex == partionLen )
		{
			return targetIndex - partionIndex;
		}
	}

	return -1;
}

int mySunDay( const std::string& targetStr, const std::string& partStr )
{
	const int targetSize = targetStr.size();
	const int partSize = partStr.size();

	int targetIndex = 0;
	int partIndex = 0;

	const int baseLetterIndex = 'a';
	std::vector< int > vecSymbol;
	vecSymbol.resize( 256, -1 );
	for( int i = 0; i < partSize; ++i )
	{
		vecSymbol[ partStr[ i ] - baseLetterIndex ] = i;
	}

	while( targetIndex <= targetSize )
	{
		if( targetStr[ targetIndex ] == partStr[ partIndex ] )
		{
			++targetIndex;
			++partIndex;
		}
		else
		{
			int nextIndex = targetIndex + partSize - partIndex;
			if( nextIndex >= targetSize )
			{
				return -1;
			}
			const int symbolIndex = vecSymbol[ targetStr[ nextIndex ] - baseLetterIndex ];
			if( symbolIndex >= 0 )
			{
				targetIndex = nextIndex - symbolIndex;
			}
			else
			{
				targetIndex = nextIndex + 1;
			}
			partIndex = 0;
		}

		if( partIndex == partSize )
		{
			return targetIndex - partIndex;
		}
	}

	return -1;
}