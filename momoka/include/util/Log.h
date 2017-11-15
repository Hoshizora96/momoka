#pragma once
#include <sstream>

#define MOMOKA_LOG_MAX_LEVEL 5

namespace momoka {
#define MOMOKA_LOG(level) \
	if(level > MOMOKA_LOG_MAX_LEVEL) {} \
	else if (level > ::momoka::Log::GetReportingLevel()) {} \
	else ::momoka::Log::StartLog(__FUNCTION__, level)

	enum LogLevel {
		fatal,
		error,
		warning,
		info,
		verbose,
		debug
	};

	class Log {
		static LogLevel m_reportingLevel_;
		static std::ostream & m_outputStream_;

		static std::string GetNowTime();
		static std::string ToString(const LogLevel& level);
	public:
		static std::ostream& StartLog(char* module, LogLevel level = debug);
		static LogLevel& GetReportingLevel();
		static void SetReportingLevel(const LogLevel& level);
		static void SetReportingLevel(const char* level);
	};
}
