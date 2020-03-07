add_subdirectory(events)
add_subdirectory(things)

target_sources(rebound PRIVATE
        AffineTransform.cpp
        AnimatedSprite.cpp
        Camera.cpp
        DisplayObject.cpp
        Game.cpp
        QuestManager.cpp
        Scene.cpp
        Sprite.cpp)