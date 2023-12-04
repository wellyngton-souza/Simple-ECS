#include <SFML/Graphics.hpp>
#include <iostream>

// g++ -Wall -Wextra -Werror ./src/main.cpp -o ./build/main.exe -lsfml-graphics -lsfml-window -lsfml-system

const int windowWidth = 960;
const int windowHeight = 540;

void mover(sf::Event event, sf::CircleShape &shape){ // & no shape quer dizer que estou editando a variavel original invez de criar uma copia
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            shape.move(0, -2); // Move o círculo para cima ao pressionar espaço
        } else if(event.key.code == sf::Keyboard::Down){
            shape.move(0, 2);
        }
        
        if(event.key.code == sf::Keyboard::Left){
            shape.move(-2, 0);
        } else if(event.key.code == sf::Keyboard::Right){
            shape.move(2, 0);
        }
    }
}

sf::CircleShape gerarCirculo(){
    sf::CircleShape shape(20.f);
    shape.setFillColor(sf::Color::Red);

    return shape;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "moveCircle");
    
    sf::CircleShape shape = gerarCirculo();

    while (window.isOpen()) {
        sf::Event event;
        
        while (window.pollEvent(event)) {
            mover(event, shape);

            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}