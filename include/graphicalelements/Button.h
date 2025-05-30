#ifndef BUTTON_H
#define BUTTON_H
#include "../entities/Ente.h"
#include "MouseSubject.h"


enum class ButtonState {
    NORMAL,
    HOVERED,
    PRESSED
};

class Button : public Ente, public MouseObserver {
private:
    Texture hoverTexture;
    Texture pressedTexture;
    Font font;
    Text label;
    unsigned int fontSize;
    Vector2f position;
    ButtonState state;
    MouseSubject* mouseSubject;

public:
    Button(const string fontPath, const string info, const string normalTexturePath, 
           const string hoveredTexturePath, const string pressedTexturePath, MouseSubject* subject, 
           unsigned int fontSize = 20, Vector2f position = Vector2f(0.f, 0.f));
    virtual ~Button();
    void setPosition(Vector2f pos);
    Vector2f getPosition() const;
    void setState(ButtonState newState);
    ButtonState getState() const;
    void draw() override;
    Drawable& getDrawable() override;
    void execute() override;
    void adjustSize();
    void handleMouseInput(const Vector2f& mousePosition);
    void onMouseEvent(const Event::MouseMoveEvent& event) override;
};


#endif
