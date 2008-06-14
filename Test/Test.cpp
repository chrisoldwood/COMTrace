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

int _tmain(int /*argc*/, _TCHAR* /*argv*/[])
{
	TEST_SUITE_BEGIN
	{
		WCL::AutoCom oCom(COINIT_APARTMENTTHREADED);
//		WCL::AutoCom oCom(COINIT_MULTITHREADED);

		TestComPtr();
		TestCustom();
		TestDual();
		TestDispatch();
		TestErrorInfo();

		Core::SetTestRunFinalStatus(true);
	}
	TEST_SUITE_END
}
