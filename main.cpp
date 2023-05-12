#include <SFML/Graphics.hpp>
#include "Ball.h"

double mapValue(double value, double min, double max, double nMin, double nMax)
{
	// Y = (X-A)/(B-A) * (D-C) + C
	double newVal = (((value - min) / (max - min)) * (nMax - nMin)) + nMin;
	return newVal;
}

int main(int argc, char **argv)
{
	Ball ball(200, 250, 10, 400);
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(75, 25));
	rectangle.setFillColor(sf::Color::Cyan);
	rectangle.setOutlineColor(sf::Color::Blue);
	rectangle.setOutlineThickness(2);
	rectangle.setPosition(50, 50);

	sf::RectangleShape rdr2;
	rdr2.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	
	sf::Clock clock;
	sf::Vector3f xFactor(10, 20, 30);
	float ellapsedTime = 0;

	// on fait tourner le programme jusqu'à ce que la fenêtre soit fermée
	while (window.isOpen())
	{
		ellapsedTime = clock.restart().asSeconds();
		// on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		sf::Event event;
		while (window.pollEvent(event))
		{
			// évènement "fermeture demandée" : on ferme la fenêtre
			if (event.type == sf::Event::Closed)
				window.close();


		}

		ball.move(ellapsedTime);
		ball.manageCollisionWith(window);

		window.clear();


		window.draw(rectangle);
		ball.draw(window);
		window.display();
	}

	return 0;
}