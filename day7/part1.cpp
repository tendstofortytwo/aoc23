#include <fmt/core.h>
#include <bits/stdc++.h>

using std::operator""sv;

enum Type {
	HighCard, OnePair, TwoPair, ThreeOfKind, FullHouse, FourOfKind, FiveOfKind
};

struct Hand {
	Type type = HighCard;
	int deck[5];
	int bet = 0;
};

Hand makeHand(std::string_view line) {
	Hand h;
	std::unordered_map<int, int> count;
	for(int i = 0; i < 5; ++i) {
		switch(line[i]) {
			case 'A': h.deck[i] = 14; break;
			case 'K': h.deck[i] = 13; break;
			case 'Q': h.deck[i] = 12; break;
			case 'J': h.deck[i] = 11; break;
			case 'T': h.deck[i] = 10; break;
			default:  h.deck[i] = line[i] - '0';
		};
		if(count.contains(h.deck[i])) count.at(h.deck[i])++;
		else count.insert({h.deck[i], 1});
	}
	if(count.size() == 1) {
		h.type = FiveOfKind;
	} else if(count.size() == 2) {
		switch(count.begin()->second) {
			case 1: case 4: h.type = FourOfKind; break;
			case 2: case 3: h.type = FullHouse; break;
		};
	} else if(count.size() == 3) {
		bool three = false;
		for(auto it = count.begin(); it != count.end(); ++it) {
			if(it->second == 3) {
				three = true;
				break;
			}
		}
		h.type = three ? ThreeOfKind : TwoPair;
	} else if(count.size() == 4) {
		h.type = OnePair;
	}
	std::from_chars(line.begin() + 6, line.end(), h.bet);
	return h;
}

int main() {
	std::string lineStr;

	std::vector<Hand> hands;

	while(std::getline(std::cin, lineStr)) {
		std::string_view line(lineStr);
		hands.push_back(makeHand(line));
	}

	std::sort(hands.begin(), hands.end(), [](auto& x, auto& y) {
		if(x.type > y.type) return true;
		if(x.type < y.type) return false;
		for(int i = 0; i < 5; ++i) {
			if(x.deck[i] > y.deck[i]) return true;
			if(x.deck[i] < y.deck[i]) return false;
		}
		return false; // should never happen
	});

	long sum = 0;
	for(int i = 0; i < hands.size(); ++i) {
		sum += hands[i].bet * (hands.size() - i);
	}

	fmt::println("{}", sum);
}
