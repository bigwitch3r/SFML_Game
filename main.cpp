#include <SFML/Graphics.hpp>

using namespace sf;
int ground = 400;

const int H = 12;
const int W = 40;

String TileMap[H] = {

"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
"B                                B     B",
"B                                B     B",
"B                                B     B",
"B                                B     B",
"B         0000                BBBB     B",
"B                                B     B",
"BBB                              B     B",
"B              BB                BB    B",
"B              BB                      B",
"B    B         BB         BB           B",
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",

};

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
		dx = dy = 0.1;
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
	RenderWindow window(VideoMode(600, 450), "Test!");

	Texture texture;
	texture.loadFromFile("walking.png");

	float currentFrame = 0;

	Player player(texture);

	Clock clock;

	RectangleShape rectangle(Vector2f(32, 32));

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
				player.dy = -0.35;
				player.onGround = false;
			}
		}

		player.update(time);

		window.clear(Color::White);

		for (int i = 0; i < H; i++)
		{
			for (int j = 0; j < W; j++)
			{
				if (TileMap[i][j] == 'B')
				{
					rectangle.setFillColor(Color::Black);
				}

				if (TileMap[i][j] == '0')
				{
					rectangle.setFillColor(Color::Green);
				}

				if (TileMap[i][j] == ' ')
				{
					continue;
				}

				rectangle.setPosition(j * 32, i * 32);
				window.draw(rectangle);
			}
		}

		window.draw(player.sprite);
		window.display();
	}
	return 0;
}