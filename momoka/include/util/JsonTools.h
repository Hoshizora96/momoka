#pragma once
#include "extlib/rapidjson/document.h"
#include "extlib/rapidjson/filereadstream.h"
#include <cstdio>
#include "util/Log.h"
#include <string.h>

#pragma warning(disable:4996)

inline bool LoadJsonFile(rapidjson::Document& d, const char* filename, bool doLog = true) {
	// �������doLog����ΪAllocConsole()ִ��ǰ�������׼�����д���ݣ�һд����̨�Ͳ�����ˡ�
	// ��Ҳ��֪����ν��������⣬����ܽ���Ͳ��ô���������ˡ�
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
