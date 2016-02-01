////////////////////////////////////////////////////////////////////////////////
//! \file   TestDispatch.cpp
//! \brief  The unit tests for the automation interface.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/Variant.hpp>
#include <WCL/ComPtr.hpp>

TEST_SET(Dispatch)
{
	typedef WCL::ComPtr<::IDispatch> IInterfacePtr;

TEST_CASE("The IDispatch-based tracer COM object test method can be invoked")
{
	const wchar_t* wstrIn(L"Hello World!");

	IInterfacePtr pTracer(__uuidof(COMTraceLib::DispatchTracer));

	wchar_t* apszMethods[1] = { L"TestMethod" };
	DISPID   anMethodIDs[1];

	HRESULT hr = pTracer->GetIDsOfNames(IID_NULL, apszMethods, ARRAY_SIZE(apszMethods), 0, anMethodIDs);

	TEST_TRUE(SUCCEEDED(hr));

	WCL::ComStr  bstrIn(wstrIn);
	WCL::Variant vtInput(bstrIn);
	DISPPARAMS   oParams = {&vtInput, nullptr, 1, 0};
	WCL::Variant vtResult;
	EXCEPINFO    oExcepInfo = {0};
	UINT         uArgErr = 0;

	hr = pTracer->Invoke(anMethodIDs[0], IID_NULL, 0, DISPATCH_METHOD, &oParams, &vtResult, &oExcepInfo, &uArgErr);

	TEST_TRUE(SUCCEEDED(hr));
	TEST_TRUE(wcscmp(V_BSTR(&vtResult), L"!dlroW olleH") == 0);
}
TEST_CASE_END

}
TEST_SET_END
