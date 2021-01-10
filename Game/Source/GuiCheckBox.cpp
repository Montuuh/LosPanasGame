#include "GuiCheckBox.h"
#include "App.h"

GuiCheckBox::GuiCheckBox(uint32 id, SDL_Rect bounds, const char* text) : GuiControl(GuiControlType::CHECKBOX, id)
{
    this->bounds = bounds;
    this->text = text;
    this->checked = false;
}

GuiCheckBox::~GuiCheckBox()
{
}

bool GuiCheckBox::Update(Input* input, float dt)
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
            }

            // If mouse button pressed -> Generate event!
            if (input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
            {
                checked = !checked;
                NotifyObserver();
            }
        }
        else state = GuiControlState::NORMAL;
    }

    return false;
}

bool GuiCheckBox::Draw(Render* render)
{
    // Draw the right button depending on state
    switch (state)
    {
        case GuiControlState::DISABLED:
        {
            if (checked) render->DrawRectangle(bounds, 100, 100, 100, 255);
            else render->DrawRectangle(bounds, 100, 100, 100, 255);
        } 
        break;
        case GuiControlState::NORMAL:
        {
            if (app->render->guiDebug)
            {
                app->render->DrawRectangle(bounds, 0, 255, 0, 100);
            }
        } 
        break;
        case GuiControlState::FOCUSED:
        {
            if (app->render->guiDebug)
            {
                app->render->DrawRectangle(bounds, 225, 255, 0, 100);
            }
        }
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

bool GuiCheckBox::DrawTexture(Render* render)
{
    /*switch (state)
    {
        case GuiControlState::NORMAL:
        {
            if (checked)
            {
                render->DrawTexture(this->texture, this->bounds.x, this->bounds.y, &this->anim.frames[0], 0.0f);
            }
            else
            {
                           
            }    
            break;
        }
    }*/
    return true;
}
