// graphicalelements/TextInputField.h
#ifndef TEXT_INPUT_FIELD_H
#define TEXT_INPUT_FIELD_H

#include "../entities/Ente.h"
#include "MouseObserver.h"
#include "TextInputObserver.h"
#include <SFML/Graphics.hpp>

class TextInputField : public Ente,
                       public TextInputObserver,
                       public MouseObserver {
private:
  Text label;
  Text inputText;
  string currentInput;
  size_t maxLength;
  bool isActive;

public:
  TextInputField(sf::Font &font, const std::string &labelStr,
                 const sf::Vector2f &position);

  void setActive(bool active);
  void onTextEntered(const sf::Event::TextEvent &event) override;
  void onMouseEvent(const Event::MouseButtonEvent &event) override;
  void onMouseEvent(const Event::MouseMoveEvent &event) override;
  void draw() override;
  Drawable &getDrawable() override;
  const std::string getInput() const;
  void setPosition(sf::Vector2f pos) override;
  void execute() override;
  FloatRect getInputBounds() const;
  bool contains(const sf::Vector2f &point) const;
};

#endif
