#include <iostream>
#include <regex>
#include <vector>
#include <fstream>
#include <set>

bool hasMoreVowels(std::string &word) {
    int vowelCount = 0;
    int consonantCount = 0;
    if (word.size() > 30) {
        word = word.substr(0, 30);
    }
    for (char c : word) {
        // in order not to check upper case cases
        char lc = std::tolower(c);
        if (std::isalpha(c)) {
            if (lc == 'a' || lc == 'e' || lc == 'i' || lc == 'o' || lc == 'u') {
                vowelCount++;
            } else {
                consonantCount++;
            }
        }
    }

    return vowelCount > consonantCount;
}

std::vector<std::string> selectWordsWithMoreVowels(const std::string &text) {
    std::vector<std::string> selectedWords;
    std::regex wordRegex(R"(\b[a-zA-Z]+\b)");
    std::sregex_iterator it(text.begin(), text.end(), wordRegex);
    std::sregex_iterator end;

    while (it != end) {
        std::string word = it->str();
        if (hasMoreVowels(word)) {
            selectedWords.push_back(word);
        }
        ++it;
    }

    return selectedWords;
}

void processFile(const std::string& filename) {
    std::ifstream inputFile(filename);

    if (!inputFile) {
        std::cerr << "Failed to open the input file." << std::endl;
        return;
    }

    std::string line;
    std::set<std::string> uniqueWords;
    while (std::getline(inputFile, line)) {
        std::vector<std::string> selectedWords = selectWordsWithMoreVowels(line);
        for (const std::string &word : selectedWords) {
            uniqueWords.insert(word);
        }
    }

    inputFile.close();

    for (const std::string &word : uniqueWords) {
        std::cout << word << std::endl;
    }
}

int main() {
    std::string path = "/Users/maksymkhodakov/CLionProjects/SysProgLab1/";
    std::string inputTexts[] = {"input1.txt", "input2.txt", "input3.txt"};
    for (const auto& test : inputTexts) {
        std::string filename = path + test;
        std::cout << "Start processing file: " << test << std::endl;
        processFile(filename);
        std::cout << "Finish processing file: " << test << std::endl;
    }

    return 0;
}
