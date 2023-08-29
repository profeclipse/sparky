#include <stdio.h>
#include <cstddef>
#include <iostream>
#include "utils/FileUtils.h"

namespace sparky {
	namespace utils {
		std::string read_file(const char* filepath) {
			FILE* file = fopen(filepath,"r");
			if (!file) {
				// TODO: log error
				std::cout << "failed to open file '" << filepath << "'" << std::endl;
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
}
