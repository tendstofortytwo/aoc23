#include <fmt/core.h>
#include <fmt/ranges.h>
#include <bits/stdc++.h>

using std::operator""sv;

/*
solution rationale because I *will* forget:

1. flag all the grid squares that are part of the loop
2. maintain a flag "inLoop" that flips whenever you go from outside the maze
   to inside the maze or vice-versa
3. flip inLoop whenever I cross a | or F---J or L---7, with obviously any number
   of dashes between them
4. if a square is not part of the loop and inLoop is true, increment the result
   counter
*/

struct Point { int x, y, origX, origY; char going, origGoing; };
bool maybeAddPoint(
	std::vector<Point>& vec,
	std::vector<std::vector<char>>& grid,
	int x, int y, char going
) {
	if(x < 0 || x >= grid[0].size()) return false;
	if(y < 0 || y >= grid.size()) return false;
	switch(grid[y][x]) {
	case '|':
		if(going != 'N' && going != 'S') return false;
		break;
	case '-':
		if(going != 'E' && going != 'W') return false;
		break;
	case 'L':
		if(going != 'W' && going != 'S') return false;
		break;
	case 'J':
		if(going != 'E' && going != 'S') return false;
		break;
	case '7':
		if(going != 'E' && going != 'N') return false;
		break;
	case 'F':
		if(going != 'W' && going != 'N') return false;
		break;
	default:
		return false;
	}
	vec.push_back({x, y, x, y, going, going});
	return true;
}

void movePoint(Point& p, std::vector<std::vector<char>>& grid) {
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
	};
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
	bool sw = maybeAddPoint(points, grid, startX - 1, startY, 'W');
	bool se = maybeAddPoint(points, grid, startX + 1, startY, 'E');
	bool sn = maybeAddPoint(points, grid, startX, startY - 1, 'N');
	bool ss = maybeAddPoint(points, grid, startX, startY + 1, 'S');

	Point mainGridPoint;

	bool foundStart = false;
	while(!foundStart) {
		for(auto& p : points) {
			if(grid[p.y][p.x] =='S') {
				foundStart = true;
				mainGridPoint.x = p.origX;
				mainGridPoint.y = p.origY;
				mainGridPoint.going = p.origGoing;
				break;
			}
			movePoint(p, grid);
		}
	}

	foundStart = false;
	while(!foundStart) {
		char& c = grid[mainGridPoint.y][mainGridPoint.x];
		if(c == 'S') foundStart = true;
		movePoint(mainGridPoint, grid);
		c |= 0x80; // set top bit to indicate this is in maze
	}

	if(sn && ss) grid[startY][startX] = '|' | 0x80;
	if(se && sw) grid[startY][startX] = '-' | 0x80;
	if(sn && se) grid[startY][startX] = 'L' | 0x80;
	if(sn && sw) grid[startY][startX] = 'J' | 0x80;
	if(ss && sw) grid[startY][startX] = '7' | 0x80;
	if(ss && se) grid[startY][startX] = 'F' | 0x80;

	std::vector<Point> inPoints;

	bool inLoop = false;
	char onLine = '\0';
	int inCount = 0;
	for(int i = 0; i < grid.size(); ++i) {
		const auto& v = grid[i];
		for(int j = 0; j < v.size(); ++j) {
			char c = v[j];
			if(c & 0x80) {
				switch(c & 0x7f) {
				case '|':
					inLoop = !inLoop;
					break;
				case 'L':
				case 'F':
					onLine = (c & 0x7f);
					break;
				case '7':
					if(onLine) {
						if(onLine == 'L') {
							inLoop = !inLoop;
						}
						onLine = '\0';
					}
					break;
				case 'J':
					if(onLine) {
						if(onLine == 'F') {
							inLoop = !inLoop;
						}
						onLine = '\0';
					}
					break;
				}
			} else if(inLoop) {
				++inCount;
				inPoints.push_back({j, i, j, i, c, c});
			}
		}
	}

	fmt::println("{}", inCount);
}

