#include <fmt/core.h>
#include <string>
#include <iostream>
#include <string_view>
#include <ranges>
#include <charconv>
#include <set>
#include <map>
#include <vector>

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
long int map(std::map<long int, Mapping> m, long int val) {
	auto next = m.upper_bound(val);
	if(next == m.begin()) return val;
	--next;
	auto& map = next->second;
	if(map.src <= val && val < map.src + map.sz) {
		return map.dst + (val - map.src);
	}
	return val;
}

int main() {
	std::vector<std::string> lines;
	std::string lineStr;
	while(std::getline(std::cin, lineStr)) {
		lines.push_back(lineStr);
	}

	long int idx = 0;

	std::set<long int> seeds;
	auto line = std::string_view(lines[idx++]).substr(7);
	for(const auto & numRange : std::views::split(line, ' ')) {
		std::string_view numStr(numRange);
		long int res;
		std::from_chars(numStr.begin(), numStr.end(), res);
		seeds.insert(res);
	}

	idx += 2;
	std::map<long int, Mapping> seedToSoil;
	while(lines[idx].size() != 0) {
		Mapping m = readMapping(lines[idx++]);
		seedToSoil.insert({m.src, m});
	}

	idx += 2;
	std::map<long int, Mapping> soilToFertilizer;
	while(lines[idx].size() != 0) {
		Mapping m = readMapping(lines[idx++]);
		soilToFertilizer.insert({m.src, m});
	}

	idx += 2;
	std::map<long int, Mapping> fertilizerToWater;
	while(lines[idx].size() != 0) {
		Mapping m = readMapping(lines[idx++]);
		fertilizerToWater.insert({m.src, m});
	}

	idx += 2;
	std::map<long int, Mapping> waterToLight;
	while(lines[idx].size() != 0) {
		Mapping m = readMapping(lines[idx++]);
		waterToLight.insert({m.src, m});
	}

	idx += 2;
	std::map<long int, Mapping> lightToTemperature;
	while(lines[idx].size() != 0) {
		Mapping m = readMapping(lines[idx++]);
		lightToTemperature.insert({m.src, m});
	}

	idx += 2;
	std::map<long int, Mapping> temperatureToHumidity;
	while(lines[idx].size() != 0) {
		Mapping m = readMapping(lines[idx++]);
		temperatureToHumidity.insert({m.src, m});
	}

	idx += 2;
	std::map<long int, Mapping> humidityToLocation;
	while(lines[idx].size() != 0) {
		Mapping m = readMapping(lines[idx++]);
		humidityToLocation.insert({m.src, m});
	}

	long int min = LONG_MAX;
	for(auto seed : seeds) {
		long int soil = map(seedToSoil, seed);
		long int fertilizer = map(soilToFertilizer, soil);
		long int water = map(fertilizerToWater, fertilizer);
		long int light = map(waterToLight, water);
		long int temperature = map(lightToTemperature, light);
		long int humidity = map(temperatureToHumidity, temperature);
		long int location = map(humidityToLocation, humidity);
		if(location < min) min = location;
		fmt::print("seed:\t{}, fertilizer:\t{}, water:\t{}, ", seed, fertilizer, water);
		fmt::print("light:\t{}, temperature:\t{}, ", light, temperature);
		fmt::println("humidity:\t{}, location: {}", humidity, location);
	}

	fmt::println("min {}", min);
}
