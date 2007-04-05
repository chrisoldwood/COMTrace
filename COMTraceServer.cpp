////////////////////////////////////////////////////////////////////////////////
//! \author Chris Oldwood
//! \file   COMTraceServer.cpp
//! \brief  The COMTraceServer class definition.

#include "AppHeaders.hpp"

#ifdef _DEBUG
// For memory leak detection.
#define new DBGCRT_NEW
#endif

//! The component object.
COMTraceServer Dll;

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
	WCL::TraceLogger::SetLogFile(CPath::ModuleDir() / "COMTrace.log");

	TRACE("****************************************\n");
	TRACE("COMTraceServer::OnLoad()\n");
}

////////////////////////////////////////////////////////////////////////////////
//! DLL unloading.

void COMTraceServer::OnUnload()
{
	TRACE("COMTraceServer::OnUnload()\n");
}

////////////////////////////////////////////////////////////////////////////////
//! Thread created.

void COMTraceServer::OnThreadAttached()
{
	TRACE("COMTraceServer::OnThreadAttached()\n");
}

////////////////////////////////////////////////////////////////////////////////
//! Thread destroyed.

void COMTraceServer::OnThreadDetached()
{
	TRACE("COMTraceServer::OnThreadDetached()\n");
}

////////////////////////////////////////////////////////////////////////////////
//! Entry point for obtaining the class factory.

HRESULT COMTraceServer::DllGetClassObject(REFCLSID rCLSID, REFIID rIID, LPVOID* /*ppFactory*/)
{
	std::tstring strCLSID = COM::FormatGUID(rCLSID);
	std::tstring strIID   = COM::FormatGUID(rIID);

	TRACE("COMTraceServer::DllGetClassObject(...)\n");
	TRACE1("  CLSID=%s\n", strCLSID.c_str());
	TRACE1("  IID=%s\n",   strIID.c_str());

	return E_NOTIMPL;
}

////////////////////////////////////////////////////////////////////////////////
//! Entry point for querying if the server can be unloaded..

HRESULT COMTraceServer::DllCanUnloadNow()
{
	TRACE("COMTraceServer::DllCanUnloadNow()\n");

	return E_NOTIMPL;
}

////////////////////////////////////////////////////////////////////////////////
//! Entry point for registering the inproc server.

HRESULT COMTraceServer::DllRegisterServer()
{
	TRACE("COMTraceServer::DllRegisterServer()\n");

	return E_NOTIMPL;
}

////////////////////////////////////////////////////////////////////////////////
//! Entry point for unregistering the inproc server.

HRESULT COMTraceServer::DllUnregisterServer()
{
	TRACE("COMTraceServer::DllUnregisterServer()\n");

	return E_NOTIMPL;
}
