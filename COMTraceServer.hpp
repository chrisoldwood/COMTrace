////////////////////////////////////////////////////////////////////////////////
//! \author Chris Oldwood
//! \file   COMTraceServer.hpp
//! \brief  The COMTraceServer class declaration.

// Check for previous inclusion
#ifndef COMTRACESERVER_HPP
#define COMTRACESERVER_HPP

////////////////////////////////////////////////////////////////////////////////
//! The COM server concrete class.

class COMTraceServer : public COM::InprocServer
{
public:
	//! Default constructor.
	COMTraceServer();

	//! Destructor.
	~COMTraceServer();
	
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
};

/******************************************************************************
**
** Global variables.
**
*******************************************************************************
*/

//! The component object.
extern COMTraceServer Dll;

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif // COMTRACESERVER_HPP
