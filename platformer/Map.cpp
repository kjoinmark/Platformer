#include "Map.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <iostream>

Map::Map(const std::string& filename, const float& block_siz) :
	block_size(block_siz) {
	_block.setSize(sf::Vector2f(block_siz, block_siz));
	std::ifstream fmap(filename);
	std::string map{ std::istreambuf_iterator<char>(fmap), std::istreambuf_iterator<char>() };
	_map = std::move(map);
	_width = _map.find('\n') + 1;
	_height = _map.size() / _width;
	fmap.close();
};

bool Map::is_block(size_t it_x, size_t it_y) const {
	if (it_y * _width + it_x >= _map.size())
		return 1;
	return (_map.at(it_y * _width + it_x) == 'B') == 1;
}


std::pair<size_t, size_t> Map::one_spawn(const char type) const {
	size_t pos = _map.find_first_of(type);
	size_t y = pos / _width;
	size_t x = pos - y * _width;
	return std::make_pair(x, y);
};

std::vector<std::pair<size_t, size_t>> Map::spawns(const char type) const {
	std::vector< std::pair<size_t, size_t>> mobs;
	size_t pos = 1, x, y;
	for (size_t i = 0; i < _map.size() && pos != 0; ) {
		pos = _map.find(type, i + 1);
		if (pos > _map.size())
			break;
		i = pos;
		y = pos / _width;
		x = pos - y * _width;
		mobs.push_back(std::make_pair(x, y));
	}
	return mobs;
};