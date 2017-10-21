#include "stdafx.h"
#include "util/Log.h"
#include <ctime>
#include <iostream>
#include <cstdio>

namespace momoka {
	LogLevel Log::m_reportingLevel_ = info;
	std::ostream & Log::m_outputStream_ = std::cout;

	LogLevel& Log::GetReportingLevel() {
		return m_reportingLevel_;
	}

	void Log::SetReportingLevel(const LogLevel& level) {
		m_reportingLevel_ = level;
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

	std::ostream& Log::StartLog(LogLevel level) {
		m_outputStream_ << std::endl << "[" << GetNowTime() << "] *" << ToString(level) << "* ";
		return m_outputStream_;
	}
}
