#ifndef CUSTOM_BASE64
#define CUSTOM_BASE64

#include <string>
#include <vector>

namespace Custom {
	namespace Coder {
		namespace Base64 {
			const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
			std::string Encode(const std::string& input) {
				std::string output;
				int a = 0, b = -6;
				for (unsigned char character : input) {
					a = (a << 8) + character;
					b += 8;
					while (b >= 0) {
						output.push_back(characters[(a >> b) & 0x3F]);
						b -= 6;
					}
				}
				if (b > -6) {
					output.push_back(characters[((a << 8) >> (b + 8)) & 0x3F]);
				}
				while (output.size() % 4) {
					output.push_back('=');
				}
				return output;
			}

			std::string Decode(const std::string& input) {
				std::string output;
				std::vector<int> T(256, -1);
				for (int i = 0; i < 64; i++) T[characters[i]] = i;
				int a = 0, b = -8;
				for (unsigned char character : input) {
					if (character == '=') break;
					if (T[character] == -1) continue;
			
					a = (a << 6) + T[character];
					b += 6;
					if (b >= 0) {
						output.push_back(char((a >> b) & 0xFF));
						b -= 8;
					}
				}
				return output;
			}
		}
	}
}

#endif