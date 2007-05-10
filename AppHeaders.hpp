////////////////////////////////////////////////////////////////////////////////
//! \file   AppHeaders.hpp
//! \brief  Wrapper include file for all the core headers.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef APPHEADERS_HPP
#define APPHEADERS_HPP

#if _MSC_VER > 1000
#pragma once
#endif

////////////////////////////////////////////////////////////////////////////////
// Application documentation
//
//! \namespace COMTraceLib
//! \brief     The type library namespace.

////////////////////////////////////////////////////////////////////////////////
// System headers

#include <Core/Common.hpp>		// Core library common headers.
#include <WCL/wcl.hpp>			// Windows C++ library.
#include <COM/COM.hpp>			// COM library.

////////////////////////////////////////////////////////////////////////////////
// Application headers

#include "Interfaces_h.h"
#include "Logger.hpp"
#include "COMTraceObject.hpp"
#include "CustomTracer.hpp"
#include "DispatchTracer.hpp"
#include "DualTracer.hpp"
#include "COMTraceServer.hpp"
#include "COMTraceFactory.hpp"

#endif // APPHEADERS_HPP
