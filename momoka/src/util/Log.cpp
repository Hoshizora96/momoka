#include "stdafx.h"
#include "util/Log.h"
#include <ctime>
#include <iostream>
#include <cstdio>
#include <windows.h>

namespace momoka {
	//   0 = ��ɫ      8 = ��ɫ
	//   1 = ��ɫ      9 = ����ɫ
	//   2 = ��ɫ      A = ����ɫ
	//   3 = ǳ��ɫ    B = ��ǳ��ɫ
	//   4 = ��ɫ      C = ����ɫ
	//   5 = ��ɫ      D = ����ɫ
	//   6 = ��ɫ      E = ����ɫ
	//   7 = ��ɫ      F = ����ɫ
	void Log::SetColor(unsigned short forecolor, unsigned short backgroudcolor) {

		HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE); //��ȡ���������
		SetConsoleTextAttribute(hCon, forecolor | backgroudcolor); //�����ı�������ɫ
	}

	LogLevel Log::m_reportingLevel_ = debug;
	std::ostream& Log::m_outputStream_ = std::cout;

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
		case verbose:
			return "VERBOSE";
		case debug:
			return "DEBUG";
		default:
			return "UNKNOWN";
		}
	}

	std::ostream& Log::StartLog(char* module, LogLevel level) {
		SetColor();
		m_outputStream_ << std::endl;
		SetColor(0x3);
		m_outputStream_ << "[" << GetNowTime() << "] ";
		switch (level) {
		case fatal:
			SetColor(0xc);
			break;
		case error:
			SetColor(0xc);
			break;
		case warning:
			SetColor(0xe);
			break;
		case info:
			SetColor(0x9);
			break;
		case verbose:
			SetColor(0x2);
			break;
		case debug:
			SetColor(0xa);
			break;
		default:
			SetColor(0x5);
			break;
		}
		m_outputStream_ << "*" << ToString(level) << "* ";
		SetColor(0x6);
		m_outputStream_ << "[" << module << "] ";
		SetColor();
		return m_outputStream_;
	}

}
