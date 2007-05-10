////////////////////////////////////////////////////////////////////////////////
//! \file   CustomTracer.hpp
//! \brief  The CustomTracer class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef CUSTOMTRACER_HPP
#define CUSTOMTRACER_HPP

#if _MSC_VER > 1000
#pragma once
#endif

////////////////////////////////////////////////////////////////////////////////
//! The tracer object that is accessed only through a COM custom interface.

class CustomTracer : public COMTraceObject<ICustomInterface>
{
public:
	//! Default constructor.
	CustomTracer();

	//! Destructor.
	virtual ~CustomTracer();

	DEFINE_INTERFACE_TABLE(ICustomInterface)
		IMPLEMENT_INTERFACE(IID_ICustomInterface, ICustomInterface)
	END_INTERFACE_TABLE()
	IMPLEMENT_IUNKNOWN()

	//
	// ICustomInterface methods.
	//

	//! The test method.
	virtual HRESULT COMCALL TestMethod(BSTR bstrInput, BSTR *pbstrOutput);
	
private:
	//
	// Members.
	//
};

#endif // CUSTOMTRACER_HPP
