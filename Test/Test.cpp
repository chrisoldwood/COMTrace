////////////////////////////////////////////////////////////////////////////////
//! \file   Test.cpp
//! \brief  The test harness entry point.
//! \author Chris Oldwood

#include "stdafx.h"
#include <tchar.h>
#include <Core/UnitTest.hpp>
#include <WCL/AutoCom.hpp>

////////////////////////////////////////////////////////////////////////////////
//! The entry point for the test harness.

int _tmain(int argc, _TCHAR* argv[])
{
	TEST_SUITE(argc, argv)
	{
		WCL::AutoCom oCom(COINIT_APARTMENTTHREADED);
//		WCL::AutoCom oCom(COINIT_MULTITHREADED);

		TEST_SUITE_RUN();
	}
	TEST_SUITE_END
}
