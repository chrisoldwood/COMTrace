////////////////////////////////////////////////////////////////////////////////
//! \file   DualTracer.hpp
//! \brief  The DualTracer class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef DUALTRACER_HPP
#define DUALTRACER_HPP

#include <COM/IDispatchImpl.hpp>

#if _MSC_VER > 1000
#pragma once
#endif

////////////////////////////////////////////////////////////////////////////////
//! The tracer object that is accessed through a COM Dual interface. It can be
//! access either via the custom IDualInterface interface or via the automation
//! compatoble IDispatch interface.

class DualTracer : public COMTraceObject<IDualInterface>, COM::IDispatchImpl<DualTracer>
{
public:
	//! Default constructor.
	DualTracer();

	//! Destructor.
	virtual ~DualTracer();
	
	DEFINE_INTERFACE_TABLE(IDualInterface)
		IMPLEMENT_INTERFACE(IID_IDualInterface, IDualInterface)
		IMPLEMENT_INTERFACE(IID_IDispatch,		IDualInterface)
	END_INTERFACE_TABLE()
	IMPLEMENT_IUNKNOWN()

	//
	// IDualInterface methods.
	//

	//! The test method.
	virtual HRESULT COMCALL TestMethod(BSTR bstrInput, BSTR* pbstrOutput);

	//
	// IDispatch methods.
	//

	//! Get the number of type information interfaces supported.
	virtual HRESULT COMCALL GetTypeInfoCount(UINT* pnInfo);

	//! Get the type information for an object.
	virtual HRESULT COMCALL GetTypeInfo(UINT nInfo, LCID dwLCID, ITypeInfo** ppTypeInfo);

	//! Map a number of names to their dispatch IDs.
	virtual HRESULT COMCALL GetIDsOfNames(REFIID rIID, LPOLESTR* aszNames, UINT nNames, LCID dwLCID, DISPID* alMemberIDs);

	//! Invoke a method or access a property.
	virtual HRESULT COMCALL Invoke(DISPID lMemberID, REFIID rIID, LCID dwLCID, WORD wFlags, DISPPARAMS* pParams, VARIANT* pResult, EXCEPINFO* pExcepInfo, UINT* pnArgError);
};

#endif // DUALTRACER_HPP
