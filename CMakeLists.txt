cmake_minimum_required(VERSION 3.16)
project(CS202_Group9 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_subdirectory(Source)

add_executable(${PROJECT_NAME}  Source/Main.cpp
                                Source/SceneNode.cpp
                                Source/Entity.cpp
                                Source/SpriteNode.cpp
                                Source/Character.cpp
                                Source/World.cpp
                                Source/Command.cpp
                                Source/CommandQueue.cpp
                                Source/Player.cpp
                                Source/State.cpp
                                Source/StateStack.cpp
                                Source/GameState.cpp
                                Source/LoadingState.cpp
                                Source/Utility.cpp
                                Source/ParallelTask.cpp
                                Source/MenuState.cpp
                                Source/PauseState.cpp
                                Source/TitleState.cpp
                                Source/Application.cpp
                                Source/CollisionBox.cpp 
                                Source/Object.cpp
                                Source/TextureHolder.cpp
                                Source/MovingObject.cpp
                                Source/Component.cpp
                                Source/Button.cpp
                                Source/Container.cpp
                                Source/Label.cpp
                                Source/SettingState.cpp
                                Source/HighScoreState.cpp
                                Source/CharacterState.cpp
                                Source/Animation.cpp
                                Source/GameOverState.cpp
                                Source/TileManagement.cpp
                                Source/ObstacleManagement.cpp
                                Source/GameObject.cpp
                                Source/CreditState.cpp
                                Source/DataTables.cpp
                                Source/MapState.cpp
                                Source/GameLevel.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
include_directories(Media)
include_directories(Include)

add_custom_command(
    TARGET ${PROJECT_NAME}
    COMMENT "Copy Media"
    PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Media $<TARGET_FILE_DIR:${PROJECT_NAME}>/Media
    VERBATIM)

if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
        VERBATIM)
endif()

install(TARGETS ${PROJECT_NAME})
