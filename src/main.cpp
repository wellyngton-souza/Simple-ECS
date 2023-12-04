#include <SFML/Graphics.hpp>
#include <iostream>

// g++ -Wall -Wextra -Werror ./src/main.cpp -o ./build/main.exe -lsfml-graphics -lsfml-window -lsfml-system

const int windowWidth = 540;
const int windowHeight = 540;
const int grid = 3;
const int quadradoSize = windowWidth / grid;

void verificaClick(sf::Event event, int c[grid][grid], int &vezPlayer, sf::Window &window){
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        int x = mousePos.x / quadradoSize;
        int y = mousePos.y / quadradoSize;

        if(x >= 0 && x < grid && y >= 0 && y < grid && c[y][x] == 0){
            c[y][x] = vezPlayer;
            vezPlayer = (vezPlayer == 1) ? 2 : 1;
        }
    }
}

void renderizarTabuleiro(int c[grid][grid], sf::RenderWindow &window){
    for(int i = 0; i < grid; i++){
        for(int j = 0; j < grid; j++){
            // redenriza quadrados tabuleiro
            sf::RectangleShape cell(sf::Vector2f(quadradoSize - 1, quadradoSize - 1));
            cell.setPosition(j * quadradoSize, i * quadradoSize);
            cell.setOutlineThickness(1);
            cell.setOutlineColor(sf::Color::Black);
            window.draw(cell);

            // renderiza jogadas
            if(c[i][j] == 1){
                sf::CircleShape circle(quadradoSize / 3);
                circle.setFillColor(sf::Color::Blue);
                circle.setPosition(j * quadradoSize + quadradoSize / 6, i * quadradoSize + quadradoSize / 6); // não sei a lógica disso
                window.draw(circle);
            } else if(c[i][j] == 2){
                // cria dos quadrados e muda o angulo pra simular o X
                sf::RectangleShape cross(sf::Vector2f(quadradoSize / 1.2, 15));
                cross.setFillColor(sf::Color::Red);
                cross.rotate(45);
                cross.setPosition(j * quadradoSize + quadradoSize / 4, i * quadradoSize + quadradoSize / 6);
                window.draw(cross);

                cross.rotate(-90);
                cross.setPosition(j * quadradoSize + quadradoSize / 4, i * quadradoSize + quadradoSize / 1.4);
                window.draw(cross);
            }
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "jogoVelha");

    int c[grid][grid] = {0};
    int vezPlayer = 1;
    bool fimJogo = false;

    std::vector<std::vector<int>> casasVictory = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {6, 4, 2}};

    while (window.isOpen()) {
        sf::Event event;
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            verificaClick(event, c, vezPlayer, window);
        }

        window.clear();

        for(auto i = 0u; i < casasVictory.size(); i++){
            int casaA = casasVictory[i][0];
            int casaB = casasVictory[i][1];
            int casaC = casasVictory[i][2];

            if (c[casaA / grid][casaA % grid] != 0 && c[casaA / grid][casaA % grid] == c[casaB / grid][casaB % grid] && c[casaB / grid][casaB % grid] == c[casaC / grid][casaC % grid]) {
                fimJogo = true;
                break;
            }
        }

        if(!fimJogo) renderizarTabuleiro(c, window);

        window.display();
    }

    return 0;
}