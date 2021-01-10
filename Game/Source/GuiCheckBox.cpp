#include "GuiCheckBox.h"
#include "App.h"
#include "Input.h"

GuiCheckBox::GuiCheckBox(uint32 id, SDL_Rect bounds, const char* text) : GuiControl(GuiControlType::CHECKBOX, id)
{
    this->bounds = bounds;
    this->text = text;
    this->checked = false;
    this->id = id;
}

GuiCheckBox::~GuiCheckBox()
{
}

bool GuiCheckBox::Update(float dt)
{
    if (state != GuiControlState::DISABLED)
    {
        int mouseX, mouseY;
        app->input->GetMousePosition(mouseX, mouseY);

        // Check collision between mouse and button bounds
        if ((mouseX > bounds.x) && (mouseX < (bounds.x + bounds.w)) &&
            (mouseY > bounds.y) && (mouseY < (bounds.y + bounds.h)))
        {
            state = GuiControlState::FOCUSED;

            if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
            {
                state = GuiControlState::PRESSED;
            }

            // If mouse button pressed -> Generate event!
            if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
            {
                checked = !checked;
                NotifyObserver();
            }
        }
        else state = GuiControlState::NORMAL;
    }

    return false;
}

bool GuiCheckBox::DrawDebug()
{
    // Draw the right button depending on state
    switch (state)
    {
    case GuiControlState::NORMAL:
    {
        if (app->render->guiDebug)
        {
            if (checked)
            {
                app->render->DrawRectangle(bounds, 0, 255, 0, 255); // Green
            }
            else
            {
                app->render->DrawRectangle(bounds, 0, 255, 0, 150); // Light green
            }
        }

        break;
    }

    case GuiControlState::FOCUSED:
    {
        if (app->render->guiDebug)
        {
            if (checked)
            {
                app->render->DrawRectangle(bounds, 255, 255, 0, 255); // Yellow
            }
            else
            {
                app->render->DrawRectangle(bounds, 250, 250, 210, 255); // Light yellow
            }
        }

        break;
    }

    case GuiControlState::PRESSED:
    {
        if (app->render->guiDebug)
        {
            if (checked)
            {
                app->render->DrawRectangle(bounds, 255, 0, 0, 255); // Red
            }
            else
            {
                app->render->DrawRectangle(bounds, 255, 0, 0, 150); // Light red
            }
        }

        break;
    }

    default:
        break;
    }

    return false;
}

bool GuiCheckBox::DrawTexture()
{
    switch (state)
    {
    case GuiControlState::NORMAL:
    {
        if (checked)
        {
            app->render->DrawTexture(this->texture, this->bounds.x, this->bounds.y, &this->anim.frames[0]); // Normal with tick
        }
        else
        {
            app->render->DrawTexture(this->texture, this->bounds.x, this->bounds.y, &this->anim.frames[1]); // Normal without tick
        }
        break;
    }
    case GuiControlState::FOCUSED:
    {
        if (checked)
        {
            app->render->DrawTexture(this->texture, this->bounds.x, this->bounds.y, &this->anim.frames[2]); // Focused with tick
        }
        else
        {
            app->render->DrawTexture(this->texture, this->bounds.x, this->bounds.y, &this->anim.frames[3]); // Focused without tick
        }
        break;
    }
    case GuiControlState::PRESSED:
    {
        if (checked)
        {
            app->render->DrawTexture(this->texture, this->bounds.x, this->bounds.y, &this->anim.frames[4]); // Pressed with tick
        }
        else
        {
            app->render->DrawTexture(this->texture, this->bounds.x, this->bounds.y, &this->anim.frames[5]); // Pressed without tick
        }
        break;
    }
    }
    return true;
}
