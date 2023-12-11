#include <fmt/core.h>
#include <bits/stdc++.h>

using std::operator""sv;

std::vector<long long> emptyRows, emptyCols;

constexpr long long scaleFactor = 1;

long long distance(long long x1, long long y1, long long x2, long long y2) {
	long long res = std::abs(y2 - y1) + std::abs(x2 - x1);
	auto [minX, maxX] = std::minmax(x1, x2);
	auto [minY, maxY] = std::minmax(y1, y2);
	for(long long i = 0; i < emptyRows.size(); ++i) {
		if(emptyRows[i] > maxY) break;
		if(emptyRows[i] > minY) res += scaleFactor;
	}
	for(long long i = 0; i < emptyCols.size(); ++i) {
		if(emptyCols[i] > maxX) break;
		if(emptyCols[i] > minX) res += scaleFactor;
	}
	return res;
}

int main() {
	std::string lineStr;
	std::vector<std::string> sky; // (x, y) -> sky[y][x]
	std::vector<std::pair<long long, long long>> galaxies;

	while(std::getline(std::cin, lineStr)) {
		sky.push_back(lineStr);
	}
	for(long long y = 0; y < sky.size(); ++y) {
		bool allDots = true;
		for(long long x = 0; x < sky[y].size(); ++x) {
			if(sky[y][x] == '#') {
				allDots = false;
				galaxies.push_back({x, y});
			}
		}
		if(allDots) emptyRows.push_back(y);
	}
	for(long long x = 0; x < sky[0].size(); ++x) {
		bool allDots = true;
		for(long long y = 0; y < sky.size(); ++y) {
			if(sky[y][x] == '#') {
				allDots = false;
				break;
			}
		}
		if(allDots) emptyCols.push_back(x);
	}

	long long sum = 0;
	for(long long i = 0; i < galaxies.size(); ++i) {
		for(long long j = i+1; j < galaxies.size(); ++j) {
			auto [x1, y1] = galaxies[i];
			auto [x2, y2] = galaxies[j];
			sum += distance(x1, y1, x2, y2);
		}
	}

	fmt::println("{}", sum);
}
