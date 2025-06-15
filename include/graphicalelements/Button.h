#ifndef BUTTON_H
#define BUTTON_H
#include "../entities/Ente.h"
#include "MouseSubject.h"

enum class ButtonState { NORMAL, HOVERED };

class Button : public Ente, public MouseObserver {

    private:
        /* ----- VARIABLES ----- */
        MouseSubject *mouseSubject;

        /* ------ STATUS ------- */
        Texture hoverTexture;
        Font font;
        Text label;
        unsigned int fontSize;
        Vector2f position;

        /* ------ FLAGS ------- */
        ButtonState state;
        bool clicked;

    public:
        Button(const string fontPath, const string info,
                const string normalTexturePath,
                const string hoveredTexturePath, MouseSubject *subject,
                unsigned int fontSize = 20, Vector2f position = Vector2f(0.f, 0.f));
        virtual ~Button();

        /* ---- OWN FUNCTIONS ---- */
        void activate();
        void deactivate();
        void execute() override;
        void draw() override;
        Drawable &getDrawable() override;

        /* ----- GETS & SETS ----- */
        void setPosition(Vector2f pos);
        Vector2f getPosition() const;
        void setState(ButtonState newState);
        ButtonState getState() const;

        /* ----- BUTTON ----- */
        void adjustSize();
        void onMouseEvent(const Event::MouseMoveEvent &event) override;
        void onMouseEvent(const Event::MouseButtonEvent& event) override;
        bool wasClicked();
};

#endif
