#include "TitleScreen.h"



#include <chrono>
#include <iostream>

using namespace std::chrono;
using namespace std;


TitleScreen::TitleScreen()
{}


void TitleScreen::begin()
{
    release = false;

    printf("Event dispatcher added to this\n");
    EventDispatcher::getInstance().addEventListener(this, KeyDownEvent::ESC_DOWN_EVENT);
    printf("Event dispatcher added to this\n");
    selection_menu_base = std::make_shared<SelectionMenuBase>();
	selection_menu_base->width = 600;
	selection_menu_base->height = 500;
	container->addChild(selection_menu_base);
    printf("Added to child\n");

	selection_resume_option = std::make_shared<SelectionMenuOption>(SelectionMenuOption::RESUME, "Resume");
	printf("Resume option\n");
    selection_resume_option->width = 200;
	selection_resume_option->height = 50;
	selection_resume_option->position = {200, 200};
	selection_resume_option->alpha = 0;
	selection_menu_base->addChild(selection_resume_option);
    printf("Selection menu add child\n");

	selection_quit_option = std::make_shared<SelectionMenuOption>(SelectionMenuOption::QUIT, "Quit");
    printf("Quit option\n");
	selection_quit_option->width = 200;
	selection_quit_option->height = 50;
	selection_quit_option->position = {200, 300};
	selection_quit_option->alpha = 0;
	selection_menu_base->addChild(selection_quit_option);
    printf("Quit child added\n");

	EventDispatcher::getInstance().addEventListener(this->selection_menu_base.get(), KeyDownEvent::ESC_DOWN_EVENT);
	EventDispatcher::getInstance().addEventListener(this->selection_resume_option.get(), MouseDownEvent::MOUSE_DOWN_EVENT);
	EventDispatcher::getInstance().addEventListener(this->selection_quit_option.get(), MouseDownEvent::MOUSE_DOWN_EVENT);

    while(release == false)
    {

    }
    

}



void TitleScreen::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) {
    
}

void TitleScreen::draw(AffineTransform& at) {
    
}

void TitleScreen::handleEvent(Event* e)
{
    if (e->getType() == KeyDownEvent::ESC_DOWN_EVENT){
    // printf("Escape event\n");
    release = true;

    }   
}