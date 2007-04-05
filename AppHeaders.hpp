////////////////////////////////////////////////////////////////////////////////
//! \author Chris Oldwood
//! \file   AppHeaders.hpp
//! \brief  Wrapper include file for all the core headers.

// Check for previous inclusion
#ifndef APPHEADERS_HPP
#define APPHEADERS_HPP

#if _MSC_VER > 1000
#pragma once
#endif

////////////////////////////////////////////////////////////////////////////////
// System headers

#include <Core/Common.hpp>	// Core library headers.
#include "wcl.hpp"			// Windows C++ library.
#include <COM/COM.hpp>		// COM library headers..

////////////////////////////////////////////////////////////////////////////////
// Application headers

#include "COMTraceServer.hpp"

#endif // APPHEADERS_HPP
