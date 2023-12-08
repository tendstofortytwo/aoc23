#include <fmt/core.h>
#include <bits/stdc++.h>

using std::operator""sv;

struct Node { size_t left; size_t right; };
struct NodeStr { std::string left; std::string right; };

int main() {
	std::string directions;
	std::getline(std::cin, directions);

	std::string lineStr;
	// blank line
	std::getline(std::cin, lineStr);

	std::vector<std::string> curs;
	std::vector<Node> lookup;
	std::vector<NodeStr> lookupStr;

	while(std::getline(std::cin, lineStr)) {
		std::string cur = lineStr.substr(0, 3);
		std::string left = lineStr.substr(7, 3);
		std::string right = lineStr.substr(12, 3);
		curs.push_back(cur);
		lookupStr.push_back({left, right});
	}
	for(size_t i = 0; i < curs.size(); ++i) {
		size_t left, right;
		for(size_t j = 0; j < curs.size(); ++j) {
			if(curs[j] == lookupStr[i].left) {
				left = j;
			}
			if(curs[j] == lookupStr[i].right) {
				right = j;
			}
		}
		lookup.push_back({ left, right });
	}

	size_t directionIdx = 0;
	size_t steps = 0;
	std::vector<size_t> its;
	for(size_t i = 0; i < curs.size(); ++i) {
		if(curs[i][2] == 'A') {
			its.push_back(i);
		}
	}
	fmt::println("{} iterators", its.size());
	while(true) {
		bool allZ = true;
		for(auto& it : its) {
			if(directions[directionIdx] == 'L') {
				it = lookup[it].left;
			} else {
				it = lookup[it].right;
			}
			if(curs[it][2] != 'Z') allZ = false;
		}
		directionIdx = (directionIdx + 1) % directions.size();
		++steps;
		if(steps % 10000000 == 0) fmt::println("{} steps", steps);
		if(allZ) break;
	}

	fmt::println("{}", steps);
}
