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
	auto it = lookup.find("AAA");
	while(it->first != "ZZZ") {
		if(directions[directionIdx] == 'L') {
			it = lookup.find(it->second.left);
		} else {
			it = lookup.find(it->second.right);
		}
		directionIdx = (directionIdx + 1) % directions.size();
		++steps;
	}

	fmt::println("{}", steps);
}
