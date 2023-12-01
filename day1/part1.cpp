#include <fmt/core.h>
#include <string>
#include <iostream>

int main() {
	std::string line;

	int sum = 0;

	while(std::getline(std::cin, line)) {
		int i, start = 0, end = 0;
		for(i = 0; i < line.size(); ++i) {
			if(line[i] >= '0' && line[i] <= '9') {
				start = line[i] - '0';
				break;
			}
		}
		for(i = line.size() - 1; i >= 0; --i) {
			if(line[i] >= '0' && line[i] <= '9') {
				end = line[i] - '0';
				break;
			}
		}
		int n = start*10 + end;
		sum += n;
	}

	fmt::println("{}", sum);
}
