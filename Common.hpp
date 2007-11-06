////////////////////////////////////////////////////////////////////////////////
//! \file   Common.hpp
//! \brief  Wrapper include file for all the most common header files.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef APP_COMMON_HPP
#define APP_COMMON_HPP

#if _MSC_VER > 1000
#pragma once
#endif

////////////////////////////////////////////////////////////////////////////////
// Application documentation.
//

////////////////////////////////////////////////////////////////////////////////
// System headers.

#include <Core/Common.hpp>		// Core library common headers.
#include <WCL/Common.hpp>		// Windows C++ library common headers.
#include <COM/Common.hpp>		// COM library common headers.

////////////////////////////////////////////////////////////////////////////////
// Application common headers.

#include "Interfaces_h.h"
#include "Logger.hpp"
#include "COMTraceObject.hpp"

#endif // APP_COMMON_HPP
