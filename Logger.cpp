////////////////////////////////////////////////////////////////////////////////
//! \file   Logger.cpp
//! \brief  The Logger class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include <stdio.h>
#include <tchar.h>

//! The number of chars to ident functions by.
const size_t FUNC_INDENT = 4;

//! The number of chars to ident parameters by.
const size_t PARAM_INDENT = 1;

//! The logger singleton.
Logger g_oLogger;

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

Logger::Logger()
	: m_nIndent(0)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

Logger::~Logger()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Set the log filename.

void Logger::SetFilename(const tstring& strFile)
{
	m_strFile = strFile;
}

////////////////////////////////////////////////////////////////////////////////
//! Write a non-functional message.

void Logger::LogRawMsg(const tchar* pszMsg, ...)
{
	ASSERT(pszMsg != nullptr);

	va_list	args;
	va_start(args, pszMsg);

	Write(TXT(""), CString::FmtEx(pszMsg, args));

	va_end(args);
}

////////////////////////////////////////////////////////////////////////////////
//! Write a function entry message.

void Logger::LogFnEntry(const tchar* pszMsg, ...)
{
	ASSERT(pszMsg != nullptr);

	va_list	args;
	va_start(args, pszMsg);

	Write(tstring(m_nIndent, ' ').c_str(), CString::FmtEx(pszMsg, args));

	va_end(args);

	m_nIndent += FUNC_INDENT;
}

////////////////////////////////////////////////////////////////////////////////
//! Write a function parameter message.

void Logger::LogFnParam(const tchar* pszMsg, ...)
{
	ASSERT(pszMsg != nullptr);

	va_list	args;
	va_start(args, pszMsg);

	Write(tstring(m_nIndent-FUNC_INDENT+PARAM_INDENT, ' ').c_str(), CString::FmtEx(pszMsg, args));

	va_end(args);
}

////////////////////////////////////////////////////////////////////////////////
//! Write a function exit message.

void Logger::LogFnExit(const tchar* pszMsg, ...)
{
	ASSERT(pszMsg != nullptr);

	m_nIndent -= FUNC_INDENT;

	va_list	args;
	va_start(args, pszMsg);

	Write(tstring(m_nIndent, ' ').c_str(), CString::FmtEx(pszMsg, args));

	va_end(args);

	if (m_nIndent == 0)
		Write(TXT(""), TXT(""));
}

////////////////////////////////////////////////////////////////////////////////
//! Write a message to the file.

void Logger::Write(const tchar* pszPrefix, const tchar* pszMsg)
{
	ASSERT(pszPrefix != nullptr);
	ASSERT(pszMsg    != nullptr);
	ASSERT(!m_strFile.empty());

	// Open the file for appending.
	FILE* pLogFile = _tfopen(m_strFile.c_str(), TXT("a"));

	if (pLogFile != NULL)
	{
		// Write the message and close.
		fputs(T2A(pszPrefix), pLogFile);
		fputs(T2A(pszMsg),    pLogFile);
		fputs("\n",           pLogFile);

		fclose(pLogFile);
	}

	// Write to the debugger output.
	::OutputDebugString(pszPrefix);
	::OutputDebugString(pszMsg);
	::OutputDebugString(TXT("\n"));
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor. Write the function result message.

Logger::ResultWriter::~ResultWriter()
{
	ASSERT(!m_strMsg.empty());

	g_oLogger.LogFnExit(TXT("%s"), m_strMsg.c_str());
}
