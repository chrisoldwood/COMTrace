////////////////////////////////////////////////////////////////////////////////
//! \file   DispatchTracer.cpp
//! \brief  The DispatchTracer class definition.
//! \author Chris Oldwood

#include "AppHeaders.hpp"

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

DispatchTracer::DispatchTracer()
	: COMTraceObject<IDispatch>("DispatchTracer")
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

DispatchTracer::~DispatchTracer()
{
}

////////////////////////////////////////////////////////////////////////////////
//! The test method.

BSTR DispatchTracer::TestMethod(BSTR bstrInput)
{
	// Reverse the input string.
	return _wcsrev(::SysAllocString(bstrInput));
}

////////////////////////////////////////////////////////////////////////////////
//! Get the number of type information interfaces supported. We do not support
//! any type information in this implementation.

HRESULT COMCALL DispatchTracer::GetTypeInfoCount(UINT* pnInfo)
{
	LOG_ENTRY("DispatchTracer::GetTypeInfoCount(UINT*)");

	HRESULT hr = S_OK;

	try
	{
		// Check output parameters.
		if (pnInfo == nullptr)
			throw E_POINTER;

		*pnInfo = 0;
	}
	COM_CATCH_TRACE_AND_SET("DispatchTracer::GetTypeInfoCount()", hr)

	LOG_EXIT("HRESULT=0x%08X [%s]", hr, CStrCvt::FormatError(hr));

	return hr;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the type information for an object.

HRESULT COMCALL DispatchTracer::GetTypeInfo(UINT nInfo, LCID dwLCID, ITypeInfo** ppTypeInfo)
{
	USES_CONVERSION;

	LOG_ENTRY("DispatchTracer::GetTypeInfoCount(UINT, dwLCID)");
	LOG_PARAM("UINT=%u", nInfo);
	LOG_PARAM("dwLCID=%u", dwLCID);

	HRESULT hr = E_NOTIMPL;

	try
	{
		// Check output parameters.
		if (ppTypeInfo == nullptr)
			throw E_POINTER;

		// Reset output parameters.
		*ppTypeInfo = nullptr;
	}
	COM_CATCH_TRACE_AND_SET("DispatchTracer::GetTypeInfo()", hr)

	LOG_EXIT("HRESULT=0x%08X [%s]", hr, CStrCvt::FormatError(hr));

	return hr;
}

////////////////////////////////////////////////////////////////////////////////
//! Map a number of names to their dispatch IDs.

HRESULT COMCALL DispatchTracer::GetIDsOfNames(REFIID /*rIID*/, LPOLESTR* aszNames, UINT nNames, LCID /*dwLCID*/, DISPID* alMemberIDs)
{
	USES_CONVERSION;

	LOG_ENTRY("DispatchTracer::GetIDsOfNames(REFIID, LPOLESTR*, UINT, LCID, DISPID*)");
	LOG_PARAM("UINT=%u", nNames);

	for (size_t i = 0; i < nNames; ++i)
		LOG_PARAM("LPOLESTR*[%d]=%s", i, W2T(aszNames[i]));

	HRESULT hr = DISP_E_UNKNOWNNAME;

	try
	{
		// Check output parameters.
		if (alMemberIDs == nullptr)
			throw E_POINTER;

		// Validate input parameters.
		if (nNames == 0)
			throw E_INVALIDARG;

		// Initialise output DISPID array.
		for (size_t i = 0; i < nNames; ++i)
			alMemberIDs[i] = DISPID_UNKNOWN;

		// The first name must be the method or property name.
		if (wcsicmp(aszNames[0], L"TestMethod") == 0)
		{
			alMemberIDs[0] = ID_TESTMETHOD;

			// We don't support named parameters.
			if (nNames == 1)
				hr = S_OK;
		}
	}
	COM_CATCH_TRACE_AND_SET("DispatchTracer::GetIDsOfNames()", hr)

	LOG_EXIT("HRESULT=0x%08X [%s]", hr, CStrCvt::FormatError(hr));

	return hr;
}

////////////////////////////////////////////////////////////////////////////////
//! Invoke a method or access a property.

HRESULT COMCALL DispatchTracer::Invoke(DISPID lMemberID, REFIID /*rIID*/, LCID /*dwLCID*/, WORD wFlags, DISPPARAMS* pParams, VARIANT* pResult, EXCEPINFO* pExcepInfo, UINT* pnArgError)
{
	LOG_ENTRY("DispatchTracer::Invoke(DISPID, REFIID, LCID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO*, UINT*)");
	LOG_PARAM("DISPID=%d", lMemberID);
	LOG_PARAM("WORD=0x%08X", static_cast<DWORD>(wFlags));
	LOG_PARAM("DISPPARAMS*=Total: %u Named: %u", pParams->cArgs, pParams->cNamedArgs);

	for (size_t i = 0; i < pParams->cArgs; ++i)
		LOG_PARAM("DISPPARAMS[%u]=%s", i, WCL::Variant::FormatFullType(&pParams->rgvarg[i]));

	HRESULT hr = E_FAIL;

	try
	{
		// Check output parameters.
		if ( (pResult == nullptr) || (pExcepInfo == nullptr) || (pnArgError == nullptr) )
			throw E_POINTER;

		// Validate input parameters.
		if (pParams == nullptr)
			throw E_POINTER;

		// Reset output parameters.
//		::VariantInit(pResult);

		// Validate DISPID.
		if (lMemberID != ID_TESTMETHOD)
			throw DISP_E_MEMBERNOTFOUND;

		// Validate call type.
		if (!(wFlags & DISPATCH_METHOD))
			throw DISP_E_MEMBERNOTFOUND;

		// Validate parameters.
		if (pParams->cArgs != 1)
			throw DISP_E_BADPARAMCOUNT;

		if (pParams->cNamedArgs != 0)
			throw DISP_E_NONAMEDARGS;

		// Coerce parameters.
		WCL::Variant vtParam(pParams->rgvarg[0], VT_BSTR);

		// Invoke the method.
		V_BSTR(pResult) = TestMethod(V_BSTR(&vtParam));
		V_VT(pResult)   = VT_BSTR;

		hr = S_OK;
	}
	COM_CATCH_TRACE_AND_SET("DispatchTracer::Invoke()", hr)

	LOG_EXIT("HRESULT=0x%08X [%s]", hr, CStrCvt::FormatError(hr));

	return hr;
}
