////////////////////////////////////////////////////////////////////////////////
//! \file   CustomTracer.cpp
//! \brief  The CustomTracer class definition.
//! \author Chris Oldwood

#include "AppHeaders.hpp"

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
			throw E_POINTER;

		// Reverse the input string.
		*pbstrOutput = _wcsrev(::SysAllocString(bstrInput));
	}
	COM_CATCH_TRACE_AND_SET("CustomTracer::TestMethod()", hr)

	LOG_EXIT("HRESULT=0x%08X [%s]", hr, CStrCvt::FormatError(hr));

	return hr;
}
