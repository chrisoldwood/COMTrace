////////////////////////////////////////////////////////////////////////////////
//! \file   COMTraceFactory.cpp
//! \brief  The COMTraceFactory class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "COMTraceFactory.hpp"
#include <COM/InprocServer.hpp>

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

COMTraceFactory::COMTraceFactory(const CLSID& rCLSID)
	: COMTraceObject<IClassFactory>(TXT("COMTraceFactory"))
	, m_pClassFactory(new COM::ClassFactory(rCLSID), true)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

COMTraceFactory::~COMTraceFactory()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Create an instance object of the class.

HRESULT COMCALL COMTraceFactory::CreateInstance(IUnknown* pOuter, const IID& rIID, void** ppInterface)
{
	tstring strIID       = COM::FormatGUID(rIID);
	tstring strIFaceName = COM::LookupIID(rIID);

	LOG_ENTRY(TXT("COMTraceFactory::CreateInstance(IUnknown*, IID)"));
	LOG_PARAM(TXT("IUnknown*=0x%p"), pOuter);
	LOG_PARAM(TXT("IID=%s [%s]"), strIID.c_str(), strIFaceName.c_str());

	HRESULT hr = m_pClassFactory->CreateInstance(pOuter, rIID, ppInterface);

	LOG_EXIT(TXT("HRESULT=0x%08X [%s]"), hr, CStrCvt::FormatError(hr));

	return hr;
}

////////////////////////////////////////////////////////////////////////////////
//! Lock the COM server.

HRESULT COMCALL COMTraceFactory::LockServer(BOOL fLock)
{
	LOG_ENTRY(TXT("COMTraceFactory::LockServer(%s)"), (fLock) ? TXT("TRUE") : TXT("FALSE"));

	HRESULT hr = m_pClassFactory->LockServer(fLock);

	LOG_VAR(TXT("LockCount=%u"), COM::InprocServer::This().LockCount());
	LOG_EXIT(TXT("HRESULT=0x%08X [%s]"), hr, CStrCvt::FormatError(hr));

	return hr;
}
