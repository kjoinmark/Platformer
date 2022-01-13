#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>


class Map {
	std::string _map;
	sf::RectangleShape _block;
	size_t _width;
	size_t _height;
public:
	const size_t block_size;
public:
	Map(const std::string& filename, const float& block_siz);
public:
	//return width of map
	size_t get_width() const {
		return _width;
	};
	//return height of map
	size_t get_height() const {
		return _height;
	};
public:
	//return is there block on x,y coordinates
	bool is_block(size_t it_x, size_t it_y) const;
public:
	std::pair<size_t, size_t> one_spawn(const char type) const;
	std::vector<std::pair<size_t, size_t>> spawns(const char type) const;
};

