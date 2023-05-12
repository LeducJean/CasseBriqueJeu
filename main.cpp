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

	const int numRectanglesWidth = 8; // Nombre de rectangles en largeur
	const int numRectanglesHeight = 5; // Nombre de rectangles en hauteur
	sf::Vector2f rectangleSize(75, 25); // Taille des rectangles
	float spacingX = 10.0f; // Espacement horizontal entre les rectangles
	float spacingY = 10.0f; // Espacement vertical entre les rectangles

	// Créer un tableau de rectangles
	std::vector<sf::RectangleShape> rectangles(numRectanglesWidth * numRectanglesHeight);
	for (int i = 0; i < numRectanglesHeight; ++i)
	{
		for (int j = 0; j < numRectanglesWidth; ++j)
		{
			sf::RectangleShape rectangle;
			rectangle.setSize(rectangleSize);
			rectangle.setFillColor(sf::Color::Cyan);
			rectangle.setOutlineColor(sf::Color::Blue);
			rectangle.setOutlineThickness(2);
			float posX = 50 + (j * (rectangleSize.x + spacingX)); // Position en X
			float posY = 50 + (i * (rectangleSize.y + spacingY)); // Position en Y
			rectangle.setPosition(posX, posY);
			rectangles[i * numRectanglesWidth + j] = rectangle;
		}
	}

	sf::RectangleShape rdr2;
	rdr2.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));

	sf::Clock clock;
	sf::Vector3f xFactor(10, 20, 30);
	float ellapsedTime = 0;

	// On fait tourner le programme jusqu'à ce que la fenêtre soit fermée
	while (window.isOpen())
	{
		ellapsedTime = clock.restart().asSeconds();
		// On inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Évènement "fermeture demandée" : on ferme la fenêtre
			if (event.type == sf::Event::Closed)
				window.close();
		}

		ball.move(ellapsedTime);
		ball.manageCollisionWith(window);

		window.clear();

		// Dessiner les rectangles dans la boucle principale
		for (const auto& rectangle : rectangles)
		{
			window.draw(rectangle);
		}

		ball.draw(window);
		window.display();
	}

	return 0;
}
