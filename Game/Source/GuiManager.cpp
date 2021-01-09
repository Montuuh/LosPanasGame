#include "GuiManager.h"
#include "App.h"
#include "GuiCheckBox.h"
#include "GuiSlider.h"
#include "GuiButton.h"

GuiManager::GuiManager() : Module()
{
	name.Create("guimanager");
}

GuiManager::~GuiManager()
{

}

bool GuiManager::Awake(pugi::xml_node& config)
{
	return true;
}

bool GuiManager::Start()
{
	return true;
}

bool GuiManager::Update(float dt)
{
	accumulatedTime += dt;
	if (accumulatedTime >= updateMsCycle) doLogic = true;

	UpdateAll(dt, doLogic);

	if (doLogic == true)
	{
		accumulatedTime = 0.0f;
		doLogic = false;
	}

	return true;
}

bool GuiManager::PostUpdate()
{
	DrawAll();
	return true;
}

bool GuiManager::CleanUp()
{
	return true;
}

GuiControl* GuiManager::CreateGuiControl(GuiControlType type)
{
	GuiControl* control = nullptr;

	switch (type)
	{
		case GuiControlType::BUTTON:
			control = new GuiButton(id, { 1280 / 2 - 300 / 2, 200, 20, 20 }, "EXIT");
			break;
		case GuiControlType::CHECKBOX:
			control = new GuiCheckBox(id, { 1280 / 2 - 300 / 2, 200, 20, 20 }, "EXIT");
			break;
		case GuiControlType::SLIDER:
			control = new GuiSlider(id, { 1280 / 2 - 300 / 2, 200, 20, 20 }, "EXIT");
			break;
		default: break;
	}
	id++;

	if (control != nullptr)
	{
		controls.Add(control);
	}
	return control;
}

void GuiManager::AddGuiControl(GuiControl* control)
{
	if (control != nullptr) controls.Add(control);
}

void GuiManager::DestroyGuiControl(GuiControl* control)
{
	//controls.Del(control);
}

void GuiManager::UpdateAll(float dt, bool doLogic)
{
	if (doLogic == true)
	{
		for (int i = 0; i < controls.Count(); i++)
		{
			controls[i]->Update(app->input, dt);
		}
	}
}

void GuiManager::DrawAll()
{
	for (int i = 0; i < controls.Count(); i++)
	{
		controls[i]->Draw(app->render);
	}
}