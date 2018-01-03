#include <iostream>
#include <SFML/Graphics.hpp>
#include "Camera/Camera.h"
#include <iomanip>
using namespace TD;

int main()
{
	sf::Vector2u winSize(512, 512);
	sf::RenderWindow window(sf::VideoMode(winSize.x, winSize.y), "SFML 3D Graphics Engine");
	//window.setFramerateLimit(15);
	
	TD::Camera camera({winSize.x, winSize.y});
	camera.moveInLocal({ 0,0,40 });

	sf::Vector2i lastCamPos = sf::Mouse::getPosition(window);
	sf::Clock clock;
	float deltaT = 0;

	while (window.isOpen())
	{
		deltaT = clock.restart().asSeconds();
		std::cout << 1. / deltaT << std::endl;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			camera.moveInLocal(TD::Vec3d(50 * deltaT, 0, 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			camera.moveInLocal(TD::Vec3d(-50 * deltaT, 0, 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			camera.moveInLocal(TD::Vec3d(0, 0, -50 * deltaT));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			camera.moveInLocal(TD::Vec3d(0, 0, 50 * deltaT));
		if (sf::Mouse::getPosition(window) != lastCamPos)
		{
			auto delta = sf::Mouse::getPosition(window) - lastCamPos;
			lastCamPos = sf::Mouse::getPosition(window);

			camera.rotateInGlobal({0, TD::toRadians(delta.x * -0.5), 0});
			camera.rotateInGlobal({ TD::toRadians(delta.y * -0.5), 0, 0 });
		}

		while (window.pollEvent(sf::Event())) {}
		window.clear();
		window.draw(camera);
		window.display();
	}

	return 0;
}