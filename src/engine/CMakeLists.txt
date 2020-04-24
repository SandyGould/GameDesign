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
        EnvironmentObject.cpp
        Game.cpp
        HitObject.cpp
        Layer.cpp
        QuestManager.cpp
        Scene.cpp
        SceneManager.cpp
        Sprite.cpp
        StatBar.cpp
        TextObject.cpp
        WalkOnObject.cpp)