#include "pch.h"
#include "CppUnitTest.h"
#include "../ProgrammerProject/Programmer.h"
#include "../ProgrammerProject/Programmer.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestOneArgConstructor)
		{
			//Arrange
			std::string testName = "Test";

			//Act
			Programmer p1(testName);

			//Assert
			Assert::AreEqual(testName, p1.GetName());
			Assert::AreEqual(1, p1.GetCount());
		}
	};
}
