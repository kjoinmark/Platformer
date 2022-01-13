#include "Game.hpp"
#include "Packs.hpp"

bool Game::menu(sf::Texture& img) {
	sf::Event event;

	sf::Sprite back(img);
	window.clear(sf::Color::Black);
	sf::Text start_t;
	sf::Font font;
	font.loadFromFile("data-latin.ttf");
	start_t.setFont(font);
	start_t.setCharacterSize(40);
	start_t.setString("To Start Game\n  Press F");
	sf::FloatRect textRect = start_t.getLocalBounds();
	start_t.setOrigin(textRect.left + textRect.width / 2.0f + 1,
		textRect.top + textRect.height / 2.0f + 1);
	start_t.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f));
	window.draw(back);
	window.draw(start_t);
	window.display();
	while (!window.pollEvent(event) || !sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
		if (event.type == sf::Event::Closed) {
			window.close();
			return false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
			return true;
		}
	}

}

bool Game::over_window(World& world, bool type) {
	sf::Event event;

	window.clear(sf::Color::Black);
	sf::Text text = world.get_score();
	if (!type)
		text.setString("You died\nYour " + text.getString() + "\nTo restart press F");
	else
		text.setString("You win\nYour " + text.getString() + "\nTo restart press F\nTo continue press C");
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f + 1,
		textRect.top + textRect.height / 2.0f + 1);
	text.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f));
	if (!type) {
		sf::Texture respect;
		respect.loadFromFile("respect.png");
		sf::Sprite cat(respect);
		cat.setPosition(-80, height - 250);
		window.draw(cat);
	}
	window.draw(text);
	window.display();
	while (!window.pollEvent(event) || !sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
		if (event.type == sf::Event::Closed) {
			window.close();
			return true;

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
			world.restart();
			currentFrame = 0;
			break;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
			currentFrame = 0;
			break;
		}
	}
}

bool Game::level(Texture_Pack& texture_pack, Sound_Pack& sound_pack, const std::string& map) {
	World world(texture_pack, sound_pack, map, window.getSize());

	currentFrame = 0;

	time_since_last_update = sf::Time::Zero;
	clock.restart();
	while (window.isOpen()) {
		if (dead == true) {
			time_since_last_update += clock.restart();
			time_since_last_update = sf::Time::Zero;
		}
		else
			time_since_last_update += clock.restart();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		dead = !world.update(time_since_last_update.asMilliseconds(), currentFrame);
		while (time_since_last_update > frame_time) {
			time_since_last_update -= frame_time;
			dead = !world.update(time_since_last_update.asMilliseconds(), currentFrame);
		}


		window.clear(sf::Color::White);

		world.render(window);
		window.display();
		if (dead == true) {
			over_window(world, world.is_win());
			if (world.is_win())
				return true;
		}
	}
	return false;
}


bool Game::run() {
	music.play();
	music.setLoop(true);

	Texture_Pack texture_pack;

	if (!menu(texture_pack.background))
		return true;
	

	Sound_Pack sound_pack;

	if (level(texture_pack, sound_pack, "test.txt"));
	else
		return true;
	dead = false;
	if (level(texture_pack, sound_pack, "test2.txt"));
	else
		return true;

};