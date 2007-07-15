////////////////////////////////////////////////////////////////////////////////
//! \file   COMTraceFactory.hpp
//! \brief  The COMTraceFactory class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef COMTRACEFACTORY_HPP
#define COMTRACEFACTORY_HPP

#include <COM/ClassFactory.hpp>
#include <WCL/ComPtr.hpp>

#if _MSC_VER > 1000
#pragma once
#endif

////////////////////////////////////////////////////////////////////////////////
//! The class factory used to wrap to generic class factory so that it can log
//! the calls to its methods.

class COMTraceFactory : public COMTraceObject<IClassFactory>
{
public:
	//! Default constructor.
	COMTraceFactory(const CLSID& rCLSID);

	//! Destructor.
	virtual ~COMTraceFactory();

	DEFINE_INTERFACE_TABLE(IClassFactory)
		IMPLEMENT_INTERFACE(IID_IClassFactory, IClassFactory)
	END_INTERFACE_TABLE()
	IMPLEMENT_IUNKNOWN()

	//
	// IClassFactory methods.
	//

	//! Create an instance object of the class.
	virtual HRESULT COMCALL CreateInstance(IUnknown* pOuter, const IID& rIID, void** ppInterface);

	//! Lock the COM server.
	virtual HRESULT COMCALL LockServer(BOOL fLock);
	
private:
	// Type shorthands.
	typedef WCL::ComPtr<COM::ClassFactory> ClassFactoryPtr;

	//
	// Members.
	//
	ClassFactoryPtr	m_pClassFactory;	//!< The real class factory.
};

#endif // COMTRACEFACTORY_HPP
