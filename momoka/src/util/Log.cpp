#include "stdafx.h"
#include "util/Log.h"
#include <ctime>
#include <iostream>
#include <cstdio>

namespace momoka {
	LogLevel Log::m_reportingLevel_ = debug;
	std::ostream & Log::m_outputStream_ = std::cout;

	LogLevel& Log::GetReportingLevel() {
		return m_reportingLevel_;
	}
	void Log::SetReportingLevel(const LogLevel& level) {
		m_reportingLevel_ = level;
	}

	void Log::SetReportingLevel(const char* level) {
		if (!strcmp(level, "debug")) m_reportingLevel_ = debug;
		else if (!strcmp(level, "fatal")) m_reportingLevel_ = fatal;
		else if (!strcmp(level, "error")) m_reportingLevel_ = error;
		else if (!strcmp(level, "warning")) m_reportingLevel_ = warning;
		else if (!strcmp(level, "info")) m_reportingLevel_ = info;
		else if (!strcmp(level, "verbose")) m_reportingLevel_ = verbose;
		else m_reportingLevel_ = info;
	}

	std::string Log::GetNowTime() {
		std::stringstream ss;
		struct tm t;
		time_t now; 
		time(&now); 
		localtime_s(&t, &now); 

		char mbstr[100];
		std::fill_n(mbstr, 100, 0);

		if (std::strftime(mbstr, 100, "%H:%M:%S", &t)) {
			ss << mbstr;
		}
		return ss.str();
	}

	std::string Log::ToString(const LogLevel& level) {
		switch (level) {
		case fatal:
			return "FATAL";
		case error:
			return "ERROR";
		case warning:
			return "WARNING";
		case info:
			return "INFO";
		case debug:
			return "DEBUG";
		case verbose:
			return "VERBOSE";
		default:
			return "UNKNOWN";
		}
	}

	std::ostream& Log::StartLog(char* module, LogLevel level) {
		m_outputStream_ << std::endl << "[" << GetNowTime() << "] *" << ToString(level) << "* " << "[" << module << "] ";
		return m_outputStream_;
	}

}
