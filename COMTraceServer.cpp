////////////////////////////////////////////////////////////////////////////////
//! \file   COMTraceServer.cpp
//! \brief  The COMTraceServer class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "COMTraceServer.hpp"
#include "COMTraceFactory.hpp"
#include <WCL/File.hpp>

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
	CPath strFile = CPath::ModuleDir() / TXT("COMTrace.log");

	// Initialise the logger.
	// NB: We have to do it after the CModule singleton has been initialised.
	g_oLogger.SetFilename(tstring(strFile));
	CFile::Delete(strFile);

	LOG_MSG  (TXT("************************************************************"));
	LOG_ENTRY(TXT("COMTraceServer::OnLoad()"));
	LOG_EXIT (TXT("VOID"));
}

////////////////////////////////////////////////////////////////////////////////
//! DLL unloading.

void COMTraceServer::OnUnload()
{
{
	LOG_ENTRY(TXT("COMTraceServer::OnUnload()"));
	LOG_EXIT (TXT("VOID"));
}
	LOG_MSG  (TXT("------------------------------------------------------------"));
}

////////////////////////////////////////////////////////////////////////////////
//! Thread created.

void COMTraceServer::OnThreadAttached()
{
	LOG_ENTRY(TXT("COMTraceServer::OnThreadAttached()"));
	LOG_EXIT (TXT("VOID"));
}

////////////////////////////////////////////////////////////////////////////////
//! Thread destroyed.

void COMTraceServer::OnThreadDetached()
{
	LOG_ENTRY(TXT("COMTraceServer::OnThreadDetached()"));
	LOG_EXIT (TXT("VOID"));
}

////////////////////////////////////////////////////////////////////////////////
//! Entry point for obtaining the class factory.

HRESULT COMTraceServer::DllGetClassObject(REFCLSID rCLSID, REFIID rIID, LPVOID* ppFactory)
{
	try
	{
		tstring strCLSID     = COM::FormatGUID(rCLSID);
		tstring strClassName = COM::LookupCLSID(rCLSID);
		tstring strIID       = COM::FormatGUID(rIID);
		tstring strIFaceName = COM::LookupIID(rIID);

		LOG_ENTRY(TXT("COMTraceServer::DllGetClassObject(CLSID, IID)"));
		LOG_PARAM(TXT("CLSID=%s [%s]"), strCLSID.c_str(), strClassName.c_str());
		LOG_PARAM(TXT("IID=%s [%s]"),   strIID.c_str(),   strIFaceName.c_str());

		HRESULT hr = InprocServer::DllGetClassObject(rCLSID, rIID, ppFactory);

		LOG_EXIT(TXT("HRESULT=0x%08X [%s]"), hr, CStrCvt::FormatError(hr));

		return hr;
	}
	LOG_EXCEPTION_AND_RETHROW
}

////////////////////////////////////////////////////////////////////////////////
//! Entry point for querying if the server can be unloaded.

HRESULT COMTraceServer::DllCanUnloadNow()
{
	try
	{
		LOG_ENTRY(TXT("COMTraceServer::DllCanUnloadNow()"));
		LOG_VAR(TXT("LockCount=%u"), LockCount());

		HRESULT hr = InprocServer::DllCanUnloadNow();

		LOG_EXIT(TXT("HRESULT=0x%08X [%s]"), hr, CStrCvt::FormatError(hr));

		return hr;
	}
	LOG_EXCEPTION_AND_RETHROW
}

////////////////////////////////////////////////////////////////////////////////
//! Entry point for registering the inproc server.

HRESULT COMTraceServer::DllRegisterServer()
{
	try
	{
		LOG_ENTRY(TXT("COMTraceServer::DllRegisterServer()"));

		HRESULT hr = InprocServer::DllRegisterServer();

		LOG_EXIT(TXT("HRESULT=0x%08X [%s]"), hr, CStrCvt::FormatError(hr));

		return hr;
	}
	LOG_EXCEPTION_AND_RETHROW
}

////////////////////////////////////////////////////////////////////////////////
//! Entry point for unregistering the inproc server.

HRESULT COMTraceServer::DllUnregisterServer()
{
	try
	{
		LOG_ENTRY(TXT("COMTraceServer::DllUnregisterServer()"));

		HRESULT hr = InprocServer::DllUnregisterServer();

		LOG_EXIT(TXT("HRESULT=0x%08X [%s]"), hr, CStrCvt::FormatError(hr));

		return hr;
	}
	LOG_EXCEPTION_AND_RETHROW
}

////////////////////////////////////////////////////////////////////////////////
//! Register or unregister the server to/from the registry.

HRESULT COMTraceServer::DllInstall(bool install, const tchar* cmdLine)
{
	try
	{
		LOG_ENTRY(TXT("COMTraceServer::DllInstall()"));
		LOG_PARAM(TXT("INSTALL=%s"), (install) ? TXT("true") : TXT("false"));
		LOG_PARAM(TXT("CMDLINE=%s"), (cmdLine != nullptr) ? cmdLine : TXT("(null)"));

		HRESULT hr = InprocServer::DllInstall(install, cmdLine);

		LOG_EXIT(TXT("HRESULT=0x%08X [%s]"), hr, CStrCvt::FormatError(hr));

		return hr;
	}
	LOG_EXCEPTION_AND_RETHROW
}

////////////////////////////////////////////////////////////////////////////////
//! Lock the server.

void COMTraceServer::Lock()
{
	try
	{
		LOG_ENTRY(TXT("COMTraceServer::Lock()"));

		Server::Lock();

		LOG_VAR(TXT("LockCount=%u"), LockCount());
		LOG_EXIT(TXT("VOID"));
	}
	LOG_EXCEPTION_AND_RETHROW
}

////////////////////////////////////////////////////////////////////////////////
//! Unlock the server.

void COMTraceServer::Unlock()
{
	try
	{
		LOG_ENTRY(TXT("COMTraceServer::Unlock()"));

		Server::Unlock();

		LOG_VAR(TXT("LockCount=%u"), LockCount());
		LOG_EXIT(TXT("VOID"));
	}
	LOG_EXCEPTION_AND_RETHROW
}

////////////////////////////////////////////////////////////////////////////////
//! Template Method to get the servers class factory.

COM::IClassFactoryPtr COMTraceServer::CreateClassFactory(const CLSID& oCLSID)
{
	return COM::IClassFactoryPtr(new COMTraceFactory(oCLSID), true);
}
