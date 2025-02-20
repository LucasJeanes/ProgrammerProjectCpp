/*
 `....
`..   `..   `..      `..
`..         `..      `..
`..     `...`.....`...`.....
`..         `..      `..
`..   `..   `..      `..
 `....

Michelle Lynch
*/

#include <iostream>          // cout, endl, fixed
#include <string>            // string
#include "Programmer.h"		 // Programmer
#include "TestProgrammer.h"	 // Test functions

void RunTests(int argc, char** argv)
{
	//TestDefaultCstr();
	TestAllArgCstr();
	//TestCopyCstr();
	//TestStaticDataMember();

}

void TestDefaultCstr()
{
	std::cout << std::endl << "***** Test Default Constructor *****" << std::endl;
	Programmer p1; //Default constructer
	std::cout << p1;
}

void TestAllArgCstr()
{
	std::cout << std::endl << "***** Test All-Argument Constructor *****" << std::endl;
	std::vector<std::string> lang{ "C++", "Simula", "Java" };
	Programmer p1("testName", lang);
	std::cout << p1;
}

void TestCopyCstr()
{
	std::cout << std::endl << "***** Test Copy Constructor *****" << std::endl;

	std::vector<std::string> lang{ "C++", "Rust", "Simula", "Java" };
	Programmer p1("me"); //Another constructor
	Programmer p2(p1); //Copy constructor
	std::cout << p1 << p2;
}

void TestStaticDataMember()
{
	std::cout << std::endl << "***** Test Static Data Member *****" << std::endl;
	Programmer p1;
	std::cout << p1.GetCount() << std::endl;
	Programmer p2;
	std::cout << p2.GetCount() << std::endl;
	std::cout << p1.GetCount() << std::endl;
}