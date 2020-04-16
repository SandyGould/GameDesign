add_subdirectory(enemies)
add_subdirectory(events)
add_subdirectory(things)
add_subdirectory(tweens)

target_sources(rebound PRIVATE
        AffineTransform.cpp
        AnimatedSprite.cpp
        Camera.cpp
        CollisionSystem.cpp
        DisplayObject.cpp
        Game.cpp
        QuestManager.cpp
        Scene.cpp
        Sprite.cpp
        TextObject.cpp
        pugixml.cpp)