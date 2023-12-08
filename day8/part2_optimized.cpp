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

	std::vector<size_t> its;
	std::vector<size_t> steps;
	for(size_t i = 0; i < curs.size(); ++i) {
		if(curs[i][2] == 'A') {
			its.push_back(i);
		}
	}
	for(size_t i = 0; i < its.size(); ++i) {
		steps.push_back(0);
		size_t directionIdx = 0;
		while(true) {
			bool allZ = true;
			if(directions[directionIdx] == 'L') {
				its[i] = lookup[its[i]].left;
			} else {
				its[i] = lookup[its[i]].right;
			}
			if(curs[its[i]][2] != 'Z') allZ = false;
			directionIdx = (directionIdx + 1) % directions.size();
			++steps[i];
			if(allZ) break;
		}
	}

	size_t prod = 1;
	for(auto& s : steps) {
		prod = std::lcm(prod, s);
	}

	fmt::println("{}", prod);
}
