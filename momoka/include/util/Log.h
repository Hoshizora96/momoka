#pragma once
#include <sstream>

#define MOMOKA_LOG_MAX_LEVEL 5

namespace momoka {
#define COLOR_NONE            "\033[0m"
#define FONT_COLOR_RED        "\033[0;31m"
#define FONT_COLOR_YELLOW     "\033[1;33m"
#define BACKGROUND_COLOR_RED  "\033[41m"
#define BG_RED_FONT_YELLOW    "\033[41;33m"

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
		static std::ostream& m_outputStream_;

		static std::string GetNowTime();
		static std::string ToString(const LogLevel& level);
		static void SetColor(unsigned short forecolor = 0x7, unsigned short backgroudcolor = 0);
	public:
		static std::ostream& StartLog(char* module, LogLevel level = debug);
		static LogLevel& GetReportingLevel();
		static void SetReportingLevel(const LogLevel& level);
		static void SetReportingLevel(const char* level);
	};
}
