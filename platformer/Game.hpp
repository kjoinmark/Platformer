#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "World.hpp"

class Game{
	sf::RenderWindow window;
	sf::Clock clock;
	sf::Time time_since_last_update;
	sf::Music music;
	const sf::Time frame_time;
	float currentFrame;
	bool dead;
	size_t width, height;
	//private windows that can't be changed by user
	//menu's image
	bool menu(sf::Texture& img);
	//window after death or competing level
	bool over_window(World& world, bool type);
	//the level creating and run
	bool level(Texture_Pack& texture_pack, Sound_Pack& sound_pack, const std::string& map);
public:
	//base constructor
	Game() :window(sf::VideoMode(854, 480), "Game"), frame_time(sf::seconds(1.f / 64.f)) {
		window.setFramerateLimit(70);
		dead = false;
		currentFrame = 0;
		width = 854;
		height = 480;
		music.openFromFile("Spookster_long.ogg");
	};
	//to start game
	bool run();


};

