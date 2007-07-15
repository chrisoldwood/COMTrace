////////////////////////////////////////////////////////////////////////////////
//! \file   COMTraceServer.cpp
//! \brief  The COMTraceServer class definition.
//! \author Chris Oldwood

#include "COMTrace.hpp"
#include "COMTraceServer.hpp"
#include "COMTraceFactory.hpp"
#include <WCL/File.hpp>

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

//! The component object.
COMTraceServer g_oDll;

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

COMTraceServer::COMTraceServer()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

COMTraceServer::~COMTraceServer()
{
}

////////////////////////////////////////////////////////////////////////////////
//! DLL loaded.

void COMTraceServer::OnLoad()
{
	CPath strFile = CPath::ModuleDir() / "COMTrace.log";

	// Initialise the logger.
	// NB: We have to do it after the CModule singleton has been initialised.
	g_oLogger.SetFilename(std::tstring(strFile));
	CFile::Delete(strFile);

	LOG_MSG  ("************************************************************");
	LOG_ENTRY("COMTraceServer::OnLoad()");
	LOG_EXIT ("VOID");
}

////////////////////////////////////////////////////////////////////////////////
//! DLL unloading.

void COMTraceServer::OnUnload()
{
	LOG_ENTRY("COMTraceServer::OnUnload()");
	LOG_EXIT ("VOID");
}

////////////////////////////////////////////////////////////////////////////////
//! Thread created.

void COMTraceServer::OnThreadAttached()
{
	LOG_ENTRY("COMTraceServer::OnThreadAttached()");
	LOG_EXIT ("VOID");
}

////////////////////////////////////////////////////////////////////////////////
//! Thread destroyed.

void COMTraceServer::OnThreadDetached()
{
	LOG_ENTRY("COMTraceServer::OnThreadDetached()");
	LOG_EXIT ("VOID");
}

////////////////////////////////////////////////////////////////////////////////
//! Entry point for obtaining the class factory.

HRESULT COMTraceServer::DllGetClassObject(REFCLSID rCLSID, REFIID rIID, LPVOID* ppFactory)
{
	std::tstring strCLSID     = COM::FormatGUID(rCLSID);
	std::tstring strClassName = COM::LookupCLSID(rCLSID);
	std::tstring strIID       = COM::FormatGUID(rIID);
	std::tstring strIFaceName = COM::LookupIID(rIID);

	LOG_ENTRY("COMTraceServer::DllGetClassObject(CLSID, IID)");
	LOG_PARAM("CLSID=%s [%s]", strCLSID.c_str(), strClassName.c_str());
	LOG_PARAM("IID=%s [%s]",   strIID.c_str(),   strIFaceName.c_str());

	HRESULT hr = InprocServer::DllGetClassObject(rCLSID, rIID, ppFactory);

	LOG_EXIT("HRESULT=0x%08X [%s]", hr, CStrCvt::FormatError(hr));

	return hr;
}

////////////////////////////////////////////////////////////////////////////////
//! Entry point for querying if the server can be unloaded.

HRESULT COMTraceServer::DllCanUnloadNow()
{
	LOG_ENTRY("COMTraceServer::DllCanUnloadNow()");
	LOG_VAR("LockCount=%u", LockCount());

	HRESULT hr = InprocServer::DllCanUnloadNow();

	LOG_EXIT("HRESULT=0x%08X [%s]", hr, CStrCvt::FormatError(hr));

	return hr;
}

////////////////////////////////////////////////////////////////////////////////
//! Entry point for registering the inproc server.

HRESULT COMTraceServer::DllRegisterServer()
{
	LOG_ENTRY("COMTraceServer::DllRegisterServer()");

	HRESULT hr = InprocServer::DllRegisterServer();

	LOG_EXIT("HRESULT=0x%08X [%s]", hr, CStrCvt::FormatError(hr));

	return hr;
}

////////////////////////////////////////////////////////////////////////////////
//! Entry point for unregistering the inproc server.

HRESULT COMTraceServer::DllUnregisterServer()
{
	LOG_ENTRY("COMTraceServer::DllUnregisterServer()");

	HRESULT hr = InprocServer::DllUnregisterServer();

	LOG_EXIT("HRESULT=0x%08X [%s]", hr, CStrCvt::FormatError(hr));

	return hr;
}

////////////////////////////////////////////////////////////////////////////////
//! Lock the server.

void COMTraceServer::Lock()
{
	LOG_ENTRY("COMTraceServer::Lock()");

	Server::Lock();

	LOG_VAR("LockCount=%u", LockCount());
	LOG_EXIT ("VOID");
}

////////////////////////////////////////////////////////////////////////////////
//! Unlock the server.

void COMTraceServer::Unlock()
{
	LOG_ENTRY("COMTraceServer::Unlock()");

	Server::Unlock();

	LOG_VAR("LockCount=%u", LockCount());
	LOG_EXIT ("VOID");
}

////////////////////////////////////////////////////////////////////////////////
//! Template Method to get the servers class factory.

COM::IClassFactoryPtr COMTraceServer::CreateClassFactory(const CLSID& oCLSID)
{
	return COM::IClassFactoryPtr(new COMTraceFactory(oCLSID), true);
}
