#pragma once

#include <string>
#include <sstream>
#include <vector>

namespace sparky {
	inline std::vector<std::string> splitString(const std::string& s,char delimiter) {
		std::vector<std::string> elems;
		std::stringstream ss(s);
		std::string item;

		while (std::getline(ss,item,delimiter)) {
			elems.push_back(item);
		}

		return elems;
	}
}
