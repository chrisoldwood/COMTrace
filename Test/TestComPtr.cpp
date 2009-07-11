////////////////////////////////////////////////////////////////////////////////
//! \file   TestComPtr.cpp
//! \brief  The unit tests for .
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/ComPtr.hpp>

////////////////////////////////////////////////////////////////////////////////
//! The unit tests for the ComPtr template class.

void TestComPtr()
{
	typedef WCL::ComPtr<COMTraceLib::ICustomInterface> IInterfacePtr;

	IInterfacePtr pTracer1(__uuidof(COMTraceLib::CustomTracer));
	IInterfacePtr pTracer2(pTracer1);
	IInterfacePtr pTracer3;

	TEST_TRUE(pTracer1.get() != nullptr);
	TEST_TRUE(pTracer1.get() == pTracer2.get());
	TEST_TRUE(pTracer3.get() == nullptr);

	pTracer3 = pTracer2;

	TEST_TRUE(pTracer1 == pTracer2);

	pTracer1.Release();

	TEST_TRUE(!pTracer1);
}
