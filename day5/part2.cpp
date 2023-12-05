#include <fmt/core.h>
#include <string>
#include <iostream>
#include <string_view>
#include <ranges>
#include <charconv>
#include <map>
#include <vector>
#include <algorithm>

struct Mapping { long int src; long int dst; long int sz; };
Mapping readMapping(std::string_view line) {
	Mapping m;
	std::from_chars(line.begin(), line.end(), m.dst);
	line = line.substr(line.find(' ') + 1);
	std::from_chars(line.begin(), line.end(), m.src);
	line = line.substr(line.find(' ') + 1);
	std::from_chars(line.begin(), line.end(), m.sz);
	line = line.substr(line.find(' ') + 1);
	return m;
}
auto cmp = [](const Mapping& a, const Mapping& b) { return a.src < b.src; };
long int map(const std::vector<Mapping>& m, long int val) {
	Mapping tmp = {val,val,val};
	auto next = std::upper_bound(m.begin(), m.end(), tmp, cmp);
	if(next == m.begin()) return val;
	--next;
	auto& map = *next;
	if(map.src <= val && val < map.src + map.sz) {
		return map.dst + (val - map.src);
	}
	return val;
}
struct Seed { long int start; long int sz; };

int main() {
	std::vector<std::string> lines;
	std::string lineStr;
	while(std::getline(std::cin, lineStr)) {
		lines.push_back(lineStr);
	}

	long int idx = 0;

	std::vector<Seed> seeds;
	auto line = std::string_view(lines[idx++]).substr(7);
	long int buf[2];
	long int bufIdx = 0;
	for(const auto & numRange : std::views::split(line, ' ')) {
		std::string_view numStr(numRange);
		std::from_chars(numStr.begin(), numStr.end(), buf[bufIdx++]);
		if(bufIdx == 2) {
			seeds.push_back({ buf[0], buf[1] });
			bufIdx = 0;
		}
	}

	idx += 2;
	std::vector<Mapping> seedToSoil;
	while(lines[idx].size() != 0) {
		Mapping m = readMapping(lines[idx++]);
		seedToSoil.push_back(m);
	}
	std::sort(seedToSoil.begin(), seedToSoil.end(), cmp);

	idx += 2;
	std::vector<Mapping> soilToFertilizer;
	while(lines[idx].size() != 0) {
		Mapping m = readMapping(lines[idx++]);
		soilToFertilizer.push_back(m);
	}
	std::sort(soilToFertilizer.begin(), soilToFertilizer.end(), cmp);

	idx += 2;
	std::vector<Mapping> fertilizerToWater;
	while(lines[idx].size() != 0) {
		Mapping m = readMapping(lines[idx++]);
		fertilizerToWater.push_back(m);
	}
	std::sort(fertilizerToWater.begin(), fertilizerToWater.end(), cmp);

	idx += 2;
	std::vector<Mapping> waterToLight;
	while(lines[idx].size() != 0) {
		Mapping m = readMapping(lines[idx++]);
		waterToLight.push_back(m);
	}
	std::sort(waterToLight.begin(), waterToLight.end(), cmp);

	idx += 2;
	std::vector<Mapping> lightToTemperature;
	while(lines[idx].size() != 0) {
		Mapping m = readMapping(lines[idx++]);
		lightToTemperature.push_back(m);
	}
	std::sort(lightToTemperature.begin(), lightToTemperature.end(), cmp);

	idx += 2;
	std::vector<Mapping> temperatureToHumidity;
	while(lines[idx].size() != 0) {
		Mapping m = readMapping(lines[idx++]);
		temperatureToHumidity.push_back(m);
	}
	std::sort(temperatureToHumidity.begin(), temperatureToHumidity.end(), cmp);

	idx += 2;
	std::vector<Mapping> humidityToLocation;
	while(lines[idx].size() != 0) {
		Mapping m = readMapping(lines[idx++]);
		humidityToLocation.push_back(m);
	}
	std::sort(humidityToLocation.begin(), humidityToLocation.end(), cmp);

	long int min = LONG_MAX;
	fmt::println("{} seed ranges", seeds.size());
	idx = 0;
	for(auto [start, sz] : seeds) {
		fmt::println("start: {}, sz: {}, sum: {}", start, sz, start+sz);
		for(long int seed = start; seed < start+sz; ++seed) {
			long int soil = map(seedToSoil, seed);
			long int fertilizer = map(soilToFertilizer, soil);
			long int water = map(fertilizerToWater, fertilizer);
			long int light = map(waterToLight, water);
			long int temperature = map(lightToTemperature, light);
			long int humidity = map(temperatureToHumidity, temperature);
			long int location = map(humidityToLocation, humidity);
			if(location < min) min = location;
		}
		fmt::println("{}", min);
	}

	fmt::println("min {}", min);
}
