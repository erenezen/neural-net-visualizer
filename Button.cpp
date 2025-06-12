// Kamil Eren Ezen
// 040210021
#include "Button.h"

//Button object's constructor.
Button::Button(float x, float y, float width, float height,
    const sf::Font& font, const std::string& label) {
    
    shape.setPosition(x, y); //Set the position of the object.
    shape.setSize(sf::Vector2f(width, height)); //Set the size of the object.
    shape.setFillColor(sf::Color(180, 180, 180)); //Set the color of the object(light gray).

    text.setFont(font); //Set the font.
    text.setString(label); //Set the text string.
    text.setCharacterSize(20); //Set the font size.
    text.setFillColor(sf::Color::Black); //Set the color of the text(Black).

    sf::FloatRect textBounds = text.getLocalBounds(); //Get the bounds of the button.
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, //Using that bounds, set the text on center.
        textBounds.top + textBounds.height / 2.0f);
    text.setPosition(x + width / 2.0f, y + height / 2.0f); //Set the position of the text on center.
}

void Button::draw(sf::RenderWindow& window) const { //Function that draws the button on window.
    window.draw(shape);
    window.draw(text);
}

bool Button::isClicked(sf::Vector2f mousePos) const { //Function that checks if the button is clicked. 
    return shape.getGlobalBounds().contains(mousePos); //If position of the mouse is in the bounds of the button, return true.
}
