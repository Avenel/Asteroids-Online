#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window.hpp>
#include "Systems\MotionControlSystem.h"
#include "Graphics\StarshipView.h"
#include "Systems\EntityManager.h"
#include "Entity\EntityCreator.h"

int mainML() {

	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	MotionControlSystem motionControlSystem;
	EntityManager entityManager(new FamilyManager());
	EntityCreator entityCreator;

	//Starship erstellen
	entityManager.addEntity(entityCreator.createStarship());

	//Darzustellende Objekte registrieren

	
	while (window.isOpen())
	{
		sf::Event event1;
		while(window.pollEvent(event1))
		{
			if(event1.type == sf::Event::KeyPressed) {
				motionControlSystem.update();
			}
		}
	}

	return 0;
}