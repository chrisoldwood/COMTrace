////////////////////////////////////////////////////////////////////////////////
//! \file   CustomTracer.cpp
//! \brief  The CustomTracer class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "CustomTracer.hpp"

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

CustomTracer::CustomTracer()
	: COMTraceObject<ICustomInterface>(TXT("CustomTracer"))
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
	LOG_ENTRY(TXT("CustomTracer::TestMethod()"));

	HRESULT hr = S_OK;

	try
	{
		// Check output parameters.
		if (pbstrOutput == nullptr)
			throw WCL::ComException(E_POINTER, TXT("pbstrOutput is NULL"));

		// Reverse the input string.
		*pbstrOutput = _wcsrev(::SysAllocString(BSTR2W(bstrInput)));
	}
	COM_CATCH(hr)

	LOG_EXIT(TXT("HRESULT=0x%08X [%s]"), hr, CStrCvt::FormatError(hr));

	return hr;
}
