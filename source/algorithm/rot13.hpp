#ifndef CUSTOM_ROT13
#define CUSTOM_ROT13

#include <string>
#include <vector>
#include <cctype>

namespace Custom {
	namespace Coder {
		namespace Rot13 {
			std::string Convert(const std::string& input) {
				std::string output = input;
				for (char& character : output) {
					if (character >= 'a' && character <= 'z') {
						character = static_cast<char>((character - 'a' + 13) % 26 + 'a');
					} else if (character >= 'A' && character <= 'Z') {
						character = static_cast<char>((character - 'A' + 13) % 26 + 'A');
					}
				}
				return output;
			}
		}
	}
}

#endif