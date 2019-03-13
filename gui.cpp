#include <SFML/Graphics.hpp>

void gui()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Roll Block", sf::Style::Default);
	sf::Image img;

	img.loadFromFile("roll_block.png");
	window.setIcon(img.getSize().x, img.getSize().y, img.getPixelsPtr());

	sf::RectangleShape rectangle(sf::Vector2f(50.f, 50.f));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
				{
					rectangle.move(sf::Vector2f(0.f, -5.f));
				}
				if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
				{
					rectangle.move(sf::Vector2f(-5.f, 0.f));
				}
				if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
				{
					rectangle.move(sf::Vector2f(5.f, 0.f));
				}
				if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
				{
					rectangle.move(sf::Vector2f(0.f, 5.f));
				}
				break;

			default:
				break;
			}
		}

		window.clear(sf::Color::Black);

		window.draw(rectangle);

		window.display();
	}
}