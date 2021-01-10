#ifndef __GUIBUTTON_H__
#define __GUIBUTTON_H__

#include "GuiControl.h"

#include "Point.h"
#include "SString.h"

class GuiButton : public GuiControl
{
public:

    GuiButton(uint32 id, SDL_Rect bounds, SDL_Texture* tex);
    virtual ~GuiButton();

    bool Update(float dt);
    bool Draw();

private:

};

#endif

