#include <SFML/Graphics.hpp>

using namespace sf;
int ground = 150;

class Player
{

public:

	float dx, dy;
	FloatRect rect;
	bool onGround;
	Sprite sprite;
	float currentFrame;

	Player(Texture &image)
	{
		sprite.setTexture(image);
		rect = FloatRect(0, 0, 24, 38);
		dx = dy = 0;
		currentFrame = 0;
	}

	void update(float time)
	{
		rect.left += dx;

		if (!onGround)
		{
			dy = dy + 0.0005;
		}

		rect.top += dy;

		onGround = false;

		if (rect.top > ground)
		{
			rect.top = ground;
			dy = 0;
			onGround = true;
		}

		currentFrame += 0.005;

		if (currentFrame > 6)
		{
			currentFrame -= 6;
		}

		if (dx > 0)
		{
			sprite.setTextureRect(IntRect(24 * int(currentFrame), 0, 24, 38));
		}

		if (dx < 0)
		{
			sprite.setTextureRect(IntRect(24 * int(currentFrame) + 24, 0, -24, 38));
		}

		sprite.setPosition(rect.left, rect.top);

		dx = 0;
	}

};

int main()
{
	RenderWindow window(VideoMode(200, 200), "Test!");


	Texture texture;
	texture.loadFromFile("walking.png");

	float currentFrame = 0;

	Player player(texture);

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
			player.dx = -0.1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			player.dx = 0.1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			if (player.onGround)
			{
				player.dy = -0.25;
				player.onGround = false;
			}
		}

		player.update(time);

		window.clear(Color::White);
		window.draw(player.sprite);
		window.display();
	}
	return 0;
}