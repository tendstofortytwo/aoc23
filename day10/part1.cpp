#include <fmt/core.h>
#include <bits/stdc++.h>

using std::operator""sv;

struct Point { int x, y; char going; };
void maybeAddPoint(
	std::vector<Point>& vec,
	std::vector<std::vector<char>>& grid,
	int x, int y, char going
) {
	if(x < 0 || x >= grid[0].size()) return;
	if(y < 0 || y >= grid.size()) return;
	switch(grid[y][x]) {
	case '|':
		if(going != 'N' && going != 'S') return;
		break;
	case '-':
		if(going != 'E' && going != 'W') return;
		break;
	case 'L':
		if(going != 'W' && going != 'S') return;
		break;
	case 'J':
		if(going != 'E' && going != 'S') return;
		break;
	case '7':
		if(going != 'E' && going != 'N') return;
		break;
	case 'F':
		if(going != 'W' && going != 'N') return;
		break;
	default:
		return;
	}
	vec.push_back({x, y, going});
}

int main() {
	std::string lineStr;

	// at pos (x, y) -> grid[y][x]
	std::vector<std::vector<char>> grid;

	int lineIdx = 0;
	int startX, startY;
	while(std::getline(std::cin, lineStr)) {
		grid.push_back({});
		for(int i = 0; i < lineStr.size(); ++i) {
			grid[lineIdx].push_back(lineStr[i]);
			if(lineStr[i] == 'S') {
				startX = i;
				startY = lineIdx;
			}
		}
		++lineIdx;
	}

	std::vector<Point> points;
	maybeAddPoint(points, grid, startX - 1, startY, 'W');
	maybeAddPoint(points, grid, startX + 1, startY, 'E');
	maybeAddPoint(points, grid, startX, startY - 1, 'N');
	maybeAddPoint(points, grid, startX, startY + 1, 'S');

	int stepsTaken = 0;

	bool foundStart = false;
	while(!foundStart) {
		++stepsTaken;
		for(auto& p : points) {
			switch(grid[p.y][p.x]) {
			case '|': // north south
				if(p.going == 'N') p.y--;
				else p.y++; // going south
				break;
			case '-': // east west
				if(p.going == 'E') p.x++;
				else p.x--; // going west
				break;
			case 'L': // north east
				if(p.going == 'S') {
					p.x++;
					p.going = 'E';
				} else { // entered going west
					p.y--;
					p.going = 'N';
				}
				break;
			case 'J': // north west
				if(p.going == 'S') {
					p.x--;
					p.going = 'W';
				} else { // entered going east
					p.y--;
					p.going = 'N';
				}
				break;
			case '7': // south west
				if(p.going == 'N') {
					p.x--;
					p.going = 'W';
				} else { // entered going east
					p.y++;
					p.going = 'S';
				}
				break;
			case 'F': // south east
				if(p.going == 'N') {
					p.x++;
					p.going = 'E';
				} else { // entered going east
					p.y++;
					p.going = 'S';
				}
				break;
			case '.':
				continue;
			case 'S':
				foundStart = true;
				break;
			};
		}
	}

	fmt::println("{} steps taken in smallest loop", stepsTaken);
	fmt::println("result {}", stepsTaken / 2);
}
