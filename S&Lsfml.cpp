#include "S&Lsfml.h"
#include "game.h"

// game menu function --->
int gamemenu()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "SNAKE & LADDERS GAME MENU");

	sf::Font font;
	if (!font.loadFromFile("tuffy.ttf"))
	{
		std::cerr << "font file not found";
		return -1;
	}

	sf::Text title("SNAKE & LADDERS", font, 60);
	title.setFillColor(sf::Color::Blue);
	title.setPosition(sf::Vector2f(150, 50));


	std::string menuoption[3];
	menuoption[0] = "1. Player VS Player";
	menuoption[1] = "2. Player VS AI";
	menuoption[2] = "3. Exit The Game";

	sf::Text menu[3];
	for (int i = 0; i < 3; i++)
	{
		menu[i].setFont(font);
		menu[i].setCharacterSize(40);
		menu[i].setString(menuoption[i]);
		menu[i].setFillColor(sf::Color::Yellow);
		menu[i].setPosition(sf::Vector2f(200, (i * 150) + 200));
	}

	while (window.isOpen())
	{
		sf::Event event;
		sf::Vector2i pix(sf::Mouse::getPosition(window));
		sf::Vector2f mouspos(window.mapPixelToCoords(pix));

		for (int i = 0;i < 3; i++)
		{
			if (menu[i].getGlobalBounds().contains(mouspos))
			{
				menu[i].setFillColor(sf::Color::Red);
			}
			else
			{
				menu[i].setFillColor(sf::Color::Yellow);
			}
		}

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();


			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				for (int i = 0; i < 3; i++)
				{
					if (menu[i].getGlobalBounds().contains(mouspos))
					{
						window.close();
						return i + 1;
					}
				}
			}
		}

		window.clear(sf::Color(30, 30, 30));

		window.draw(title);

		for (auto& option : menu)
		{
			window.draw(option);
		}
		window.display();
	}
	return 0;
}

// get position of board --->
sf::Vector2f getpos(int player, int cellsiz)
{
	int row = (player - 1) / 10;
	int col = (player - 1) % 10;
	if (row % 2 == 1
		) col = 9 - col;
	return sf::Vector2f(col * cellsiz, (9 - row) * cellsiz);
}

void drawSnakesAndLadders(sf::RenderWindow& window, float cellSize) {
	std::vector<std::pair<int, int>> ladders = {
		{6, 46}, {45, 65}, {77, 82}
	};
	std::vector<std::pair<int, int>> snakes = {
		{13, 23}, {43, 61}, {58, 66}, {10, 98}
	};

	// Draw ladders (green lines)
	for (const auto& ladder : ladders) {
		sf::Vertex line[] = {
			sf::Vertex(getpos(ladder.first, cellSize) + sf::Vector2f(50, 50), sf::Color::Green),
			sf::Vertex(getpos(ladder.second, cellSize) + sf::Vector2f(50, 50), sf::Color::Green)
		};
		window.draw(line, 2, sf::Lines);
	}

	// Draw snakes (red lines)
	for (const auto& snake : snakes) {
		sf::Vertex line[] = {
			sf::Vertex(getpos(snake.first, cellSize) + sf::Vector2f(50, 50), sf::Color::Red),
			sf::Vertex(getpos(snake.second, cellSize) + sf::Vector2f(50, 50), sf::Color::Red)
		};
		window.draw(line, 2, sf::Lines);
	}
}


void dicerol(sf::RenderWindow& window, sf::Sprite diceimg[], int& currget,
	sf::RectangleShape cell, sf::Font& font,
	sf::Text& statusmsg, sf::Text& dicemsg1,
	sf::RectangleShape& dicebuton, sf::Text& startmsg,
	int player1score, int player2score)
{
	for (int i = 0; i < 6; ++i)
	{
		int fake = rand() % 6;
		currget = fake + 1;
		window.clear(sf::Color::Black);

		for (int row = 0; row < 10; ++row)
		{
			for (int col = 0; col < 10; ++col)
			{
				int currrow = 9 - row;
				int num = currrow * 10 + (currrow % 2 == 0 ? col : 9 - col) + 1;
				cell.setPosition(col * 100, row * 100);
				cell.setFillColor((row % 2 == 0) ? sf::Color(60, 60, 120) : sf::Color(70, 70, 140));
				window.draw(cell);

				sf::Text count(std::to_string(num), font, 30);
				count.setPosition((col * 100) + 20, (row * 100) + 20);
				count.setFillColor(sf::Color::Magenta);
				window.draw(count);
			}

		}
		drawSnakesAndLadders(window, 100.f);


		sf::CircleShape p1(20);
		p1.setFillColor(sf::Color(255, 0, 0));
		p1.setPosition(getpos(player1score, 100.f) + sf::Vector2f(5, 5));

		sf::Text mark1("p1", font, 25);
		mark1.setFillColor(sf::Color::Black);
		mark1.setPosition(p1.getPosition() + sf::Vector2f(5, 5));

		sf::CircleShape p2(20);
		p2.setFillColor(sf::Color(0, 255, 0));
		p2.setPosition(getpos(player2score, 100.f) + sf::Vector2f(30, 5));

		sf::Text mark2("p2", font, 20);
		mark2.setFillColor(sf::Color::Blue);
		mark2.setPosition(p2.getPosition() + sf::Vector2f(5, 5));

		window.draw(p1);
		window.draw(mark1);
		window.draw(p2);
		window.draw(mark2);

		window.draw(dicebuton);
		window.draw(startmsg);
		window.draw(statusmsg);
		window.draw(dicemsg1);
		window.draw(diceimg[fake]);

		window.display();
		sf::sleep(sf::milliseconds(70));
	}

}

void draw1(sf::RenderWindow& window, sf::Sprite diceimg[], int& currget,
	sf::RectangleShape cell, sf::Font& font,
	sf::Text& statusmsg, sf::Text& dicemsg1,
	sf::RectangleShape& dicebuton, sf::Text& startmsg,
	int player1score, int player2score)
{
	window.clear(sf::Color::Black);

	for (int row = 0; row < 10; ++row)
	{
		for (int col = 0; col < 10; ++col)
		{
			int currrow = 9 - row;
			int num = currrow * 10 + (currrow % 2 == 0 ? col : 9 - col) + 1;
			cell.setPosition(col * 100, row * 100);
			cell.setFillColor((row % 2 == 0) ? sf::Color(60, 60, 120) : sf::Color(70, 70, 140));
			window.draw(cell);

			sf::Text count(std::to_string(num), font, 30);
			count.setPosition((col * 100) + 20, (row * 100) + 20);
			count.setFillColor(sf::Color::Magenta);
			window.draw(count);
		}

	}
	drawSnakesAndLadders(window, 100.f);

	sf::CircleShape p1(20);
	p1.setFillColor(sf::Color(255, 0, 0));
	p1.setPosition(getpos(player1score, 100.f) + sf::Vector2f(5, 5));

	sf::Text mark1("p1", font, 25);
	mark1.setFillColor(sf::Color::Black);
	mark1.setPosition(p1.getPosition() + sf::Vector2f(5, 5));

	sf::CircleShape p2(20);
	p2.setFillColor(sf::Color(0, 255, 0));
	p2.setPosition(getpos(player2score, 100.f) + sf::Vector2f(30, 5));

	sf::Text mark2("p2", font, 20);
	mark2.setFillColor(sf::Color::Blue);
	mark2.setPosition(p2.getPosition() + sf::Vector2f(5, 5));

	window.draw(p1);
	window.draw(mark1);
	window.draw(p2);
	window.draw(mark2);

	window.draw(dicebuton);
	window.draw(startmsg);
	window.draw(statusmsg);
	window.draw(dicemsg1);


	switch ((currget)) {

	case 1:
		window.draw(diceimg[0]);
		break;
	case 2:
		window.draw(diceimg[1]);
		break;
	case 3:
		window.draw(diceimg[2]);
		break;
	case 4:
		window.draw(diceimg[3]);
		break;
	case 5:
		window.draw(diceimg[4]);
		break;
	case 6:
		window.draw(diceimg[5]);
		break;
	default:
		window.draw(diceimg[5]);
		break;
	}

	window.display();
}

void gamefun(int mode)
{
	sf::RenderWindow window(sf::VideoMode(1000, 1000 + 300), "SNAKE & LADDERS");

	sf::Font font;
	if (!font.loadFromFile("tuffy.ttf")) std::cerr << "font file not found";

	sf::Text statusmsg("", font, 40);
	statusmsg.setFillColor(sf::Color::Cyan);
	statusmsg.setPosition(50.f, 1000.f + 20.f);

	sf::RectangleShape cell(sf::Vector2f(100.f, 100.f));
	cell.setFillColor(sf::Color::Transparent);
	cell.setOutlineThickness(2);
	cell.setOutlineColor(sf::Color::Black);

	// start msg -->
	sf::Text startmsg("roll dice", font, 35);
	startmsg.setFillColor(sf::Color::Black);
	startmsg.setPosition(55.f, 1210.f);

	// roll dice buton --->
	sf::RectangleShape dicebuton(sf::Vector2f(200.f, 70.f));
	dicebuton.setOutlineThickness(5);
	dicebuton.setOutlineColor(sf::Color::Blue);
	dicebuton.setFillColor(sf::Color::Cyan);
	dicebuton.setPosition(50.f, 1200.f);

	int dice;
	int currget = 0;
	bool p1turn = true;
	bool gameEnd = false;

	sf::Text dicemsg1("", font, 40);
	dicemsg1.setPosition(50.f, 1100.f + 20.f);
	dicemsg1.setFillColor(sf::Color::Blue);

	
	sf::Texture imag[6];
	sf::Sprite diceimg[6];
	for (int i = 0; i < 6; i++)
	{
		imag[i].loadFromFile("dice" + to_string(i + 1) + ".png");
		diceimg[i].setTexture(imag[i]);
		diceimg[i].setPosition(sf::Vector2f(500.f, 1100));
	}

	sf::SoundBuffer dicesound;
	dicesound.loadFromFile("dice.wav");

	sf::Sound click;
	click.setBuffer(dicesound);


	while (window.isOpen())
	{
		sf::Event event;
		sf::Vector2i pix(sf::Mouse::getPosition(window));
		sf::Vector2f mouspos(window.mapPixelToCoords(pix));

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (!gameEnd)
			{
				if (mode == 1)
				{
					if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left &&
						dicebuton.getGlobalBounds().contains(mouspos))
					{
						dicerol(window, diceimg, currget, cell, font, statusmsg, dicemsg1, dicebuton, startmsg, player1score, player2score);
						click.play();
						dice = rolldice();
						currget = dice;
						if (p1turn)
						{
							player1score = move(player1score, dice);
							dicemsg1.setString("player 1 roll's : " + to_string(dice));

						}
						else
						{
							player2score = move(player2score, dice);
							dicemsg1.setString("player 2 roll's : " + to_string(dice));
						}
						if (player1score == 100)
						{
							gameEnd = true;
							statusmsg.setString("player 1 wins...");
						}
						else if (player2score == 100)
						{
							gameEnd = true;
							statusmsg.setString("player 2 wins...");
						}
						else
						{
							p1turn = !p1turn;
							statusmsg.setString(p1turn ? "player 1 turns ..." : "player 2 turns...");
						}
					}
				}
				else if (mode == 2)
				{
					if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left &&
						dicebuton.getGlobalBounds().contains(mouspos))
					{
						dicerol(window, diceimg, currget, cell, font, statusmsg, dicemsg1, dicebuton, startmsg, 
							player1score, player2score);
						dice = rolldice();
						click.play();
						currget = dice;
						if (p1turn)
						{
							player1score = move(player1score, dice);
							dicemsg1.setString("player 1 roll's : " + to_string(dice));

						}
						if (player1score == 100)
						{
							gameEnd = true;
							statusmsg.setString("player 1 wins...");
							std::cout << "player 1 wins...." << endl;
						}
						else
						{
							p1turn = !p1turn;
							statusmsg.setString(p1turn ? "player 1 turns ..." : "computer turns...");
						}
					}
					draw1(window, diceimg, currget,cell, font,statusmsg, dicemsg1,dicebuton, startmsg,
						player1score, player2score);


				}
			}
		}

		if (!p1turn && !gameEnd && mode == 2)
		{
			sf::sleep(sf::milliseconds(500));
			dice = rolldice();
			player2score = move(player2score, dice);
			dicemsg1.setString("compter roll's : " + to_string(dice));

			if (player2score == 100)
			{
				gameEnd = true;
				statusmsg.setString("computer wins...");
				std::cout << "computer wins..." << endl;
			}
			else
			{
				p1turn = true;
				statusmsg.setString(p1turn ? "player 1 turns ..." : "computer turns...");

			}
		}

		draw1(window, diceimg, currget,
			cell, font,
			statusmsg, dicemsg1,
			dicebuton, startmsg,
			player1score, player2score);

	}
}



