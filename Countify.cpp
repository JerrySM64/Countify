#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include <cctype>
#include <vector>

int main(int argc, char* argv[]) {
	if (argc < 2 || argc > 3) {
		std::cerr << "Usage: countify <word|line> [filename]" << std::endl;
		return 1;
	}

	std::string mode = argv[1];
	std::ifstream file;
	std::istream* input = &std::cin;

	if (argc == 3) {
		std::string filename = argv[2];
		file.open(filename);
		if (!file.is_open()) {
			std::cerr << "Error: could not open file " << filename << std::endl;
			return 1;
		}
		input = &file;
	}

	if (mode == "word") {
		std::map<std::string, int> word_count;
		std::string line;
		while (std::getline(*input, line)) {
			std::istringstream iss(line);
			std::string word;
			while (iss >> word) {
				std::transform(word.begin(), word.end(), word.begin(), ::tolower);
				word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());
				word_count[word]++;
			}
		}
		for (auto& pair : word_count) {
			std::cout << pair.first << ": " << pair.second << std::endl;
		}
	}
	else if (mode == "line") {
		std::vector<std::string> lines;
		std::string line;
		while (std::getline(*input, line)) {
			lines.push_back(line);
		}
		std::cout << "Number of lines: " << lines.size() << std::endl;
	}
	else if (mode == "char") {
		std::string line;
		int char_count = 0;
		while (std::getline(*input, line)) {
			char_count += line.size();
		}
		std::cout << "Number of characters: " << char_count << std::endl;
	}
	else if (mode == "byte") {
		std::string line;
		int byte_count = 0;
		while (std::getline(*input, line)) {
			byte_count += line.size() + 1;
		}
		std::cout << "Number of bytes: " << byte_count << std::endl;
	}
	else if (mode == "all") {
		std::map<std::string, int> word_count;
		std::vector<std::string> lines;
		std::string line;
		int char_count = 0;
		int byte_count = 0;
		while (std::getline(*input, line)) {
			lines.push_back(line);
			char_count += line.size();
			byte_count += line.size() + 1;
			std::istringstream iss(line);
			std::string word;
			while (iss >> word) {
				std::transform(word.begin(), word.end(), word.begin(), ::tolower);
				word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());
				word_count[word]++;
			}
		}
		std::cout << "Number of lines: " << lines.size() << std::endl;
		std::cout << "Number of characters: " << char_count << std::endl;
		std::cout << "Number of bytes: " << byte_count << std::endl;
		for (auto& pair : word_count) {
			std::cout << pair.first << ": " << pair.second << std::endl;
		}
	}
	else if (mode == "winget") {
		std::vector<std::string> lines;
		std::string line;
		while (std::getline(*input, line)) {
			lines.push_back(line);
		}
		size_t numLines = lines.size();
		numLines = numLines - 2;

		std::cout << "Installed packages via winget: " << numLines << std::endl;
	}
	else if (mode == "help") {
		std::cout << "Usage: countify <word|line|char|byte|all> [filename]" << std::endl;
		std::cout << "all: count the number of lines, characters, bytes, and words in the file" << std::endl;
		std::cout << "byte: count the number of bytes in the file" << std::endl;
		std::cout << "char: count the number of characters in the file" << std::endl;
		std::cout << "line: count the number of lines in the file" << std::endl;
		std::cout << "winget: count the number of installed packages via winget. It removes winget's header so the true package count is shown." << std::endl;
		std::cout << "word: count the number of times each word appears in the file" << std::endl;
		return 0;
	}
	else {
		std::cerr << "Error: invalid mode. Only 'word' and 'line' are implemented at this point." << std::endl;
		return 1;
	}

	if (file.is_open()) {
		file.close();
	}

	return 0;
}
