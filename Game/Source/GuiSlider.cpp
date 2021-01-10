#include "GuiSlider.h"
#include "App.h"
#include "GuiManager.h"
#include "Audio.h"
#include "Window.h"
#include "Render.h"
#include "Input.h"
#include "TitleScreen.h"


GuiSlider::GuiSlider(uint32 id, SDL_Rect bounds, const char* texture) : GuiControl(GuiControlType::SLIDER, id)
{
    this->bounds = bounds;
    this->text = texture;
    slider.x = bounds.x;
    slider.y = bounds.y;
    slider.w = 20;
    slider.h = bounds.h;
}

GuiSlider::~GuiSlider()
{
}

bool GuiSlider::Update(Input* input, float dt)
{
    if (state != GuiControlState::DISABLED)
    {
        int mouseX, mouseY;
        input->GetMousePosition(mouseX, mouseY);

        // Check collision between mouse and button bounds
        if ((mouseX > bounds.x) && (mouseX < (bounds.x + bounds.w)) &&
            (mouseY > bounds.y) && (mouseY < (bounds.y + bounds.h)))
        {
            state = GuiControlState::FOCUSED;

            if (input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
            {
                state = GuiControlState::PRESSED;
                int posX;
                int posY;
                input->GetMousePosition(posX, posY);
                slider.x = posX;
                    
            }
            // TODO.
        }
        else state = GuiControlState::NORMAL;
    }

    return false;
}

bool GuiSlider::Draw(Render* render)
{
    // Draw the right button depending on state
    switch (state)
    {
    case GuiControlState::DISABLED: render->DrawRectangle(bounds, 100, 100, 100, 255);
        break;
    case GuiControlState::NORMAL: render->DrawRectangle(bounds, 0, 255, 0, 255);
        break;
    case GuiControlState::FOCUSED: render->DrawRectangle(bounds, 255, 255, 0, 255);
        break;
    case GuiControlState::PRESSED: render->DrawRectangle(bounds, 0, 255, 255, 255);
        break;
    case GuiControlState::SELECTED: render->DrawRectangle(bounds, 0, 255, 0, 255);
        break;
    default:
        break;
    }

    return false;
}
