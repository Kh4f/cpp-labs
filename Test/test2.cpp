#include <iostream>
#include <string>
#include <regex>
#include <fstream>
using namespace std;

void printContourCoordinates(const vector<pair<int, int>>& contour) {
    for (size_t i = 0; i < contour.size(); ++i) {
        printf("(%d, %d)", contour[i].first, contour[i].second);
        if (i < contour.size() - 1) {
            cout << ", ";
        }
    }
    cout << "\n";
}

vector<pair<int, int>> getPathFromString(string& str) {
    vector<pair<int, int>> path;

    regex pattern("-?\\d+");
    sregex_iterator it(str.begin(), str.end(), pattern); // итератор начала поиска
    sregex_iterator end; // итератор конца

    while (it != end) {
        pair<int, int> newPair;
        newPair.first = stoi(it->str());
        ++it;
        newPair.second = stoi(it->str());
        ++it;
        path.push_back(newPair);
    }

    return path;
    /*printContourCoordinates(outerPath);*/
}

int main() {

    ifstream file("pathCoords.txt");
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл 'pathCoords.txt'. \n";
        return 1;
    }

    vector<pair<int, int>> outerPath;
    vector<vector<pair<int, int>>> innerPaths;
    string line;

    for (int i = 0; getline(file, line); i++) {
        if (i == 1) {
            // Чтение внешнего контура
            outerPath = getPathFromString(line);
        }
        if (i == 3) {
            // Чтение внутренних контуров
            while (getline(file, line)) {
                innerPaths.push_back(getPathFromString(line));
            }
            break;
        }
    }

    printContourCoordinates(outerPath);

    for (vector<pair<int, int>> innerPath : innerPaths) {
        printContourCoordinates(innerPath);
    }

    file.close();
}
