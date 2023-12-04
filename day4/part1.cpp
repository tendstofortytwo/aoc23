#include <fmt/core.h>
#include <string>
#include <iostream>
#include <string_view>
#include <ranges>
#include <charconv>
#include <algorithm>
#include <set>

int main() {
	std::string lineStr;
	int sum = 0;
	while(std::getline(std::cin, lineStr)) {
		std::string_view line(lineStr);
		std::set<int> want;
		int score = 0;
		line = line.substr(line.find(':') + 2);
		bool wantDone = false;
		for(const auto& wordRange : std::views::split(line, ' ')) {
			std::string_view word(wordRange);
			if(word == "|") {
				wantDone = true;
				continue;
			}
			if(word == "") {
				continue;
			}
			int num;
			std::from_chars(word.begin(), word.end(), num);
			if(wantDone) {
				if(want.contains(num)) {
					if(score == 0) {
						score = 1;
					}
					else {
						score *= 2;
					}
				}
			}
			else {
				want.insert(num);
			}
		}
		sum += score;
	}
	fmt::println("{}", sum);
}
