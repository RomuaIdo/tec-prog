#include "../../include/graphicalelements/Button.h"

Button::Button(const string fontPath, const string info,
               const string normalTexturePath, const string hoveredTexturePath,
               MouseSubject *subject, unsigned int fontSize, Vector2f position)
    : Ente(), mouseSubject(subject), fontSize(fontSize), position(position),
      state(ButtonState::NORMAL), clicked(false) {

  if (!texture.loadFromFile(normalTexturePath))
    cerr << "Failed to load normal texture!" << endl;

  if (!hoverTexture.loadFromFile(hoveredTexturePath))
    cerr << "Failed to load hovered texture!" << endl;

  if (!font.loadFromFile(fontPath))
    cerr << "Failed to load font!" << endl;

  sprite.setTexture(texture);
  setPosition(position);

  label.setFont(font);
  label.setString(info);
  label.setCharacterSize(fontSize);
  label.setFillColor(Color::White);
  adjustSize();
}

Button::~Button() {
  deactivate();
  mouseSubject = nullptr;
}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void Button::activate() { mouseSubject->addObserver(this); }

void Button::deactivate() { mouseSubject->removeObserver(this); }

Drawable &Button::getDrawable() { return sprite; }

void Button::draw() {
  pGM->draw(this);
  pGM->draw(&label);
}

void Button::execute() { draw(); }

/* ------------------------------------------- */
/*              BUTTON FUNCTIONS               */
/* ------------------------------------------- */

bool Button::wasClicked() {
  if (clicked) {
    clicked = false;
    return true;
  }
  return false;
}

void Button::adjustSize() {
  FloatRect textBounds = label.getLocalBounds();
  Vector2f padding(40.f, 20.f);

  float buttonWidth = textBounds.width + padding.x;
  float buttonHeight = textBounds.height + padding.y;

  float scaleX = buttonWidth / texture.getSize().x;
  float scaleY = buttonHeight / texture.getSize().y;

  sprite.setScale(scaleX, scaleY);

  FloatRect spriteBounds = sprite.getLocalBounds();
  sprite.setOrigin(spriteBounds.width / 2.f, spriteBounds.height / 2.f);

  label.setOrigin(textBounds.left + textBounds.width / 2.f,
                  textBounds.top + textBounds.height / 2.f);

  sprite.setPosition(position);
  label.setPosition(position);
}

void Button::onMouseEvent(const Event::MouseMoveEvent &event) {
  Vector2f mousepos(static_cast<float>(event.x), static_cast<float>(event.y));
  FloatRect bounds = sprite.getGlobalBounds();
  if (bounds.contains(mousepos))
    setState(ButtonState::HOVERED);
  else
    setState(ButtonState::NORMAL);
}

void Button::onMouseEvent(const Event::MouseButtonEvent &event) {
  Vector2f mousePos(static_cast<float>(event.x), static_cast<float>(event.y));
  FloatRect bounds = sprite.getGlobalBounds();

  if (bounds.contains(mousePos) && event.button == Mouse::Left)
    clicked = true;
}

/* ------------------------------------------- */
/*                 GETS & SETS                 */
/* ------------------------------------------- */

void Button::setPosition(Vector2f pos) {
  position = pos;
  sprite.setPosition(pos);
  label.setPosition(pos);
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
