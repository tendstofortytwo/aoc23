#include <fmt/core.h>
#include <fmt/ranges.h>
#include <bits/stdc++.h>

using std::operator""sv;

long getNext(std::vector<long>& sequence) {
	std::vector<long> firsts;
	size_t firstIdx = 0;
	while(true) {
		bool allZero = true;
		long prev = sequence[firstIdx];
		firsts.push_back(prev);
		for(int i = firstIdx+1; i < sequence.size(); ++i) {
			long cur = sequence[i] - prev;
			prev = sequence[i];
			sequence[i] = cur;
			if(cur != 0) allZero = false;
		}
		++firstIdx;
		if(allZero || firstIdx == 0) break;
	}
	long prevRes = 0;
	for(long i = firsts.size() - 1; i >= 0; --i) {
		long res = firsts[i] - prevRes;
		prevRes = res;
	}
	return prevRes;
}

int main() {
	std::string lineStr;

	std::vector<std::vector<long>> patterns;

	while(std::getline(std::cin, lineStr)) {
		std::vector<long> p;
		std::string_view line(lineStr);
		for(const auto & numView : std::views::split(line, ' ')) {
			std::string_view numStr(numView);
			long num;
			std::from_chars(numStr.begin(), numStr.end(), num);
			p.push_back(num);
		}
		patterns.push_back(p);
	}

	long sum = 0;
	for(auto& p : patterns) {
		sum += getNext(p);
	}

	fmt::println("{}", sum);
}
