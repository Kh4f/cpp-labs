#include <iostream>
#include <string>

std::string trimToFirstLetter(const std::string& word) {
    // Find the index of the first letter from the left
    size_t leftIndex = 0;
    while (leftIndex < word.length() && !std::isalpha(word[leftIndex])) {
        leftIndex++;
    }

    // Find the index of the first letter from the right
    size_t rightIndex = word.length() - 1;
    while (rightIndex > leftIndex && !std::isalpha(word[rightIndex])) {
        rightIndex--;
    }

    // If there are no letters, return an empty string
    if (leftIndex > rightIndex) {
        return "";
    }

    // Trim the word
    return word.substr(leftIndex, rightIndex - leftIndex + 1);
}

int main() {
    std::string word = "";
    std::string result = trimToFirstLetter(word);
    std::cout << "Result: " << result << std::endl;

    return 0;
}
