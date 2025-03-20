#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <array_list.h>
#include <WordReader.h>
#include <math.h>

// There are clearly a lot of things missing. I got caught on some issues which kept setting me back.
// I think I have WordReader set up properly but I don't have words showing on circles, 10 just print at the start
// Circles spawn and fall down, but for some reason only on one side of the screen, couldn't fix that
// Circle_strings for some reason won't allow me to append strings
// I didn't get a chance to actually write any google tests, but I did get all the CMake related stuff done and set up
// No bullets because I fell short on time
// I may work on some of this stuff after the due date, but this is what I have for submission

class TextCircle
{
private:
	sf::Text my_text;
	sf::CircleShape my_circle;

public:
	TextCircle(sf::Font& the_font) : my_text(the_font) // We HAVE to use this syntax to pass
	{												   // the required parameter to my_text's constructor
		//my_text(the_font);						   // Nice thought, but too late.
	}

	void set_position(float x, float y)
	{
		my_text.setPosition(sf::Vector2f(x, y));
		my_circle.setPosition(sf::Vector2f(x, y));
	}

	void set_text(std::string s)
	{
		my_text.setString(s);
		my_circle.setRadius(50.0f);
		my_circle.setOrigin(sf::Vector2f(50.0f, 50.0f));

		sf::FloatRect textBounds = my_text.getLocalBounds();
		sf::Vector2f textSize = textBounds.size;
		my_text.setOrigin(sf::Vector2f(textSize.x / 2.0f, textSize.y / 2.0f));
		// Adjust circle radius to fit??
	}

	void draw(sf::RenderWindow& rw)
	{
		my_circle.setFillColor(sf::Color(200, 0, 10, 255));
		rw.draw(my_circle);
		rw.draw(my_text);
	}
};

int main(int argc, char** argv)
{
	srand(time(NULL));
	// User's view
	WordReader WR("..\\..\\..\\media\\english-words.50.txt");
	for (int i = 0; i < 10; i++)
	{
		std::cout << WR.getWord() << "\n";
	}

	// This code is run before the game starts. Note how SFML is very object-oriented (creating
	// objects and calling methods) rather than SDL, which is very C based (mostly calling functions
	// and passing around structs)

	sf::RenderWindow window(sf::VideoMode({ 800,600 }), "Wyatt's Lab4");
	sf::CircleShape test_circle(100.0f);
	test_circle.setFillColor(sf::Color(200,255,100,255));
	test_circle.setPosition(sf::Vector2f(400.0f, 300.0f));
	test_circle.setOrigin(sf::Vector2f(100.0f, 100.0f));

	sf::Texture my_hand_image("..\\..\\..\\media\\hand.png");
	sf::Sprite my_hand_sprite(my_hand_image);
	my_hand_sprite.setRotation(sf::degrees(45.0f));
	my_hand_sprite.setPosition(sf::Vector2f(400.0f, 400.0f));

	// Load a font and make a Text object from it. 
	// Reference: https://www.sfml-dev.org/tutorials/3.0/graphics/text
	sf::Font my_font("..\\..\\..\\media\\Oswald\\Oswald\\static\\Oswald-Regular.ttf");
	sf::Text test_text(my_font);
	test_text.setString("Hello!");
	test_text.setCharacterSize(24);
	test_text.setFillColor(sf::Color(100, 255, 100, 128));
	test_text.setPosition(sf::Vector2(50.0f, 50.0f));
	sf::FloatRect test_text_bounds = test_text.getLocalBounds();
	sf::Vector2f test_text_size = test_text_bounds.size;
	test_text.setOrigin(sf::Vector2(test_text_size.x / 2.0f, test_text_size.y / 2.0f));
	test_text.setRotation(sf::degrees(-15));

	// Create the ArrayLists that will hold the data related to the falling circles
	//ssuds::ArrayList<TextCircle> my_circles;
	//TextCircle test(my_font);
	//my_circles.append(test);
	// Suggestion: make a collection of parallel arrays to store all DATA related to the
	// falling circles.
	ssuds::ArrayList<float> circle_xlist;
	ssuds::ArrayList<float> circle_ylist;
	ssuds::ArrayList<std::string> circle_strings;

	sf::Clock spawnClock, gameClock;

	// This is the "GAME LOOP" -- it runs as long as the window is open.  The two main
	// parts of a game loop are input-handling and drawing.  You might want to add a third
	// section that does other (non-input-related) updates.
	while (window.isOpen())
	{
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		// @ UPDATES (not input driven)              @
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		// ....
		
		// attempted to make spawn control frame control for circles
		if (spawnClock.getElapsedTime().asSeconds() >= 1.0f)
		{
			if ((int)spawnClock.getElapsedTime().asSeconds() % 5 == 0)
			{
				circle_xlist.append(rand() % window.getSize().x);
				circle_ylist.append(0);
				circle_strings.append("stuff");
			}
		}
		
		float deltaT = gameClock.getElapsedTime().asSeconds();
		gameClock.restart();
		for (int i = 0; i < circle_xlist.size();i++)
		{
			circle_ylist[i] += 100 * deltaT;
		}
		

		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		// @ Input-handling (keyboard and mouse)     @
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		// std::optional is a new C++-17+ thing -- it's kind of like
		// in python, if a function doesn't return anything useful, None is
		// returned.
		// Normally you would use == like this in a while loop -- this is assigning a result to event
		// AND THEN using that value as the "truth-test" for the while condition
		while (const std::optional event = window.pollEvent())
		{
			// We use event to see if it's something we care about
			if (event->is<sf::Event::Closed>())
			{
				// The quit button was pressed.
				window.close();
			}
			else if (const sf::Event::KeyPressed* keyEvt = event->getIf<sf::Event::KeyPressed>())
			{
				// We get here if a key is pressed.  Now see if it's a key we care about
				if (keyEvt->code == sf::Keyboard::Key::Escape)
				{
					window.close();
				}
			}
			else if (const sf::Event::MouseButtonPressed* buttonEvt =
				event->getIf<sf::Event::MouseButtonPressed>())
			{
				// We get here if any mouse button is pressed.  Now see if it's
				// a button press that we care about
				if (buttonEvt->button == sf::Mouse::Button::Left)
				{
					// We get here if it's a left-mouse button pressed.  Move green circle
					// here
					sf::Vector2f temp_pos(buttonEvt->position.x, buttonEvt->position.y);
					test_circle.setPosition(temp_pos);

					// Spawn a new circle
					circle_xlist.append(temp_pos.x);
					circle_ylist.append(temp_pos.y);
					circle_strings.append("foo");
				}

				// attempted to make hand turn to point mouse
				sf::Vector2f mouse_pos(buttonEvt->position.x, buttonEvt->position.y);
				sf::Vector2f hand_pos = my_hand_sprite.getPosition();
				float opp = mouse_pos.y - hand_pos.y;
				float adj = mouse_pos.x - hand_pos.x;
				my_hand_sprite.setRotation(sf::degrees(atan2(-opp, adj)));
			}
			// ... mouse moved
		}

		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		// @ Drawing (to the window)     @
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		window.clear();
		window.draw(test_circle);
		window.draw(my_hand_sprite);
		window.draw(test_text);
		// All circle-data lists have the same size
		for (int i = 0; i < circle_xlist.size(); i++)
		{
			float x = circle_xlist[i];
			float y = circle_ylist[i];
			std::string s = "test";//circle_strings[i];
			TextCircle temp(my_font);
			temp.set_position(x, y);
			temp.set_text(s);
			// Draw temp.
			temp.draw(window);
		}

		window.display();// Shows our drawings
	}
	return 0;
}

