// TextInputField.cpp
#include "../../include/graphicalelements/TextInputField.h"

TextInputField::TextInputField(sf::Font &font, const std::string &labelStr,
                               const sf::Vector2f &position)
    : maxLength(3), isActive(false) {

  label.setFont(font);
  label.setString(labelStr);
  label.setCharacterSize(24);
  label.setFillColor(sf::Color::White);
  label.setPosition(position);

  inputText.setFont(font);
  inputText.setString("___");
  inputText.setCharacterSize(24);
  inputText.setFillColor(sf::Color::White);
  inputText.setPosition(position.x, position.y + 30.f);
}

void TextInputField::setActive(bool active) {
  isActive = active;
  inputText.setFillColor(active ? Color::Yellow : Color::White);
}

void TextInputField::execute() {}

void TextInputField::onTextEntered(const sf::Event::TextEvent &event) {
  if (!isActive)
    return;

  if (event.unicode == '\b') { // Backspace
    if (!currentInput.empty()) {
      currentInput.pop_back();
    }
  } else if (event.unicode >= 65 && event.unicode <= 90) { // A-Z
    if (currentInput.length() < maxLength) {
      currentInput += static_cast<char>(event.unicode);
    }
  } else if (event.unicode >= 97 && event.unicode <= 122) { // a-z
    if (currentInput.length() < maxLength) {
      currentInput +=
          static_cast<char>(event.unicode - 32); // Convert to uppercase
    }
  }

  string displayStr = currentInput;
  while (displayStr.length() < maxLength) {
    displayStr += '_';
  }
  inputText.setString(displayStr);
}

bool TextInputField::contains(const Vector2f &point) const {
  FloatRect inputBounds = inputText.getGlobalBounds();

  inputBounds.top -= 50.f;
  inputBounds.height += 100.f;

  return inputBounds.contains(point) || label.getGlobalBounds().contains(point);
}

void TextInputField::draw() {
  pGM->draw(&label);
  pGM->draw(&inputText);
}

Drawable &TextInputField::getDrawable() { return label; }

const string TextInputField::getInput() const {
  if (currentInput.empty()) {
    return "___";
  }
  return currentInput;
}

void TextInputField::setPosition(Vector2f pos) {
  label.setPosition(pos);
  inputText.setPosition(pos.x, pos.y + 30.f);
}

FloatRect TextInputField::getInputBounds() const {
  return inputText.getGlobalBounds();
}

void TextInputField::onMouseEvent(const Event::MouseButtonEvent &event) {
  if (event.button == Mouse::Left) {
    RenderWindow *window = pGM->getWindow();
    Vector2f mousePos = window->mapPixelToCoords(Vector2i(event.x, event.y));
    if (contains(mousePos)) {
      setActive(true);
    } else {
      setActive(false);
    }
  }
}

void TextInputField::onMouseEvent(const Event::MouseMoveEvent &event) {}
