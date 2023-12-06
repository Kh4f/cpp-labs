#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <regex>
#include <fstream>
using namespace std;

/*
Тема 8: стандартная библиотека шаблонов C++.
15.Для заданного в текстовом файле множества координат точек, описывающих внешний контур объекта и соответствующих ему внутренних контуров (дырок), 
построить оптимальные разрезы от внешнего контура к внутренним. 
Полученная суммарная длина линий разрезов должна быть минимальной. 
Координаты точек всех внутренних контуров в точках разреза включить во внешний контур.
*/


// Вычисление расстояния между двумя точками
double calculateDistance(pair<int, int> point1, pair<int, int> point2) {
	return sqrt(pow(point1.first - point2.first, 2) + pow(point1.second - point2.second, 2));
}

// Вывод координат контура
void printContourCoordinates(const vector<pair<int, int>>& contour) {
	for (size_t i = 0; i < contour.size(); ++i) {
		printf("(%d, %d)", contour[i].first, contour[i].second);
		if (i < contour.size() - 1) {
			cout << ", ";
		}
	}
	cout << "\n";
}

// Построение оптимальных разрезов между внешним и внутренними контурами
double buildOptimalCuts(vector<pair<int, int>>& outerPath, const vector<vector<pair<int, int>>>& innerPaths) {
	int innerPathCounter = 0;
	double sumOfDistances = 0;

	for (const auto& innerPath : innerPaths) {
		double minDistance = numeric_limits<double>::max();
		pair<int, int> outerPathVertex;
		pair<int, int> innerPathVertex;

		cout << "Координаты внешнего контура: \n";
		printContourCoordinates(outerPath);

		printf("Координаты внутреннего контура #%d:\n", ++innerPathCounter);
		printContourCoordinates(innerPath);

		for (const auto& outerPoint : outerPath) {
			for (const auto& innerPoint : innerPath) {
				double distance = calculateDistance(outerPoint, innerPoint);
				if (distance < minDistance) {
					minDistance = distance;
					outerPathVertex = outerPoint;
					innerPathVertex = innerPoint;
				}
			}
		}

		sumOfDistances += minDistance;

		// Добавление точек внутреннего контура во внешний контур.
		for (const auto& innerPoint : innerPath) {
			outerPath.push_back(innerPoint);
		}

		printf("Сделан разрез между точками (%d, %d) и (%d, %d), длина: %f\n\n",
			outerPathVertex.first, outerPathVertex.second,
			innerPathVertex.first, innerPathVertex.second,
			minDistance);
	}

	return sumOfDistances;
}

// Получение контура (множества координат его точек) из строки
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

	double totalCutLength = buildOptimalCuts(outerPath, innerPaths);
	cout << "Суммарная длина линий разрезов: " << totalCutLength << "\n";
}


