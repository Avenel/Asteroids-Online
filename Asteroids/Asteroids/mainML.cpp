#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window.hpp>
#include "Systems\MotionControlSystem.h"
#include "Graphics\StarshipView.h"

int mainML() {

	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	MotionControlSystem mcs;

	StarshipView* starship1 = new StarshipView();
	window.draw(*starship1);
	window.display();
	//Display.setView(starship1);

	while (window.isOpen())
	{
		sf::Event event1;
		while(window.pollEvent(event1))
		{
			if(event1.type == sf::Event::KeyPressed) {
				mcs.update();
			}
		}
	}

	return 0;
}