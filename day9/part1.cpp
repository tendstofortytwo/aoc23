#include <fmt/core.h>
#include <bits/stdc++.h>

using std::operator""sv;

long getNext(std::vector<long>& sequence) {
	std::vector<long> lasts;
	size_t lastIdx = sequence.size() - 1;
	while(true) {
		bool allZero = true;
		long next = sequence[lastIdx];
		lasts.push_back(next);
		for(int i = lastIdx - 1; i >= 0; --i) {
			long cur = next - sequence[i];
			next = sequence[i];
			sequence[i] = cur;
			if(cur != 0) allZero = false;
		}
		--lastIdx;
		if(allZero || lastIdx == 0) break;
	}
	long sum = 0;
	for(long l : lasts) {
		sum += l;
	}
	return sum;
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
