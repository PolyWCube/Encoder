#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

#include "algorithm/base64.hpp"
#include "algorithm/rot13.hpp"

enum class EncodeAlgorithm { none, base64, rot13 };

std::string readFileContents(const std::string& filepath) {
	std::ifstream file(filepath, std::ios::binary);
	if (!file.is_open()) {
		std::cerr << "Error: Could not open input file '" << filepath << "'" << std::endl;
		return "";
	}
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

void printHelp(const std::string& program) {
	std::cout << "Usage: " << program << " [source] <flags> [destination]" << std::endl;
	std::cout << std::endl;
	std::cout << "Input Source:" << std::endl;
	std::cout << "  \"<text>\"     : Input text directly from command line (enclose in quotes)" << std::endl;
	std::cout << "  <filepath>   : Path to a file to read input from" << std::endl;
	std::cout << std::endl;
	std::cout << "Flags:" << std::endl;
	std::cout << "  -help        : Display help message" << std::endl;
	std::cout << "  -file_in     : Use file as input in <source>" << std::endl;
	std::cout << "  -base64      : Base64" << std::endl;
	std::cout << "  -rot13       : ROT13 (Caesar cipher variant)" << std::endl;
	std::cout << "  -encode      : Encode mode (default)" << std::endl;
	std::cout << "  -decode      : Decode mode" << std::endl;
	std::cout << std::endl;
	std::cout << "Output Destination (Optional):" << std::endl;
	std::cout << "  <filepath>	: Path to a file to write output to. If omitted, output goes to console." << std::endl;
}

constexpr size_t Hash(const char* string) {
	size_t hash = 0;
	while (*string) {
		hash = hash * 31 + *string++;
	}
	return hash;
}

int main(int count, char* arguments[]) {
	std::string program = arguments[0];

	if (count < 3 && std::string(arguments[1]) == "-help") {
		printHelp(program);
		return 0;
	}

	std::string input = arguments[1];
	std::string inputContent, outputContent;
	bool isReadFromFile = false;

	int index = 1;
	EncodeAlgorithm encodeAlgorithm = EncodeAlgorithm::none;
	bool isEncode = true;

	while (index++ < count - 1) {
		std::string argument = arguments[index];
		switch (Hash(argument.c_str())) {
			case Hash("-file_in") : {
				isReadFromFile = true;
				break;
			} case Hash("-base64") : {
				if (encodeAlgorithm == EncodeAlgorithm::none) {
					encodeAlgorithm = EncodeAlgorithm::base64;
					break;
				} else {
					std::cerr << "Multiple encode flags occured..." << std::endl;
					return 0;
				}
			} case Hash("-rot13") : {
				if (encodeAlgorithm == EncodeAlgorithm::none) {
					encodeAlgorithm = EncodeAlgorithm::rot13;
					break;
				}
				else {
					std::cerr << "Multiple encode flags occured..." << std::endl;
					return 0;
				}
			} case Hash("-encode") : {
				isEncode = true;
				break;
			} case Hash("-decode") : {
				isEncode = false;
				break;
			} default : {
				std::cerr << "Unknown flags..." << std::endl;
				break;
			}
		}
	}

	if (!isReadFromFile) {
		inputContent = input.substr(1, input.length() - 1);
	} else {
		inputContent = readFileContents(input);
		if (inputContent.empty() && input != "") return 1;
	}

	switch (encodeAlgorithm) {
		using namespace Custom::Coder;
		case EncodeAlgorithm::none : {
			std::cerr << "Encode flag not set..." << std::endl;
			break;
		} case EncodeAlgorithm::base64 : {
			outputContent = (isEncode) ? Base64::Encode(inputContent) : Base64::Decode(inputContent);
			break;
		} case EncodeAlgorithm::rot13 : {
			outputContent = Rot13::Convert(inputContent);
			break;
		} default : {
			std::cerr << "Unknown flags..." << std::endl;
			break;
		}
	}
	std::cout << outputContent;

	return 0;
}