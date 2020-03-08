#include "Editor.h"

#include "../engine/events/DragEvent.h"

#include <cmath>
#include <iostream>

namespace fs = std::filesystem;

using namespace std;

Editor::Editor()
    : Editor("./resources/scene/blank.json") {}

Editor::Editor(const string& sceneToLoad)
    : Game(1200, 800) {
    initSDL();

    instance = this;
    curScene = new Scene();

    camera = new Camera();
    camera->position = {this->windowWidth / 2, this->windowHeight / 2};
    camera->pivot = {this->windowWidth / 2, this->windowHeight / 2};
    instance->addChild(camera);

    curScene->loadScene(sceneToLoad);

    camera->addChild(curScene);

    crosshair = new Crosshair();
    crosshair->position = {0, 0};
    crosshair->width = crosshair->height = 100;
    crosshair->pivot = {50, 50};

    camera->addChild(crosshair);

    this->dispatcher.addEventListener(this, MouseDownEvent::MOUSE_DOWN_EVENT);
    this->dispatcher.addEventListener(this, DragEvent::DRAG_EVENT);
    this->dispatcher.addEventListener(this, MouseUpEvent::MOUSE_UP_EVENT);

    assets = new DisplayObject("assets");
    assets_dos = new DisplayObject("assets_dos");

    setupfiles("./resources/assets");
}

void Editor::setupfiles(const string& path) {
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.path() == "./resources/assets/Animated_Sprites") {
            for (const auto& AS : fs::directory_iterator(entry.path())) {
                AnimatedSprite* temp = new AnimatedSprite(AS.path().stem().string());

                for (const auto& anim : fs::directory_iterator(AS.path())) {
                    // temp->
                }

                aSprites.push_back(temp);
            }
        } else if (entry.path() == "./resources/assets/Display_Objects") {
            for (const auto& DO : fs::directory_iterator(entry.path())) {
                dos.push_back(new DisplayObject(DO.path().stem().string(), DO.path().string(), assets_renderer));
            }
        } else if (entry.path() == "./resources/assets/Sprites") {
            for (const auto& S : fs::directory_iterator(entry.path())) {
                // std::cout << S.path() << std::endl;
            }
        }
    }
    for (int i = 0; i < dos.size(); ++i) {
        dos[i]->position.x = i % 2 == 0 ? 0 : 150;
        dos[i]->position.y = (i / 2) * 150;
        dos[i]->height = 150;
        dos[i]->width = 150;
        assets_dos->addChild(dos[i]);
    }
    assets->addChild(assets_dos);
}

void Editor::update(std::unordered_set<SDL_Scancode> pressedKeys) {
    // Move
    if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
        int f = (int)5 * (1 / camera->scaleX);
        if (f < 1) {
            f = 1;
        }
        camera->panRight(f);
    }
    if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
        int f = (int)5 * (1 / camera->scaleX);
        if (f < 1) {
            f = 1;
        }
        camera->panLeft(f);
    }
    if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
        int f = (int)5 * (1 / camera->scaleY);
        if (f < 1) {
            f = 1;
        }
        camera->panDown(f);
    }
    if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
        int f = (int)5 * (1 / camera->scaleY);
        if (f < 1) {
            f = 1;
        }
        camera->panUp(f);
    }

    // Zoom
    if (pressedKeys.find(SDL_SCANCODE_X) != pressedKeys.end()) {
        camera->zoomIn(1.1);
    }
    if (pressedKeys.find(SDL_SCANCODE_Z) != pressedKeys.end()) {
        camera->zoomOut(1.1);
    }

    if (pressedKeys.find(SDL_SCANCODE_TAB) != pressedKeys.end() &&
        prevKeys.find(SDL_SCANCODE_TAB) == prevKeys.end()) {
        if (!grabbedObj) {
            if (pressedKeys.find(SDL_SCANCODE_LSHIFT) != pressedKeys.end() ||
                pressedKeys.find(SDL_SCANCODE_RSHIFT) != pressedKeys.end()) {
                if (obj_ind > 1) {
                    printf("obj_ind == %d\n", obj_ind);

                    DisplayObject* myobjc = crosshair->getChild(0);
                    crosshair->removeImmediateChild(myobjc);

                    --obj_ind;
                    Sprite* newobj = new Sprite("newobject", all_sprites[obj_ind]);
                    crosshair->addChild(newobj);
                    hasChild = true;
                } else {
                    if (obj_ind == 1) {
                        obj_ind = 0;
                        DisplayObject* myobjc = crosshair->getChild(0);
                        crosshair->removeImmediateChild(myobjc);
                        hasChild = false;
                    } else {
                        obj_ind = all_sprites.size() - 1;
                        Sprite* newobj = new Sprite("newobject", all_sprites[obj_ind]);
                        crosshair->addChild(newobj);
                        hasChild = true;
                    }
                }
            } else {
                if (obj_ind < all_sprites.size() - 1) {
                    if (obj_ind > 0) {
                        DisplayObject* myobjc = crosshair->getChild(0);
                        crosshair->removeImmediateChild(myobjc);
                    }
                    obj_ind++;
                    Sprite* newobj = new Sprite("newobject", all_sprites[obj_ind]);
                    crosshair->addChild(newobj);
                    hasChild = true;
                } else {
                    obj_ind = 0;
                    DisplayObject* myobjc = crosshair->getChild(0);
                    crosshair->removeImmediateChild(myobjc);
                    hasChild = false;
                }
            }
        }
    }

    if (pressedKeys.find(SDL_SCANCODE_BACKSPACE) != pressedKeys.end()) {
        if (obj_ind != 0) {
            obj_ind = 0;
            DisplayObject* myobjc = crosshair->getChild(0);
            crosshair->removeImmediateChild(myobjc);
            hasChild = false;
        }
    }

    if (pressedKeys.find(SDL_SCANCODE_RETURN) != pressedKeys.end()) {
        if (hasChild || grabbedObj) {
            DisplayObject* myobj = crosshair->getChild(0);
            DisplayObject* newobj = new DisplayObject(*myobj);
            newobj->position = crosshair->position;
            curScene->addChild(newobj);
            crosshair->removeImmediateChild(myobj);
            hasChild = false;
            obj_ind = 0;
            grabbedObj = false;
        }
    }

    if (SDL_GetModState() & KMOD_CTRL && pressedKeys.find(SDL_SCANCODE_X) != pressedKeys.end() &&
        prevKeys.find(SDL_SCANCODE_X) == prevKeys.end()) {
        this->cut(this->selected);
    }

    if (SDL_GetModState() & KMOD_CTRL && pressedKeys.find(SDL_SCANCODE_C) != pressedKeys.end() &&
        prevKeys.find(SDL_SCANCODE_C) == prevKeys.end()) {
        this->copy(this->selected);
    }

    if (SDL_GetModState() & KMOD_CTRL && pressedKeys.find(SDL_SCANCODE_V) != pressedKeys.end() &&
        prevKeys.find(SDL_SCANCODE_V) == prevKeys.end()) {
        this->paste();
    }

    // Pivot
    if (pressedKeys.find(SDL_SCANCODE_I) != pressedKeys.end()) {
        heldPivot.y -= 5;
    }
    if (pressedKeys.find(SDL_SCANCODE_J) != pressedKeys.end()) {
        heldPivot.x -= 5;
    }
    if (pressedKeys.find(SDL_SCANCODE_K) != pressedKeys.end()) {
        heldPivot.y += 5;
    }
    if (pressedKeys.find(SDL_SCANCODE_L) != pressedKeys.end()) {
        heldPivot.x += 5;
    }
    if (hasChild) {
        crosshair->getChild(0)->pivot = heldPivot;
    }

    // Rotation
    if (pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end()) {
        heldRotation -= 0.05;
    }
    if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {
        heldRotation += 0.05;
    }
    if (hasChild) {
        crosshair->getChild(0)->rotation = heldRotation;
    }

    // Scaling
    if (pressedKeys.find(SDL_SCANCODE_MINUS) != pressedKeys.end()) {
        heldScaleX -= 0.05;
        heldScaleY -= 0.05;
    }
    if (pressedKeys.find(SDL_SCANCODE_EQUALS) != pressedKeys.end()) {
        heldScaleX += 0.05;
        heldScaleY += 0.05;
    }
    if (pressedKeys.find(SDL_SCANCODE_O) != pressedKeys.end()) {
        heldScaleX -= 0.05;
    }
    if (pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end()) {
        heldScaleX += 0.05;
    }
    if (pressedKeys.find(SDL_SCANCODE_LEFTBRACKET) != pressedKeys.end()) {
        heldScaleY -= 0.05;
    }
    if (pressedKeys.find(SDL_SCANCODE_RIGHTBRACKET) != pressedKeys.end()) {
        heldScaleY += 0.05;
    }
    if (hasChild) {
        crosshair->getChild(0)->scaleX = heldScaleX;
        crosshair->getChild(0)->scaleY = heldScaleY;
    }

    if (pressedKeys.find(SDL_SCANCODE_Y) != pressedKeys.end()) {
        cout << "X: " << crosshair->getGlobalPosition().x << " Y: " << crosshair->getGlobalPosition().y << endl;
    }

    if (pressedKeys.find(SDL_SCANCODE_U) != pressedKeys.end()) {
        cout << "X: " << crosshair->dstrect.x << " Y: " << crosshair->dstrect.y << endl;
    }

    if ((pressedKeys.find(SDL_SCANCODE_LCTRL) != pressedKeys.end() ||
         pressedKeys.find(SDL_SCANCODE_RCTRL) != pressedKeys.end()) &&
        pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()) {
        string tmp;
        cin >> tmp;
        curScene->saveScene(tmp);
    }

    if (pressedKeys.find(SDL_SCANCODE_R) != pressedKeys.end()) {
        heldPosition = {0, 0};
        heldPivot = {0, 0};
        heldScaleX = 1.0;
        heldScaleY = 1.0;
        heldRotation = 0.0;
        if (hasChild) {
            DisplayObject* tmp = crosshair->getChild(0);
            tmp->position = heldPosition;
            tmp->pivot = heldPivot;
            tmp->scaleX = heldScaleX;
            tmp->scaleY = heldScaleY;
            tmp->rotation = heldRotation;
        }
    }

    prevKeys = pressedKeys;

    Game::update(pressedKeys);
}

void Editor::draw(AffineTransform& at) {
    Game::draw(at);

    SDL_SetRenderDrawColor(Editor::assets_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(Editor::assets_renderer);
    assets->draw(at, Editor::assets_renderer);
    SDL_RenderPresent(Editor::assets_renderer);

    SDL_SetRenderDrawColor(Editor::edit_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(Editor::edit_renderer);
    SDL_RenderPresent(Editor::edit_renderer);
}

void Editor::initSDL() {
    assets_window = SDL_CreateWindow("Assets", 0, 500, 300, 450, SDL_WINDOW_ALLOW_HIGHDPI);

    edit_window = SDL_CreateWindow("Edit", 0, 0, 300, 450, SDL_WINDOW_ALLOW_HIGHDPI);

    assets_renderer = SDL_CreateRenderer(assets_window, -1, 0);
    edit_renderer = SDL_CreateRenderer(edit_window, -1, 0);
}

void Editor::draw_post() {
    SDL_SetRenderDrawColor(Game::renderer, 90, 90, 90, SDL_ALPHA_OPAQUE);

    // Draw gridlines.
    int startX = this->camera->getGlobalPosition().x % lround(80 * this->camera->getZoom());
    for (int x = startX; x < this->windowWidth; x += lround(80 * this->camera->getZoom())) {
        if (x - this->camera->getGlobalPosition().x == 0) {
            SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        }
        SDL_RenderDrawLine(Game::renderer, x, 0, x, this->windowHeight);
        if (x - this->camera->getGlobalPosition().x == 0) {
            SDL_SetRenderDrawColor(Game::renderer, 90, 90, 90, SDL_ALPHA_OPAQUE);
        }
    }

    int startY = this->camera->getGlobalPosition().y % lround(80 * this->camera->getZoom());
    for (int y = startY; y < this->windowHeight; y += lround(80 * this->camera->getZoom())) {
        if (y - this->camera->getGlobalPosition().y == 0) {
            SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        }
        SDL_RenderDrawLine(Game::renderer, 0, y, this->windowWidth, y);
        if (y - this->camera->getGlobalPosition().y == 0) {
            SDL_SetRenderDrawColor(Game::renderer, 90, 90, 90, SDL_ALPHA_OPAQUE);
        }
    }

    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    for (DisplayObject* object : this->selected) {
        SDL_RenderDrawRect(Game::renderer, &object->dstrect);
    }
}

void Editor::cut(unordered_set<DisplayObject*> objects) {
    cout << "Not implemented :(" << endl;
    // TODO: Need to somehow remove elements from scene
    /*this->copied.clear();
    for (DisplayObject* object : objects) {
        this->copied.insert(object);
    }*/
}

void Editor::copy(unordered_set<DisplayObject*> objects) {
    this->copied.clear();
    for (DisplayObject* object : objects) {
        // Make the copy now so that future changes won't affect the copy
        DisplayObject* copy = new DisplayObject(*object);

        // Offset a bit
        copy->position.x += 16;
        copy->position.y += 16;

        this->copied.insert(copy);
    }
}

void Editor::paste() {
    this->selected.clear();
    for (DisplayObject* object : this->copied) {
        // TODO: This always inserts at the root.
        // Should that always be the case?
        this->curScene->addChild(object);
        this->selected.insert(object);
    }

    // Pre-emptively get ready to copy the same objects again
    this->copy(this->copied);
}

void Editor::handleEvent(Event* e) {
    if (e->getType() == MouseDownEvent::MOUSE_DOWN_EVENT) {
        MouseDownEvent* event = static_cast<MouseDownEvent*>(e);
        if (!this->onMouseDown(this, event)) {
            this->selected.clear();
        }
    } else if (e->getType() == DragEvent::DRAG_EVENT) {
        DragEvent* event = static_cast<DragEvent*>(e);
        for (DisplayObject* object : this->selected) {
            object->position.x += event->xrel;
            object->position.y += event->yrel;
        }
    } else if (e->getType() == MouseUpEvent::MOUSE_UP_EVENT) {
        MouseUpEvent* event = static_cast<MouseUpEvent*>(e);
        this->onMouseUp(this, event);
    }
}

bool Editor::onMouseDown(DisplayObject* object, MouseDownEvent* event) {
    // Reverse iterator to check the topmost objects first
    for (auto it = object->children.crbegin(); it != object->children.crend(); it++) {
        if (this->onMouseDown(*it, event)) {
            return true;
        }
    }

    if (object->dstrect.x <= event->x && event->x <= object->dstrect.x + object->dstrect.w &&
        object->dstrect.y <= event->y && event->y <= object->dstrect.y + object->dstrect.h) {
        if (!(event->modifiers & KMOD_CTRL)) {
            // If this object is not already selected and we are not ctrl-clicking,
            // unselect everything
            if (this->selected.find(object) == this->selected.cend()) {
                this->selected.clear();
            }

            // Then mark this object as selected
            this->selected.insert(object);
        }
        return true;
    }
    return false;
}

bool Editor::onMouseUp(DisplayObject* object, MouseUpEvent* event) {
    // Reverse iterator to check the topmost objects first
    for (auto it = object->children.crbegin(); it != object->children.crend(); it++) {
        if (this->onMouseUp(*it, event)) {
            return true;
        }
    }

    if (object->dstrect.x <= event->x && event->x <= object->dstrect.x + object->dstrect.w &&
        object->dstrect.y <= event->y && event->y <= object->dstrect.y + object->dstrect.h) {
        if (!(event->modifiers & KMOD_CTRL)) {
            // If this object is already selected and we are not ctrl-clicking,
            // clear everything and select ourselves
            if (this->selected.find(object) != this->selected.cend()) {
                this->selected.clear();
                this->selected.insert(object);
            }
        } else {
            if (this->selected.find(object) != this->selected.cend()) {
                // If ctrl-click and we are already selected, unselect only ourselves
                this->selected.erase(object);
            } else {
                // If ctrl-click and we are not already selected, select ourselves
                this->selected.insert(object);
            }
        }
        return true;
    }

    return false;
}