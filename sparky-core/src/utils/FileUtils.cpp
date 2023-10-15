#include <stdio.h>
#include <string>
#include "utils/Log.h"

namespace sparky {
	std::string read_file(const char* filepath) {
		FILE* file = fopen(filepath,"r");
		if (!file) {
			SP_ERROR("[read_file] - failed to open file '{}'",filepath);
			return "";
		}

		fseek(file,0,SEEK_END);
		size_t length = ftell(file);
		char* data = new char[length+1];
		memset(data,0,length+1);
		fseek(file,0,SEEK_SET);
		fread(data,1,length,file);
		fclose(file);

		std::string result(data);
		delete[] data;

		return result;
	}
}
