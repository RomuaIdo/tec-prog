#include "../../include/graphicalelements/Button.h"

ge::Button::Button(const string fontPath, const string info,
               const string normalTexturePath, const string hoveredTexturePath,
               MouseSubject *subject, unsigned int fontSize, Vector2f position)
    : Ente(), mouseSubject(subject), fontSize(fontSize), position(position),
      state(ButtonState::NORMAL), clicked(false) {
  
  texture = pGM->loadTexture(normalTexturePath);
  hoverTexture = pGM->loadTexture(hoveredTexturePath);

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

ge::Button::~Button() {
  deactivate();
  mouseSubject = nullptr;
}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void ge::Button::activate() { mouseSubject->addObserver(this); }

void ge::Button::deactivate() { mouseSubject->removeObserver(this); }

Drawable& ge::Button::getDrawable() { return sprite; }

void ge::Button::draw() {
  pGM->draw(this);
  pGM->draw(&label);
}

void ge::Button::execute() { draw(); }

/* ------------------------------------------- */
/*              BUTTON FUNCTIONS               */
/* ------------------------------------------- */

bool ge::Button::wasClicked() {
  if (clicked) {
    clicked = false;
    return true;
  }
  return false;
}

void ge::Button::adjustSize() {
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

void ge::Button::onMouseEvent(const Event::MouseMoveEvent &event) {
    RenderWindow* window = pGM->getWindow();
    Vector2f mousepos = window->mapPixelToCoords(Vector2i(event.x, event.y));
    
    FloatRect bounds = sprite.getGlobalBounds();

  if (bounds.contains(mousepos))
    setState(ButtonState::HOVERED);
  else
    setState(ButtonState::NORMAL);
}

void ge::Button::onMouseEvent(const Event::MouseButtonEvent &event) {
    RenderWindow* window = pGM->getWindow();
    Vector2f mousePos = window->mapPixelToCoords(Vector2i(event.x, event.y));
    
    FloatRect bounds = sprite.getGlobalBounds();

 
  if (bounds.contains(mousePos) && event.button == Mouse::Left)
    clicked = true;
}

/* ------------------------------------------- */
/*                 GETS & SETS                 */
/* ------------------------------------------- */

void ge::Button::setPosition(Vector2f pos) {
  position = pos;
  sprite.setPosition(pos);
  label.setPosition(pos);
}

Vector2f ge::Button::getPosition() const { return position; }

void ge::Button::setState(ButtonState newState) {
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

ge::ButtonState ge::Button::getState() const { return state; }
