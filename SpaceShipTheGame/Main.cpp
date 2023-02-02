#include <iostream>

#include <conio.h>

#include <SFML/Graphics.hpp>

#include <LunaSVG/lunasvg.h>

void Fee(sf::Texture& text) {
    
    sf::Image img;

    auto doc = lunasvg::Document::loadFromFile("D:\\dceecr\\Potim\\adfas\\Space\\shipFly.svg");

    auto bitmap = doc->renderToBitmap(300, 300);

    bitmap.convertToRGBA();

    auto arr = bitmap.data();

    img.create(300, 300, arr);

    text.loadFromImage(img);

    /*for (int i(0); i < 300; i++) {

        for (int j(0); j < 300; j++) {



        }

    }*/


}

int main() {

    {

        std::cout << "This is Spaceship";

        std::cout << " " << std::endl;

        std::cout << "------!" << std::endl;
        std::cout << "------!" << std::endl;
        std::cout << "------^" << std::endl;
        std::cout << "-----/ \\" << std::endl;
        std::cout << "----/ _ \\" << std::endl;
        std::cout << "----|= =|" << std::endl;
        std::cout << "---|     |" << std::endl;
        std::cout << "---|     |" << std::endl;
        std::cout << "-|-|     | |" << std::endl;
        std::cout << "-|-|     | |" << std::endl;
        std::cout << "-|-|     | |" << std::endl;
        std::cout << "---|     |" << std::endl;
        std::cout << "---|     |" << std::endl;
        std::cout << "---|     |" << std::endl;
        std::cout << "---|     |" << std::endl;
        std::cout << "--/|##!##|\\" << std::endl;
        std::cout << "-/| ##!## |\\" << std::endl;
        std::cout << "/ | ##!## | \\" << std::endl;
        std::cout << "|  /^ | ^\\  |" << std::endl;
        std::cout << "| /  (|)  \\ |" << std::endl;
        std::cout << "|/   (|)   \\|" << std::endl;
        std::cout << "-----(())" << std::endl;
        std::cout << "----((:))" << std::endl;
        std::cout << "----((:))" << std::endl;
        std::cout << "-----(())" << std::endl;
        std::cout << "----(())" << std::endl;
        std::cout << "-----()" << std::endl;
        std::cout << "-----." << std::endl;
        std::cout << "------." << std::endl;
        std::cout << "-----." << std::endl;

        std::cout << std::endl << std::endl;

        std::cout << "Wooo woo\n\n";

    }

    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);


    sf::Sprite sprite;

    sf::Texture text;

    Fee(text);

    sprite.setTexture(text);

    window.draw(shape);
    window.display();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        window.draw(sprite);
//        window.draw(shape);
        window.display();
    }

	return 0;

}