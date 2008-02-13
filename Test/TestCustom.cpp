////////////////////////////////////////////////////////////////////////////////
//! \file   TestCustom.cpp
//! \brief  The unit tests for the custom interface.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/ComPtr.hpp>
#include <WCL/ComStr.hpp>

////////////////////////////////////////////////////////////////////////////////
//! The unit tests for the custom interface.

void TestCustom()
{
	typedef WCL::ComPtr<COMTraceLib::ICustomInterface> IInterfacePtr;

	WCL::ComStr bstrIn(L"Hello World!");
	WCL::ComStr bstrOut;

	IInterfacePtr pTracer(__uuidof(COMTraceLib::CustomTracer));
	HRESULT hr = pTracer->TestMethod(bstrIn.Get(), AttachTo(bstrOut));

	TEST_TRUE(hr == S_OK);
	TEST_TRUE(wcscmp(bstrOut.Get(), L"!dlroW olleH") == 0);
}
