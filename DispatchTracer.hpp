////////////////////////////////////////////////////////////////////////////////
//! \file   DispatchTracer.hpp
//! \brief  The DispatchTracer class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef DISPATCHTRACER_HPP
#define DISPATCHTRACER_HPP

#if _MSC_VER > 1000
#pragma once
#endif

////////////////////////////////////////////////////////////////////////////////
//! The tracer object that is accessed only through the automation compatible
//! IDispatch interface. This is a pure IDispatch implementation.


class DispatchTracer : public COMTraceObject<IDispatch>
{
public:
	//! Default constructor.
	DispatchTracer();

	//! Destructor.
	virtual ~DispatchTracer();
	
	DEFINE_INTERFACE_TABLE(IDispatch)
		IMPLEMENT_INTERFACE(IID_IDispatch, IDispatch)
	END_INTERFACE_TABLE()
	IMPLEMENT_IUNKNOWN()

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

private:
	//
	// Members.
	//

	//! The DISPIDs of the methods.
	//  NB: These should match the IDL.
	enum MethodID
	{
		ID_TESTMETHOD	= 1,
	};

	//
	// Internal methods.
	//

	//! The test method.
	BSTR TestMethod(BSTR bstrInput);
};

#endif // DISPATCHTRACER_HPP
