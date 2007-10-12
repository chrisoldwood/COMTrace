////////////////////////////////////////////////////////////////////////////////
//! \file   CustomTracer.cpp
//! \brief  The CustomTracer class definition.
//! \author Chris Oldwood

#include "COMTrace.hpp"
#include "CustomTracer.hpp"

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

CustomTracer::CustomTracer()
	: COMTraceObject<ICustomInterface>("CustomTracer")
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

CustomTracer::~CustomTracer()
{
}

////////////////////////////////////////////////////////////////////////////////
//! The test method.

HRESULT COMCALL CustomTracer::TestMethod(BSTR bstrInput, BSTR* pbstrOutput)
{
	LOG_ENTRY("CustomTracer::TestMethod()");

	HRESULT hr = S_OK;

	try
	{
		// Check output parameters.
		if (pbstrOutput == nullptr)
			throw WCL::ComException(E_POINTER, "pbstrOutput is NULL");

		// Reverse the input string.
		*pbstrOutput = _wcsrev(::SysAllocString(BSTR2W(bstrInput)));
	}
	COM_CATCH(hr)

	LOG_EXIT("HRESULT=0x%08X [%s]", hr, CStrCvt::FormatError(hr));

	return hr;
}
