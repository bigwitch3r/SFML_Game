#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(300, 300), "Test!");

	CircleShape MyCircle(100.f);
	MyCircle.setFillColor(Color::Green);

	Texture texture;
	texture.loadFromFile("walking.png");

	float currentFrame = 0;

	Sprite sprite;
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, 24, 38));
	sprite.setPosition(0, 0);

	Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			sprite.move(-0.1, 0);

			currentFrame += 0.005;

			if (currentFrame > 6)
			{
				currentFrame -= 6;
			}

			sprite.setTextureRect(IntRect(24 * int(currentFrame) + 24, 0, -24, 38));
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			sprite.move(0.1, 0);

			currentFrame += 0.005;

			if (currentFrame > 6)
			{
				currentFrame -= 6;
			}

			sprite.setTextureRect(IntRect(24 * int(currentFrame), 0, 24, 38));
		}

		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			sprite.move(0, 0.1);
		}

		window.clear();
		window.draw(sprite);
		window.display();
	}
	return 0;
}