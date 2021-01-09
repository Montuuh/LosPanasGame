#include "GuiButton.h"
#include "Input.h"
#include "App.h"
#include "Render.h"
GuiButton::GuiButton(int id, SDL_Rect bounds) : GuiControl(GuiControlType::BUTTON, id)
{
    this->bounds = bounds;
    this->texture = texture;
}

GuiButton::~GuiButton()
{
}

bool GuiButton::Update(float dt)
{
    if (state != GuiControlState::DISABLED)
    {
        int mouseX, mouseY;
        app->input->GetMousePosition(mouseX, mouseY);

        // Check collision between mouse and button bounds
        if ((mouseX > bounds.x) && (mouseX < (bounds.x + bounds.w)) &&
            (mouseY > bounds.y) && (mouseY < (bounds.y + bounds.h)))
        {
            if (state == GuiControlState::NORMAL)
            {
                //app->audio->PlayFx(MouseOver){
            }
            if (state != GuiControlState::PRESSED) 
            {
                state = GuiControlState::FOCUSED;               
            }
            else
            {
                //app->audio->PlayFx(Pressed)
            }

            if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
            {
                state = GuiControlState::PRESSED;
            }

            // If mouse button pressed -> Generate event!
            if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
            {
                NotifyObserver();
            }
        }
        else state = GuiControlState::NORMAL;
    }

    return false;
}

bool GuiButton::Draw()
{
    // Draw the right button depending on state
    switch (state)
    {
    case GuiControlState::DISABLED: //render->DrawRectangle(bounds, 60, 60, 60, 255, true, false); //Grey
        break;
    case GuiControlState::NORMAL: //render->DrawRectangle(bounds, 0, 255, 0, 255, true, false); //Green
        //app->render->DrawTexture(texture, bounds.x, bounds.y, { 480, 319, 332, 61 });
        if (app->render->guiDebug)
        {
            app->render->DrawRectangle({ 480, 319, 332, 61 }, 0, 255, 0, 200);
        }
        break;
    case GuiControlState::FOCUSED: //render->DrawRectangle(bounds, 255, 255, 0, 255, true, false); //Yellow
        app->render->DrawTexture(texture, bounds.x, bounds.y, &SDL_Rect({ 0,0,9,7 }));
        break;
    case GuiControlState::PRESSED: //render->DrawRectangle(bounds, 0, 255, 255, 255, true, false);//Cyan
        app->render->DrawTexture(texture, bounds.x, bounds.y, &SDL_Rect({ 9,0,9,7 }));
        break;
    case GuiControlState::SELECTED: //render->DrawRectangle(bounds, 255, 0, 0, 255, true, false);//Red
        app->render->DrawTexture(texture, bounds.x, bounds.y, &SDL_Rect({ 9,0,9,7 }));
        break;
    default:
        break;
    }

    return false;
}
