#include <fmt/core.h>
#include <string>
#include <iostream>
#include <string_view>
#include <vector>
#include <ranges>
#include <charconv>
#include <algorithm>
#include <set>

struct Card { int count = 1; int winning = 0; };

int main() {
	std::string lineStr;
	std::vector<Card> cards;
	while(std::getline(std::cin, lineStr)) {
		std::string_view line(lineStr);
		Card c;
		std::set<int> want;
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
					++c.winning;
				}
			}
			else {
				want.insert(num);
			}
		}
		cards.push_back(c);
	}
	for(int i = 0; i < cards.size(); ++i) {
		for(int j = 1; j <= cards[i].winning; ++j) {
			cards[i+j].count += cards[i].count;
		}
	}
	int sum = 0;
	for(const auto& c : cards) {
		sum += c.count;
	}
	fmt::println("{}", sum);
}
