////////////////////////////////////////////////////////////////////////////////
//! \file   TestDual.cpp
//! \brief  The unit tests for the dual interface.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/ComPtr.hpp>
#include <WCL/ComStr.hpp>
#include <WCL/Variant.hpp>

////////////////////////////////////////////////////////////////////////////////
//! The unit tests for the dual interface.

void TestDual()
{
	typedef WCL::ComPtr<COMTraceLib::IDualInterface> IInterfacePtr;

	const wchar_t* wstrIn(L"Hello World!");

	IInterfacePtr pTracer(__uuidof(COMTraceLib::DualTracer));

	wchar_t* apszMethods[1] = { L"TestMethod" };
	DISPID   anMethodIDs[1];

	HRESULT hr = pTracer->GetIDsOfNames(IID_NULL, apszMethods, ARRAY_SIZE(apszMethods), 0, anMethodIDs);

	TEST_TRUE(SUCCEEDED(hr));

	WCL::Variant vtInput(wstrIn);
	DISPPARAMS   oParams = {&vtInput, nullptr, 1, 0};
	WCL::Variant vtResult;
	EXCEPINFO    oExcepInfo = {0};
	UINT         uArgErr = 0;

	hr = pTracer->Invoke(anMethodIDs[0], IID_NULL, 0, DISPATCH_METHOD, &oParams, &vtResult, &oExcepInfo, &uArgErr);

	TEST_TRUE(SUCCEEDED(hr));
	TEST_TRUE(wcscmp(V_BSTR(&vtResult), L"!dlroW olleH") == 0);

	WCL::ComStr bstrIn(wstrIn);
	WCL::ComStr bstrOut;

	hr = pTracer->TestMethod(bstrIn.Get(), AttachTo(bstrOut));

	TEST_TRUE(SUCCEEDED(hr));
	TEST_TRUE(wcscmp(bstrOut.Get(), L"!dlroW olleH") == 0);
}
