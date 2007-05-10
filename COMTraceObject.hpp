////////////////////////////////////////////////////////////////////////////////
//! \file   COMTraceObject.hpp
//! \brief  The COMTraceObject class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef COMTRACEOBJECT_HPP
#define COMTRACEOBJECT_HPP

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
	COMTraceObject(const std::tstring& strClass);

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

private:
	//
	// Members.
	//
	std::tstring	m_strClass;		//!< The name of the COM implementation class.
};

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

template<typename T>
inline COMTraceObject<T>::COMTraceObject(const std::tstring& strClass)
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
	std::tstring strIID       = COM::FormatGUID(rIID);
	std::tstring strIFaceName = COM::LookupIID(rIID);

	LOG_ENTRY("%s::QueryInterface(IID)", m_strClass.c_str());
	LOG_PARAM("IID=%s [%s]", strIID.c_str(), strIFaceName.c_str());

	HRESULT hr = COM::ObjectBase<T>::QueryInterfaceImpl(rIID, ppInterface);

	LOG_EXIT("HRESULT=0x%08X [%s]", hr, CStrCvt::FormatError(hr));

	return hr;
}

////////////////////////////////////////////////////////////////////////////////
//! Increment the objects reference count.

template<typename T>
inline ULONG COMTraceObject<T>::AddRefImpl()
{
	LOG_ENTRY("%s::AddRef()", m_strClass.c_str());

	ULONG nRefCount = COM::ObjectBase<T>::AddRefImpl();

	LOG_EXIT ("ULONG=%u", nRefCount);

	return nRefCount;
}

////////////////////////////////////////////////////////////////////////////////
//! Decrement the objects reference count.

template<typename T>
inline ULONG COMTraceObject<T>::ReleaseImpl()
{
	LOG_ENTRY("%s::Release()", m_strClass.c_str());

	ULONG nRefCount = COM::ObjectBase<T>::ReleaseImpl();

	LOG_EXIT ("ULONG=%u", nRefCount);

	return nRefCount;
}

#endif // COMTRACEOBJECT_HPP
