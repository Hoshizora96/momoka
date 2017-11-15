#pragma once
#include "extlib/rapidjson/document.h"
#include "extlib/rapidjson/filereadstream.h"
#include <cstdio>
#include "util/Log.h"
#include <string.h>

#pragma warning(disable:4996)

inline bool LoadJsonFile(rapidjson::Document& d, const char* filename, bool doLog = true) {
	// 这里参数doLog是因为AllocConsole()执行前不能向标准输出流写数据，一写控制台就不输出了。
	// 我也不知道如何解决这个问题，如果能解决就不用传这个参数了。
	FILE* fp = fopen(filename, "rb");

	if (fp != nullptr) {
		if (doLog) {
			MOMOKA_LOG(momoka::info) << "Loaded json file: " << filename;
		}
	}
	else {
		if (doLog) {
			MOMOKA_LOG(momoka::error) << "Loaded json file: " << filename << "failed!";
		}
		return false;
	}

	char readBuffer[65536];
	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	d.ParseStream(is);
	fclose(fp);

	return true;
}
