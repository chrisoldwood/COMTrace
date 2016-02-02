////////////////////////////////////////////////////////////////////////////////
//! \file   TestComPtr.cpp
//! \brief  The unit tests for .
//! \author Chris Oldwood

#include "Common.hpp"
#include <Core/UnitTest.hpp>
#include <WCL/ComPtr.hpp>

TEST_SET(ComPtr)
{
	typedef WCL::ComPtr<COMTraceLib::ICustomInterface> IInterfacePtr;

TEST_CASE("The custom tracer COM object can created")
{
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
TEST_CASE_END

}
TEST_SET_END
