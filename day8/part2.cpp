#include <fmt/core.h>
#include <bits/stdc++.h>

using std::operator""sv;

struct Node { std::string left; std::string right; };

int main() {
	std::string directions;
	std::getline(std::cin, directions);

	std::string lineStr;
	// blank line
	std::getline(std::cin, lineStr);

	std::unordered_map<std::string, Node> lookup;

	while(std::getline(std::cin, lineStr)) {
		std::string cur = lineStr.substr(0, 3);
		std::string left = lineStr.substr(7, 3);
		std::string right = lineStr.substr(12, 3);
		lookup.insert({cur, {left, right}});
	}

	size_t directionIdx = 0;
	size_t steps = 0;
	std::vector<decltype(lookup)::const_iterator> its;
	for(auto it = lookup.cbegin(); it != lookup.cend(); ++it) {
		if(it->first[2] == 'A') {
			its.push_back(it);
		}
	}
	fmt::println("{} iterators", its.size());
	while(true) {
		bool allZ = true;
		for(auto& it : its) {
			if(directions[directionIdx] == 'L') {
				it = lookup.find(it->second.left);
			} else {
				it = lookup.find(it->second.right);
			}
			if(it->first[2] != 'Z') allZ = false;
		}
		directionIdx = (directionIdx + 1) % directions.size();
		++steps;
		if(steps % 1000000 == 0) fmt::println("{} steps", steps);
		if(allZ) break;
	}

	fmt::println("{}", steps);
}
