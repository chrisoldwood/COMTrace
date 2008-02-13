////////////////////////////////////////////////////////////////////////////////
//! \file   DispatchTracer.cpp
//! \brief  The DispatchTracer class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "DispatchTracer.hpp"
#include <WCL/Variant.hpp>

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

DispatchTracer::DispatchTracer()
	: COMTraceObject<IDispatch>(TXT("DispatchTracer"))
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
	return _wcsrev(::SysAllocString(BSTR2W(bstrInput)));
}

////////////////////////////////////////////////////////////////////////////////
//! Get the number of type information interfaces supported. We do not support
//! any type information in this implementation.

HRESULT COMCALL DispatchTracer::GetTypeInfoCount(UINT* pnInfo)
{
	LOG_ENTRY(TXT("DispatchTracer::GetTypeInfoCount(UINT*)"));

	HRESULT hr = S_OK;

	try
	{
		// Check output parameters.
		if (pnInfo == nullptr)
			throw WCL::ComException(E_POINTER, TXT("pnInfo is NULL"));

		*pnInfo = 0;
	}
	COM_CATCH(hr)

	LOG_EXIT(TXT("HRESULT=0x%08X [%s]"), hr, CStrCvt::FormatError(hr));

	return hr;
}

////////////////////////////////////////////////////////////////////////////////
//! Get the type information for an object.

HRESULT COMCALL DispatchTracer::GetTypeInfo(UINT nInfo, LCID dwLCID, ITypeInfo** ppTypeInfo)
{
	LOG_ENTRY(TXT("DispatchTracer::GetTypeInfoCount(UINT, dwLCID)"));
	LOG_PARAM(TXT("UINT=%u"), nInfo);
	LOG_PARAM(TXT("dwLCID=%u"), dwLCID);

	HRESULT hr = E_NOTIMPL;

	try
	{
		// Check output parameters.
		if (ppTypeInfo == nullptr)
			throw WCL::ComException(E_POINTER, TXT("ppTypeInfo is NULL"));

		// Reset output parameters.
		*ppTypeInfo = nullptr;
	}
	COM_CATCH(hr)

	LOG_EXIT(TXT("HRESULT=0x%08X [%s]"), hr, CStrCvt::FormatError(hr));

	return hr;
}

////////////////////////////////////////////////////////////////////////////////
//! Map a number of names to their dispatch IDs.

HRESULT COMCALL DispatchTracer::GetIDsOfNames(REFIID /*rIID*/, LPOLESTR* aszNames, UINT nNames, LCID /*dwLCID*/, DISPID* alMemberIDs)
{
	LOG_ENTRY(TXT("DispatchTracer::GetIDsOfNames(REFIID, LPOLESTR*, UINT, LCID, DISPID*)"));
	LOG_PARAM(TXT("UINT=%u"), nNames);

	for (size_t i = 0; i < nNames; ++i)
		LOG_PARAM(TXT("LPOLESTR*[%d]=%s"), i, W2T(aszNames[i]));

	HRESULT hr = DISP_E_UNKNOWNNAME;

	try
	{
		// Check output parameters.
		if (alMemberIDs == nullptr)
			throw WCL::ComException(E_POINTER, TXT("alMemberIDs is NULL"));

		// Validate input parameters.
		if (nNames == 0)
			throw WCL::ComException(E_INVALIDARG, TXT("aszNames is empty"));

		// Initialise output DISPID array.
		for (size_t i = 0; i < nNames; ++i)
			alMemberIDs[i] = DISPID_UNKNOWN;

		// The first name must be the method or property name.
		if (_wcsicmp(aszNames[0], L"TestMethod") == 0)
		{
			alMemberIDs[0] = ID_TESTMETHOD;

			// We don't support named parameters.
			if (nNames == 1)
				hr = S_OK;
		}
	}
	COM_CATCH(hr)

	LOG_EXIT(TXT("HRESULT=0x%08X [%s]"), hr, CStrCvt::FormatError(hr));

	return hr;
}

////////////////////////////////////////////////////////////////////////////////
//! Invoke a method or access a property.

HRESULT COMCALL DispatchTracer::Invoke(DISPID lMemberID, REFIID /*rIID*/, LCID /*dwLCID*/, WORD wFlags, DISPPARAMS* pParams, VARIANT* pResult, EXCEPINFO* pExcepInfo, UINT* pnArgError)
{
	LOG_ENTRY(TXT("DispatchTracer::Invoke(DISPID, REFIID, LCID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO*, UINT*)"));
	LOG_PARAM(TXT("DISPID=%d"), lMemberID);
	LOG_PARAM(TXT("WORD=0x%08X"), static_cast<DWORD>(wFlags));
	LOG_PARAM(TXT("DISPPARAMS*=Total: %u Named: %u"), pParams->cArgs, pParams->cNamedArgs);

	for (size_t i = 0; i < pParams->cArgs; ++i)
		LOG_PARAM(TXT("DISPPARAMS[%u]=%s"), i, WCL::Variant::FormatFullType(&pParams->rgvarg[i]));

	HRESULT hr = E_FAIL;

	try
	{
		// Check output parameters.
		if ( (pResult == nullptr) || (pExcepInfo == nullptr) || (pnArgError == nullptr) )
			throw WCL::ComException(E_POINTER, TXT("pResult/pExcepInfo/pnArgError is NULL"));

		// Validate input parameters.
		if (pParams == nullptr)
			throw WCL::ComException(E_POINTER, TXT("pParams is NULL"));

		// Reset output parameters.
//		::VariantInit(pResult);

		// Validate DISPID.
		if (lMemberID != ID_TESTMETHOD)
			throw WCL::ComException(DISP_E_MEMBERNOTFOUND, TXT("lMemberID must be ID_TESTMETHOD"));

		// Validate call type.
		if (!(wFlags & DISPATCH_METHOD))
			throw WCL::ComException(DISP_E_MEMBERNOTFOUND, TXT("wFlags must contain DISPATCH_METHOD"));

		// Validate parameters.
		if (pParams->cArgs != 1)
			throw WCL::ComException(DISP_E_BADPARAMCOUNT, TXT("pParams->cArgs must be 1"));

		if (pParams->cNamedArgs != 0)
			throw WCL::ComException(DISP_E_NONAMEDARGS, TXT("pParams->cNamedArgs must be 0"));

		// Coerce parameters.
		WCL::Variant vtParam(pParams->rgvarg[0], VT_BSTR);

		// Invoke the method.
		V_BSTR(pResult) = TestMethod(V_BSTR(&vtParam));
		V_VT(pResult)   = VT_BSTR;

		hr = S_OK;
	}
	COM_CATCH(hr)

	LOG_EXIT(TXT("HRESULT=0x%08X [%s]"), hr, CStrCvt::FormatError(hr));

	return hr;
}
