////////////////////////////////////////////////////////////////////////////////
//! \file   TestCustom.cpp
//! \brief  The unit tests for the custom interface.
//! \author Chris Oldwood

#include "Common.hpp"
#include <Core/UnitTest.hpp>
#include <WCL/ComPtr.hpp>
#include <WCL/ComStr.hpp>

TEST_SET(Custom)
{
	typedef WCL::ComPtr<COMTraceLib::ICustomInterface> IInterfacePtr;

TEST_CASE("The custom tracer COM object test method can be invoked")
{
	WCL::ComStr bstrIn(L"Hello World!");
	WCL::ComStr bstrOut;

	IInterfacePtr pTracer(__uuidof(COMTraceLib::CustomTracer));
	HRESULT hr = pTracer->TestMethod(bstrIn.Get(), AttachTo(bstrOut));

	TEST_TRUE(hr == S_OK);
	TEST_TRUE(wcscmp(bstrOut.Get(), L"!dlroW olleH") == 0);
}
TEST_CASE_END

}
TEST_SET_END
