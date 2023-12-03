#include <fmt/core.h>
#include <string>
#include <iostream>
#include <string_view>
#include <charconv>
#include <vector>
#include <system_error>

struct Num { long int startPos; long int endPos; long int val; };
struct Sym { long int pos; char ch; };

int main() {
	std::string lineStr;

	std::vector<std::vector<Num>> numbers;
	std::vector<std::vector<Sym>> symbols;

	long int lineIdx = 0;
	while(std::getline(std::cin, lineStr)) {
		std::string_view line(lineStr);
		numbers.push_back({});
		symbols.push_back({});
		
		auto ptr = line.begin();
		while(ptr < line.end()) {
			if(*ptr >= '0' && *ptr <= '9') {
				auto end = ptr;
				while(end != line.end()) {
					if(*end < '0' || *end > '9') break;
					++end;
				}
				long int res;
				auto [p, ec] = std::from_chars(ptr, end, res);
				Num val = { ptr - line.begin(), p - line.begin() - 1, res };
				numbers[lineIdx].push_back(val);
				ptr = p;
				continue;
			}
			
			if(*ptr != '.') {
				Sym val = { ptr - line.begin(), *ptr };
				symbols[lineIdx].push_back(val);
			}
			++ptr;
		}

		++lineIdx;
	}

	long int sum = 0;

	for(long int line = 0; line < numbers.size(); ++line) {
		for(const auto& [startPos, endPos, val] : numbers[line]) {
			long int minY = line - 1;
			if(minY < 0) minY = 0;
			long int maxY = line + 1;
			if(maxY >= symbols.size()) maxY = symbols.size() - 1;
			long int minX = startPos - 1;
			long int maxX = endPos + 1;
			bool isPart = false;

			for(long int i = minY; i <= maxY; ++i) {
				for(const auto& [symPos, ch] : symbols[i]) {
					if(minX <= symPos && symPos <= maxX) {
						isPart = true;
						break;
					}
				}
				if(isPart) break;
			}

			if(isPart) {
				sum += val;
			}
			else {
			}
		}
	}
	fmt::println("sum {}", sum);
}
