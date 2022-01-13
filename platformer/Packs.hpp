#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

struct Texture_Pack {
	sf::Texture background;
	sf::Texture ground;

	sf::Texture player;
	sf::Texture mobs;

	sf::Texture fireball;
	sf::Texture hp_texture;
	sf::Texture bonus;
	sf::Texture portal;

	sf::Font font;
public:
	Texture_Pack() {
		background.loadFromFile("background.jpg");
		ground.loadFromFile("textures.png", sf::IntRect(205, 0, 98, 98));

		fireball.loadFromFile("fireball.png");
		hp_texture.loadFromFile("hearts.png");
		bonus.loadFromFile("diamond.png");
		portal.loadFromFile("portal.png");

		player.loadFromFile("player.png");
		mobs.loadFromFile("mob2.png");

		font.loadFromFile("data-latin.ttf");
	}
	~Texture_Pack() = default;
};

struct Sound_Pack {
	sf::Sound jump;
	sf::Sound fire;
private:
	sf::SoundBuffer jump_b;
	sf::SoundBuffer fire_b;
public:
	Sound_Pack() {
		jump_b.loadFromFile("jump.ogg");
		fire_b.loadFromFile("fire.ogg");
		jump.setBuffer(jump_b);
		fire.setBuffer(fire_b);
	}
};