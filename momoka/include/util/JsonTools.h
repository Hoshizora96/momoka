#pragma once
#include "extlib/rapidjson/document.h"
#include "extlib/rapidjson/filereadstream.h"
#include <cstdio>
#include "util/Log.h"
#include <string.h>

#pragma warning(disable:4996)

using namespace rapidjson;

inline bool LoadJsonFile(Document& d, const char* filename, bool doLog = true) {
	// �������doLog����ΪAllocConsole()ִ��ǰ�������׼�����д���ݣ�һд����̨�Ͳ�����ˡ�
	// ��Ҳ��֪����ν��������⣬����ܽ���Ͳ��ô���������ˡ�
	FILE* fp = fopen(filename, "rb");
	char readBuffer[65536];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	d.ParseStream(is);
	fclose(fp);
	if(doLog) {
		MOMOKA_LOG(momoka::info) << "Loaded json file: " << filename;
	}
	return true;
}
