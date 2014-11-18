#include "CKmp.h"
#include <iostream>

class CParam
{
public:
	CParam( int val )
	{
		_val = val;
		std::cout << "CParam" << _val << std::endl;
	}
	~CParam(){ std::cout<<"~CParam()"<< _val << std::endl; }

	CParam( const CParam& param )
	{
		_val = param._val;
		std::cout << "CParam( const CParam& param )" << _val << std::endl;
	}
private:
	int _val;
};

int main()
{
	std::string targetString = "substringsearchzingalgorithmza";
	std::string partString = "searchz";

	//std::cout << "target: ";
	//std::cin >> targetString;
	//std::cout << std::endl;

	//std::cout << "part: ";
	//std::cin >> partString;
	//std::cout << std::endl;

	//int result = myKMP( targetString, partString );
	//int result = mySunDay( targetString, partString );
	//std::cout << "result:" << result;

	std::vector<CParam> vec;
	CParam a1(1);
	CParam a2(2);
	CParam a3(3);
	vec.push_back( a1 );
	std::cout << "------------------" << std::endl;
	vec.push_back( a2 );
	std::cout << "------------------" << std::endl;
	vec.push_back( a3 );
	std::cout << "------------------" << std::endl;
	getchar();

	return 0;
};