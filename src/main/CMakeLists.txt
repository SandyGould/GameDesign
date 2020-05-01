add_subdirectory(demos)

target_sources(rebound PRIVATE
        Editor.cpp
        main.cpp
        Rebound.cpp
        Rooms.cpp
        TitleScreen.cpp)