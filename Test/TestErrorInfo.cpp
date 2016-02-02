////////////////////////////////////////////////////////////////////////////////
//! \file   TestErrorInfo.cpp
//! \brief  The unit tests for the error handling.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WCL/ComPtr.hpp>
#include <WCL/ComStr.hpp>
#include <WCL/StrCvt.hpp>

#ifdef _MSC_VER
// declaration of 'Xxx' hides global declaration (ISupportErrorInfoPtr).
#pragma warning(disable : 4459)
#endif

TEST_SET(ErrorInfo)
{
	typedef WCL::ComPtr<COMTraceLib::ICustomInterface> IInterfacePtr;
	typedef WCL::ComPtr<ISupportErrorInfo> ISupportErrorInfoPtr;
	typedef WCL::ComPtr<IErrorInfo> IErrorInfoPtr;

TEST_CASE("An IErrorInfo COM object is returned when an error occurs")
{
	IInterfacePtr pTracer;
	pTracer.CreateInstance(__uuidof(COMTraceLib::CustomTracer));
	HRESULT hrMethod = pTracer->TestMethod(nullptr, nullptr);

	TEST_TRUE(FAILED(hrMethod));

	ISupportErrorInfoPtr pSupportErrorInfo(pTracer);
	HRESULT hr = pSupportErrorInfo->InterfaceSupportsErrorInfo(__uuidof(COMTraceLib::ICustomInterface));

	TEST_TRUE(hr == S_OK);

	IErrorInfoPtr pErrorInfo;
	hr = ::GetErrorInfo(0, AttachTo(pErrorInfo));

	TEST_TRUE(hr == S_OK);

	WCL::ComStr bstrSource;
	WCL::ComStr bstrDescription;

	pErrorInfo->GetSource(AttachTo(bstrSource));
	pErrorInfo->GetDescription(AttachTo(bstrDescription));

	TEST_TRUE(wcscmp(bstrSource.Get(), L"CustomTracer::TestMethod") == 0);
	TEST_TRUE(wcscmp(bstrDescription.Get(), L"pbstrOutput is NULL [0x80004003 - Invalid pointer]") == 0);
	TEST_TRUE(hrMethod == E_POINTER);
	TEST_TRUE(CStrCvt::FormatError(hrMethod) == TXT("Invalid pointer"));
}
TEST_CASE_END

}
TEST_SET_END
