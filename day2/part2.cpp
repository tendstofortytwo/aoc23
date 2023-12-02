#include <fmt/core.h>
#include <string>
#include <iostream>
#include <unordered_map>
#include <string_view>
#include <charconv>
#include <ranges>
#include <vector>

using std::operator""sv;

struct Hand {
	int red = 0;
	int green = 0;
	int blue = 0;
};

int parseInt(std::string_view str) {
	int res;
	std::from_chars(str.data(), str.data() + str.size(), res);
	return res;
}

int main() {
	std::string lineStr;

	int sum = 0;

	while(std::getline(std::cin, lineStr)) {
		std::string_view line(lineStr);
		size_t colonIdx = line.find(':');

		int gameId = parseInt(line.substr(5, colonIdx));
		line = line.substr(colonIdx + 2);
		Hand maxHand;

		for(const auto& hand : std::views::split(line, "; "sv)) {
			Hand h;
			for(const auto& cv : std::views::split(hand, ", "sv)) {
				std::string_view c(cv);
				size_t spaceIdx = c.find(' ');
				int count = parseInt(c.substr(0, spaceIdx));
				std::string_view color = c.substr(spaceIdx+1);
				if(color == "red") {
					h.red += count;
					if(count > maxHand.red) maxHand.red = count;
				}
				else if(color == "blue") {
					h.blue += count;
					if(count > maxHand.blue) maxHand.blue = count;
				}
				else {
					h.green += count;
					if(count > maxHand.green) maxHand.green = count;
				}
			}
		}

		sum += maxHand.red * maxHand.green * maxHand.blue;
	}

	fmt::println("{}", sum);
}
