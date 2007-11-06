////////////////////////////////////////////////////////////////////////////////
//! \file   COMTraceServer.hpp
//! \brief  The COMTraceServer class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef COMTRACESERVER_HPP
#define COMTRACESERVER_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <COM/InprocServer.hpp>
#include <COM/ServerRegInfo.hpp>
#include "TypeLibrary_h.h"
#include "CustomTracer.hpp"
#include "DispatchTracer.hpp"
#include "DualTracer.hpp"

////////////////////////////////////////////////////////////////////////////////
//! The COM server concrete class.

class COMTraceServer : public COM::InprocServer
{
public:
	//! Default constructor.
	COMTraceServer();

	//! Destructor.
	virtual ~COMTraceServer();
	
private:
	//
	// Overriden DllMain methods.
	//

	//! DLL loaded.
	virtual	void OnLoad();

	//! DLL unloading.
	virtual	void OnUnload();

	//! Thread created.
	virtual	void OnThreadAttached();

	//! Thread destroyed.
	virtual	void OnThreadDetached();	

	//
	// Overriden COM entry point methods.
	//

	//! Get the class factory.
	virtual HRESULT DllGetClassObject(REFCLSID roCLSID, REFIID roIID, LPVOID* ppFactory);

	//! Query if the server can be unloaded.
	virtual HRESULT DllCanUnloadNow();

	//! Register the server in the registry.
	virtual HRESULT DllRegisterServer();

	//! Unregister the server from the registry.
	virtual HRESULT DllUnregisterServer();

	//
	// Overriden Server class methods.
	//

	//! Lock the server.
	virtual void Lock();

	//! Unlock the server.
	virtual void Unlock();

	//
	// Overriden InprocServer class methods.
	//

	//! Template Method to get the servers class factory.
	virtual COM::IClassFactoryPtr CreateClassFactory(const CLSID& oCLSID);

	DEFINE_REGISTRATION_TABLE("COMTrace", LIBID_COMTraceLib, 1, 0)
		DEFINE_CLASS_REG_INFO(CLSID_CustomTracer,   "CustomTracer",   "1", COM::SINGLE_THREAD_APT)
		DEFINE_CLASS_REG_INFO(CLSID_DispatchTracer, "DispatchTracer", "1", COM::SINGLE_THREAD_APT)
		DEFINE_CLASS_REG_INFO(CLSID_DualTracer,     "DualTracer",     "1", COM::SINGLE_THREAD_APT)
	END_REGISTRATION_TABLE()

	DEFINE_CLASS_FACTORY_TABLE()
		DEFINE_CLASS(CLSID_CustomTracer,   CustomTracer,   ICustomInterface)
		DEFINE_CLASS(CLSID_DispatchTracer, DispatchTracer, IDispatch)
		DEFINE_CLASS(CLSID_DualTracer,     DualTracer,     IDualInterface)
	END_CLASS_FACTORY_TABLE()
};

////////////////////////////////////////////////////////////////////////////////
// Global variables.

//! The component object.
extern COMTraceServer g_oDll;

#endif // COMTRACESERVER_HPP
