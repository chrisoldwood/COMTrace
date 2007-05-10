////////////////////////////////////////////////////////////////////////////////
//! \file   Logger.hpp
//! \brief  The Logger class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef LOGGER_HPP
#define LOGGER_HPP

#if _MSC_VER > 1000
#pragma once
#endif

////////////////////////////////////////////////////////////////////////////////
//! The class used to log the trace events to a file. The logger keeps track of
//! the indent level so that calls can be nested.

class Logger
{
public:
	//! Default constructor.
	Logger();

	//! Destructor.
	~Logger();

	//
	// Properties.
	//

	//! Set the log filename.
	void SetFilename(const std::tstring& strFile);

	//
	// Methods.
	//

	//! Write a non-functional message.
	void LogRawMsg(const char* pszMsg, ...);

	//! Write a function entry message.
	void LogFnEntry(const char* pszMsg, ...);

	//! Write a function parameter message.
	void LogFnParam(const char* pszMsg, ...);

	//! Write a function exit message.
	void LogFnExit(const char* pszMsg, ...);

	////////////////////////////////////////////////////////////////////////////
	//! The helper class used to write the function result code. This is needed
	//! to ensure it is called after all temporary object dtors have fired.

	class ResultWriter
	{
	public:
		//! Destructor.
		~ResultWriter();

		//
		// Members.
		//
		std::tstring	m_strMsg;	//!< The function result message.
	};

private:
	//
	// Members.
	//
	std::tstring	m_strFile;		//!< The trace filename.
	size_t			m_nIndent;		//!< The current indent level.

	//
	// Internal methods.
	//

	//! Write a message to the file.
	void Write(const char* pszPrefix, const tchar* pszMsg);
};

////////////////////////////////////////////////////////////////////////////////
// Global variables.

//! The logger singleton.
extern Logger g_oLogger;

////////////////////////////////////////////////////////////////////////////////
// Helper macros.

//! Log a raw message.
#define LOG_MSG		g_oLogger.LogRawMsg

//! Log the entry to a function.
#define LOG_ENTRY	Logger::ResultWriter rw; g_oLogger.LogFnEntry

//! Log a parameter passed to the function.
#define LOG_PARAM	g_oLogger.LogFnParam

//! Log the value of a local variable or class member.
#define LOG_VAR		g_oLogger.LogFnParam

//! Log the function exit.
#define LOG_EXIT	rw.m_strMsg = CString::Fmt

#endif // LOGGER_HPP
