////////////////////////////////////////////////////////////////////////////////
//! \file   COMTraceObject.hpp
//! \brief  The COMTraceObject class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef COMTRACEOBJECT_HPP
#define COMTRACEOBJECT_HPP

#include <COM/ComUtils.hpp>

#if _MSC_VER > 1000
#pragma once
#endif

////////////////////////////////////////////////////////////////////////////////
//! The ObjectBase Decorator used to log the IUnknown calls.

template<typename T>
class COMTraceObject : public COM::ObjectBase<T>
{
public:
	//! Default constructor.
	COMTraceObject(const tstring& strClass);

	//! Destructor.
	virtual ~COMTraceObject();
	
	//
	// IUnknown wrapped methods.
	//

	//! Query the object for a particular interface.
	virtual HRESULT QueryInterfaceImpl(const IID& rIID, void** ppInterface);
    
	//! Increment the objects reference count.
	virtual ULONG AddRefImpl();
    
	//! Decrement the objects reference count.
	virtual ULONG ReleaseImpl();

	//
	// ISupportErrorInfo methods.
	//

	//! Queries if the interface supports COM exceptiopns.
	virtual HRESULT InterfaceSupportsErrorInfoImpl(const IID& rIID);

private:
	//
	// Members.
	//
	tstring	m_strClass;		//!< The name of the COM implementation class.
};

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

template<typename T>
inline COMTraceObject<T>::COMTraceObject(const tstring& strClass)
	: m_strClass(strClass)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

template<typename T>
inline COMTraceObject<T>::~COMTraceObject()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Query the object for a particular interface.

template<typename T>
inline HRESULT COMTraceObject<T>::QueryInterfaceImpl(const IID& rIID, void** ppInterface)
{
	tstring strIID       = COM::FormatGUID(rIID);
	tstring strIFaceName = COM::LookupIID(rIID);

	LOG_ENTRY(TXT("%s::QueryInterface(IID)"), m_strClass.c_str());
	LOG_PARAM(TXT("IID=%s [%s]"), strIID.c_str(), strIFaceName.c_str());

	HRESULT hr = COM::ObjectBase<T>::QueryInterfaceImpl(rIID, ppInterface);

	LOG_EXIT(TXT("HRESULT=0x%08X [%s]"), hr, CStrCvt::FormatError(hr));

	return hr;
}

////////////////////////////////////////////////////////////////////////////////
//! Increment the objects reference count.

template<typename T>
inline ULONG COMTraceObject<T>::AddRefImpl()
{
	LOG_ENTRY(TXT("%s::AddRef()"), m_strClass.c_str());

	ULONG nRefCount = COM::ObjectBase<T>::AddRefImpl();

	LOG_EXIT (TXT("ULONG=%u"), nRefCount);

	return nRefCount;
}

////////////////////////////////////////////////////////////////////////////////
//! Decrement the objects reference count.

template<typename T>
inline ULONG COMTraceObject<T>::ReleaseImpl()
{
	LOG_ENTRY(TXT("%s::Release()"), m_strClass.c_str());

	ULONG nRefCount = COM::ObjectBase<T>::ReleaseImpl();

	LOG_EXIT (TXT("ULONG=%u"), nRefCount);

	return nRefCount;
}

////////////////////////////////////////////////////////////////////////////////
//! Queries if the interface supports COM exceptiopns.

template<typename T>
inline HRESULT COMTraceObject<T>::InterfaceSupportsErrorInfoImpl(const IID& rIID)
{
	tstring strIID       = COM::FormatGUID(rIID);
	tstring strIFaceName = COM::LookupIID(rIID);

	LOG_ENTRY(TXT("%s::InterfaceSupportsErrorInfoImpl()"), m_strClass.c_str());
	LOG_PARAM(TXT("IID=%s [%s]"), strIID.c_str(), strIFaceName.c_str());

	HRESULT hr = COM::ObjectBase<T>::InterfaceSupportsErrorInfoImpl(rIID);

	LOG_EXIT(TXT("HRESULT=0x%08X [%s]"), hr, CStrCvt::FormatError(hr));

	return hr;
}

#endif // COMTRACEOBJECT_HPP
