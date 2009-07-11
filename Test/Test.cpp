////////////////////////////////////////////////////////////////////////////////
//! \file   Test.cpp
//! \brief  The test harness entry point.
//! \author Chris Oldwood

#include "stdafx.h"
#include <tchar.h>
#include <Core/UnitTest.hpp>
#include <WCL/AutoCom.hpp>

////////////////////////////////////////////////////////////////////////////////
// The test group functions.

extern void TestComPtr();
extern void TestCustom();
extern void TestDual();
extern void TestDispatch();
extern void TestErrorInfo();

////////////////////////////////////////////////////////////////////////////////
//! The entry point for the test harness.

int _tmain(int argc, _TCHAR* argv[])
{
	TEST_SUITE_BEGIN(argc, argv)
	{
		WCL::AutoCom oCom(COINIT_APARTMENTTHREADED);
//		WCL::AutoCom oCom(COINIT_MULTITHREADED);

		TEST_CASE(TestComPtr);
		TEST_CASE(TestCustom);
		TEST_CASE(TestDual);
		TEST_CASE(TestDispatch);
		TEST_CASE(TestErrorInfo);

		Core::setTestRunFinalStatus(true);
	}
	TEST_SUITE_END
}
