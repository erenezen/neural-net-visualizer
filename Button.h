// Kamil Eren Ezen
// 040210021
#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button {
private:
    sf::RectangleShape shape; //Shape attribute of Button object.
    sf::Text text; //Text attribute of Button object.

public:
    Button(float x, float y, float width, float height, //Constructor.
        const sf::Font& font, const std::string& label);

    void draw(sf::RenderWindow& window) const; //Draw function.
    bool isClicked(sf::Vector2f mousePos) const; //isClicked Function.
};
