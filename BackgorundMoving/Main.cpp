#include <iostream>
#include <conio.h>
#include <Windows.h>

#include <SFML/Graphics.hpp>

void MoveBackground(sf::Sprite &backgroundSprite){

    static sf::IntRect textureRectangle(0, 0, 1360, 768);

    static int& offset = textureRectangle.left;

    offset++;

    if (offset == 4081) {
        offset = 1;
    }

    backgroundSprite.setTextureRect(textureRectangle);

    Sleep(20);

}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1360, 768), "SFML works!", NULL);
    
    sf::RectangleShape shape(sf::Vector2f(4081, 768));

    sf::Texture texture;

    texture.loadFromFile("C:\\Users\\user\\source\\repos\\SpaceShipTheGame\\Resources\\Background\\BitStars.png", sf::IntRect(0, 0, 5101, 768));

    sf::Sprite sprite;

    sprite.setTexture(texture);

    sprite.setTextureRect(sf::IntRect(0, 0, 1360, 768));

    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        MoveBackground(sprite);

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}