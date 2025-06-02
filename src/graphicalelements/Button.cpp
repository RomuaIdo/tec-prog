#include "../../include/graphicalelements/Button.h"

Button::Button(const string fontPath, const string info,
               const string normalTexturePath, const string hoveredTexturePath,
               MouseSubject *subject, unsigned int fontSize, Vector2f position)
    : Ente(), fontSize(fontSize), position(position),
      state(ButtonState::NORMAL), mouseSubject(subject), clicked(false) {

  if (!texture.loadFromFile(normalTexturePath)) {
    cerr << "Failed to load normal texture!" << endl;
  }
  if (!hoverTexture.loadFromFile(hoveredTexturePath)) {
    cerr << "Failed to load hovered texture!" << endl;
  }
  if (!font.loadFromFile(fontPath)) {
    cerr << "Failed to load font!" << endl;
  }
  sprite.setTexture(texture);
  setPosition(position);

  label.setFont(font);
  label.setString(info);
  label.setCharacterSize(fontSize);
  label.setFillColor(Color::White);

  adjustSize();
}

void Button::activate() { mouseSubject->addObserver(this); }

void Button::deactivate() { mouseSubject->removeObserver(this); }
bool Button::wasClicked() {
  if (clicked) {
    clicked = false;
    return true;
  }
  return false;
}

Button::~Button() {
  deactivate();
  mouseSubject = nullptr;
}

Drawable &Button::getDrawable() { return sprite; }

void Button::draw() {
  pGM->getWindow()->draw(sprite);
  pGM->getWindow()->draw(label);
}

void Button::setPosition(Vector2f pos) {
  position = pos;
  sprite.setPosition(pos);

  FloatRect textbounds = label.getLocalBounds();
  FloatRect buttonounds = sprite.getLocalBounds();

  Vector2f textposition(pos.x + (buttonounds.width - textbounds.width) / 2.f,
                        pos.y + (buttonounds.height - textbounds.height) / 2.f);

  label.setPosition(textposition);
}

Vector2f Button::getPosition() const { return position; }

void Button::setState(ButtonState newState) {
  state = newState;
  switch (state) {
  case ButtonState::NORMAL:
    sprite.setTexture(texture);
    break;
  case ButtonState::HOVERED:
    sprite.setTexture(hoverTexture);
    break;
  }
}

ButtonState Button::getState() const { return state; }

void Button::execute() { draw(); }

void Button::adjustSize() {
  FloatRect bounds = label.getLocalBounds();
  Vector2f padding(20.f, 10.f);
  sprite.setScale(1.f, 1.f);
  sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
  sprite.setScale((bounds.width + padding.x) / texture.getSize().x,
                  (bounds.height + padding.y) / texture.getSize().y);

  FloatRect buttonBounds = sprite.getGlobalBounds();
  label.setPosition(
      buttonBounds.left + (buttonBounds.width - bounds.width) / 2.f,
      buttonBounds.top + (buttonBounds.height - bounds.height) / 2.f -
          bounds.top);
}

void Button::onMouseEvent(const Event::MouseMoveEvent &event) {
  Vector2f mousepos(static_cast<float>(event.x), static_cast<float>(event.y));
  FloatRect bounds = sprite.getGlobalBounds();
  if (bounds.contains(mousepos)) {
    setState(ButtonState::HOVERED);
  }
  else {
    setState(ButtonState::NORMAL);
  }
}

void Button::onMouseEvent(const Event::MouseButtonEvent &event) {
  Vector2f mousePos(static_cast<float>(event.x), static_cast<float>(event.y));
  FloatRect bounds = sprite.getGlobalBounds();

  if (bounds.contains(mousePos) && event.button == Mouse::Left) {
    clicked = true;
  }
}
