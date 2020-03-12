#include "Editor.h"

#include "../engine/events/DragEvent.h"
#include "../engine/events/DragStartEvent.h"

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
    this->dispatcher.addEventListener(this, DragStartEvent::DRAG_START_EVENT);
    this->dispatcher.addEventListener(this, MouseUpEvent::MOUSE_UP_EVENT);
    this->dispatcher.addEventListener(this, MouseMotionEvent::MOUSE_MOTION_EVENT);
    this->dispatcher.addEventListener(this, WindowEnterEvent::WINDOW_ENTER_EVENT);    
    this->dispatcher.addEventListener(this, WindowExitEvent::WINDOW_EXIT_EVENT); 

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
    if (!(SDL_GetModState() & KMOD_CTRL) && pressedKeys.find(SDL_SCANCODE_X) != pressedKeys.end()) {
        camera->zoomIn(1.1);
    }
    if (!(SDL_GetModState() & KMOD_CTRL) && pressedKeys.find(SDL_SCANCODE_Z) != pressedKeys.end()) {
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

    if (SDL_GetModState() & KMOD_CTRL && pressedKeys.find(SDL_SCANCODE_D) != pressedKeys.end()){
        this->selected.clear();
        if (selectedAsset){
            curScene->removeImmediateChild(selectedAsset);
            selectedAsset = NULL;
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
        for (DisplayObject* object : this->selected) {
            cout << object->id << endl;
        }
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
    this->clearRenderers();
	DisplayObject::draw(at);

    assets->draw(at, Editor::assets_renderer);

	this->draw_post();
	this->presentRenderers();
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
    int startX = this->camera->getGlobalPosition().x % lround(Editor::GRID_SIZE * this->camera->getZoom());
    for (int x = startX; x < this->windowWidth; x += lround(Editor::GRID_SIZE * this->camera->getZoom())) {
        if (x - this->camera->getGlobalPosition().x == 0) {
            SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        }
        SDL_RenderDrawLine(Game::renderer, x, 0, x, this->windowHeight);
        if (x - this->camera->getGlobalPosition().x == 0) {
            SDL_SetRenderDrawColor(Game::renderer, 90, 90, 90, SDL_ALPHA_OPAQUE);
        }
    }

    int startY = this->camera->getGlobalPosition().y % lround(Editor::GRID_SIZE * this->camera->getZoom());
    for (int y = startY; y < this->windowHeight; y += lround(Editor::GRID_SIZE * this->camera->getZoom())) {
        if (y - this->camera->getGlobalPosition().y == 0) {
            SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        }
        SDL_RenderDrawLine(Game::renderer, 0, y, this->windowWidth, y);
        if (y - this->camera->getGlobalPosition().y == 0) {
            SDL_SetRenderDrawColor(Game::renderer, 90, 90, 90, SDL_ALPHA_OPAQUE);
        }
    }

    SDL_Renderer* tempR = Game::renderer;
    if (selectedAsset){
        tempR = assets_renderer;
    }
    
    SDL_SetRenderDrawColor(tempR, 255, 255, 255, SDL_ALPHA_OPAQUE);
    for (DisplayObject* object : this->selected) {
        SDL_RenderDrawRect(tempR, &object->dstrect);
    }
}

void Editor::clearRenderers(){
    Game::clearRenderers();

    SDL_SetRenderDrawColor(Editor::assets_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(Editor::assets_renderer);
    
    SDL_SetRenderDrawColor(Editor::edit_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(Editor::edit_renderer);
}

void Editor::presentRenderers(){
    Game::presentRenderers();
    SDL_RenderPresent(Editor::assets_renderer);
    SDL_RenderPresent(Editor::edit_renderer);
}

void Editor::cut(const unordered_set<DisplayObject*>& objects) {
    this->copied.clear();
    for (DisplayObject* object : objects) {
        DisplayObject* copy = new DisplayObject(*object);
        this->copied.insert(copy);
        object->removeThis();

        this->selected.erase(object);
        this->displacementX.erase(object);
        this->displacementY.erase(object);
    }
}

void Editor::copy(const unordered_set<DisplayObject*>& objects, bool keepHierarchy) {
    this->copied.clear();
    for (DisplayObject* object : objects) {
        // Make the copy now so that future changes won't affect the copy
        DisplayObject* copy = new DisplayObject(*object);

        // Offset a bit
        copy->position.x += 16;
        copy->position.y += 16;

        if (!keepHierarchy){
            copy->parent = NULL;
            copy->children.clear();
        }

        this->copied.insert(copy);

    }
    if (selectedAsset){
        selectedAsset = *copied.begin();
        curScene->addChild(selectedAsset);
    }
}

void Editor::paste(MouseDownEvent* event) {
    if (!event){
        this->selected.clear();
    }
    for (DisplayObject* object : this->copied) {
        // TODO: This always inserts at the root.
        // Should that always be the case?
        this->curScene->addChild(object);
        if (!event){
            this->selected.insert(object);
        } // else{
        //     object->position.x = -lround((1/camera->getZoom())*this->windowWidth  / 2);
        //     object->position.y = -lround((1/camera->getZoom())*this->windowHeight / 2);
        //     object->position.x += camera->pivot.x;
        //     object->position.x += lround(event->x*(1/camera->getZoom()));
        //     object->position.y += camera->pivot.y;
        //     object->position.y += lround(event->y*(1/camera->getZoom()));
        // }
    }

    // Pre-emptively get ready to copy the same objects again
    unordered_set<DisplayObject*> temp = this->copied;
    this->copy(temp);
}

void Editor::handleEvent(Event* e) {
    if (e->getType() == MouseDownEvent::MOUSE_DOWN_EVENT) {
        MouseDownEvent* event = static_cast<MouseDownEvent*>(e);
        if (event->wID == SDL_GetWindowID(assets_window)){
            assetsWindowActive = true;
            editWindowActive = mainWindowActive = false;

            DisplayObject* temp = NULL;
            if (!this->selected.empty()){
                temp = *(this->selected.begin());
            }
            this->selected.clear();
            if (selectedAsset){
                curScene->removeImmediateChild(selectedAsset);
                selectedAsset = NULL;
            }
            if (this->onMouseDown(assets->getChild(0), event)){
                if (*this->selected.begin() == temp){
                    this->selected.clear();
                } else{
                    this->copy(this->selected, false);
                    selectedAsset = *copied.begin();
                    selectedAsset->visible = false;
                    curScene->addChild(selectedAsset);
                }
            }

        } else if (event->wID == SDL_GetWindowID(edit_window)){
            editWindowActive = true;
            assetsWindowActive = mainWindowActive = false;

        } else{
            mainWindowActive = true;
            assetsWindowActive = editWindowActive = false;
            if (selectedAsset){
                this->paste(event);
                if (selectedAsset){
                    selectedAsset->position.x = -lround((1/camera->getZoom())*this->windowWidth  / 2);
                    selectedAsset->position.y = -lround((1/camera->getZoom())*this->windowHeight / 2);
                    selectedAsset->position.x += camera->pivot.x;
                    selectedAsset->position.x += lround(event->x*(1/camera->getZoom()));
                    selectedAsset->position.y += camera->pivot.y;
                    selectedAsset->position.y += lround(event->y*(1/camera->getZoom()));
                }
            } else if (!this->onMouseDown(this, event)) {
                this->selected.clear();
            }
        }
    } else if (e->getType() == DragStartEvent::DRAG_START_EVENT) {
        this->displacementX.clear();
        this->displacementY.clear();

        for (DisplayObject* object : this->selected) {
            this->displacementX.insert({object, 0.0});
            this->displacementY.insert({object, 0.0});
        }
    } else if (e->getType() == DragEvent::DRAG_EVENT) {
        DragEvent* event = static_cast<DragEvent*>(e);
        if (event->wID == SDL_GetWindowID(assets_window)){
            assetsWindowActive = true;
            editWindowActive = mainWindowActive = false;

        } else if (event->wID == SDL_GetWindowID(edit_window)){
            editWindowActive = true;
            assetsWindowActive = mainWindowActive = false;

        } else if (event->wID == SDL_GetWindowID(this->window) && !selectedAsset){
            mainWindowActive = true;
            assetsWindowActive = editWindowActive = false;

            for (DisplayObject* object : this->selected) {
                // Okay, this is convoluted. Here's a walkthrough...

                // Calculate movement threshold
                double threshold = this->camera->getZoom();
                if (!(event->modifiers & KMOD_ALT)) {
                    // Snap by the grid size if we are not holding alt
                    threshold *= Editor::GRID_SIZE;
                }

                // Add the relative movement generated by this drag event to the
                // total displacement that we need to move the object by
                this->displacementX.at(object) += event->xrel;
                this->displacementY.at(object) += event->yrel;

                // Move the object based on the current zoom level (pixel movement != screen movement),
                // being sure to truncate (round towards zero) the amount we move by.
                // Snap by the threshold (but use raw pixels as the AffineTransform will handle zoom).
                // We must truncate and not round() in cases such as zoom = 2.0, where rounding causes
                // us to *always* round away from zero, resulting in mouse/object de-sync.
                object->position.x += static_cast<int>((threshold / this->camera->getZoom()) * trunc(this->displacementX.at(object) / threshold));
                object->position.y += static_cast<int>((threshold / this->camera->getZoom()) * trunc(this->displacementY.at(object) / threshold));

                // Now that we've moved the object, reset the displacement we need to move by
                // for the _next_ iteration by calculating the unused remainder.
                // We use fmod() and not remainder() because the return value of remainder() is
                // kept within 1/2 the denominator (in other words, it is (-1/2 * denom, 1/2 * denom]),
                // whereas the result of fmod is [0, denom)
                this->displacementX.at(object) = fmod(this->displacementX.at(object), threshold);
                this->displacementY.at(object) = fmod(this->displacementY.at(object), threshold);
            }
        }
    } else if (e->getType() == MouseUpEvent::MOUSE_UP_EVENT) {
        MouseUpEvent* event = static_cast<MouseUpEvent*>(e);
        this->onMouseUp(this, event);
    } else if (e->getType() == MouseMotionEvent::MOUSE_MOTION_EVENT) {
        MouseMotionEvent* event = static_cast<MouseMotionEvent*>(e);
        if (selectedAsset && event->wID == SDL_GetWindowID(this->window)){
            if (selectedAsset && !selectedAsset->visible){
                selectedAsset->visible = true;
            }
            selectedAsset->position.x = -lround((1/camera->getZoom())*this->windowWidth  / 2);
            selectedAsset->position.y = -lround((1/camera->getZoom())*this->windowHeight / 2);
            selectedAsset->position.x += camera->pivot.x;
            selectedAsset->position.x += lround(event->x*(1/camera->getZoom()));
            selectedAsset->position.y += camera->pivot.y;
            selectedAsset->position.y += lround(event->y*(1/camera->getZoom()));
        }
    } else if (e->getType() == WindowEnterEvent::WINDOW_ENTER_EVENT) {
        WindowEnterEvent* event = static_cast<WindowEnterEvent*>(e);
        if (event->wID == SDL_GetWindowID(assets_window)){
            assetsWindowActive = true;
            editWindowActive = mainWindowActive = false;
            
            SDL_SetWindowInputFocus(assets_window);
        } else if (event->wID == SDL_GetWindowID(edit_window)){
            editWindowActive = true;
            assetsWindowActive = mainWindowActive = false;

            SDL_SetWindowInputFocus(edit_window);
        } else if (event->wID == SDL_GetWindowID(this->window)){
            mainWindowActive = true;
            assetsWindowActive = editWindowActive = false;

            SDL_SetWindowInputFocus(this->window);

            if (selectedAsset){
                selectedAsset->visible = true;
            }
        }
        
    } else if (e->getType() == WindowExitEvent::WINDOW_EXIT_EVENT) {
        WindowExitEvent* event = static_cast<WindowExitEvent*>(e);
        if (selectedAsset && event->wID == SDL_GetWindowID(this->window)){
            selectedAsset->visible = false;
        }
        
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