###############################################################################
# Project Configuration
cmake_minimum_required(VERSION 3.14)
project(CPP_r-type_2020)

###############################################################################
# Language Configuration
set(CMAKE_CXX_STANDARD 20)

###############################################################################
# Compilation modes
option(USE_DEBUG "Enter debug mode" ON)
option(USE_LOG "Log Execution in a file" OFF)
option(GH_TESTS "Github tests for disable port audio" OFF)

###############################################################################
# Set Compile Options
if (UNIX)
    add_compile_options(-Wall -Wextra -Wno-unused-parameter)
    add_compile_definitions(LOG_UNIX)
    add_compile_options(-g3)
endif (UNIX)

if (USE_LOG)
    if (UNIX)
        add_compile_definitions(LOG_UNIX)
        add_compile_definitions(_r-type_LOG_)
    endif (UNIX)
endif (USE_LOG)

if (COVERAGE)
    add_compile_options(--coverage -fprofile-arcs -ftest-coverage)
endif (COVERAGE)

if (USE_DEBUG)
    if (UNIX)
        add_compile_options(-g3)
    endif (UNIX)
    add_compile_definitions(_DEBUG_)
endif (USE_DEBUG)

###############################################################################
# Conan Build Management

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(${CMAKE_INCLUDE_PATH})

find_package(SFML 2.5.1 REQUIRED system window graphics audio network REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

set(CONAN_LIBS ${CONAN_LIBS} sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

find_package(Boost COMPONENTS REQUIRED)
set(CONAN_LIBS ${CONAN_LIBS} boost_thread)

###############################################################################
# Generate .so

set(SERVER_DIR Server)
set(CLIENT_DIR Client)

set(MONSTERS_DIR Monsters)

add_library(Monster1 SHARED ${MONSTERS_DIR}/Monster1/Monster1.cpp)
add_library(Monster2 SHARED ${MONSTERS_DIR}/Monster2/Monster2.cpp)
add_library(Monster3 SHARED ${MONSTERS_DIR}/Monster3/Monster3.cpp)

target_include_directories(Monster1 PRIVATE
                    ${MONSTERS_DIR}/include
                    ${MONSTERS_DIR}/Monster1/include
                    ${SERVER_DIR}/include)

target_include_directories(Monster2 PRIVATE
                    ${MONSTERS_DIR}/include
                    ${MONSTERS_DIR}/Monster2/include
                    ${SERVER_DIR}/include)

target_include_directories(Monster3 PRIVATE
                    ${MONSTERS_DIR}/include
                    ${MONSTERS_DIR}/Monster3/include
                    ${SERVER_DIR}/include)



###############################################################################

# r-type SERVER

#Server Includes
set(
    SERVER_INCLUDES
    ${SERVER_DIR}/include
    ${SERVER_DIR}/src/ECS/include
    ${SERVER_DIR}/src/ECS/Systems/include
    ${SERVER_DIR}/src/Game/include
    ${SERVER_DIR}/src/Player/include
    ${SERVER_DIR}/src/Shots/include
    ${SERVER_DIR}/src/Explosion/include
    ${MONSTERS_DIR}/include
)

#Server Sources
set(
    SERVER_SOURCES
    ${SERVER_DIR}/src/main.cpp
    ${SERVER_DIR}/src/AsioUdp.cpp
    ${SERVER_DIR}/src/Client.cpp
    ${SERVER_DIR}/src/Room.cpp
    ${SERVER_DIR}/src/RoomManager.cpp
    ${SERVER_DIR}/src/Server.cpp
    ${SERVER_DIR}/src/ECS/ComponentManager.cpp
    ${SERVER_DIR}/src/ECS/Coordinator.cpp
    ${SERVER_DIR}/src/ECS/EntityManager.cpp
    ${SERVER_DIR}/src/ECS/Event.cpp
    ${SERVER_DIR}/src/ECS/EventManager.cpp
    ${SERVER_DIR}/src/ECS/SystemManager.cpp
    ${SERVER_DIR}/src/ECS/Sender.cpp
    ${SERVER_DIR}/src/ECS/Systems/GenerateShotSystem.cpp
    ${SERVER_DIR}/src/ECS/Systems/HandleCollisionSystem.cpp
    ${SERVER_DIR}/src/ECS/Systems/HandleInputSystem.cpp
    ${SERVER_DIR}/src/ECS/Systems/HandleMonsterSpeed.cpp
    ${SERVER_DIR}/src/ECS/Systems/SpeedApplicationSystem.cpp
    ${SERVER_DIR}/src/ECS/Systems/HandleRequestsSystem.cpp
    ${SERVER_DIR}/src/ECS/Systems/DestroySystem.cpp
    ${SERVER_DIR}/src/ECS/Systems/GenerateMonstersSystem.cpp
    ${SERVER_DIR}/src/Game/Game.cpp
    ${SERVER_DIR}/src/Player/Player.cpp
    ${SERVER_DIR}/src/Shots/PlayerShot.cpp
    ${SERVER_DIR}/src/Explosion/Explosion.cpp
    ${MONSTERS_DIR}/LoadMonsters.cpp
)

#Server Executable
add_executable(
    r-type_server
    ${SERVER_SOURCES}
)

target_include_directories(
    r-type_server PUBLIC
    ${SERVER_INCLUDES}
)

target_compile_options(r-type_server PRIVATE)

if (UNIX)
    target_link_libraries(r-type_server ${CONAN_LIBS} stdc++fs)
endif (UNIX)

if (WIN32)
    target_link_libraries(r-type_server ${CONAN_LIBS})
endif(WIN32)




################################################
# r-type CLIENT

#Client Include
set(
    CLIENT_INCLUDES
    ${SERVER_DIR}/include
    ${CLIENT_DIR}/NewClient/src/Core/include
    ${CLIENT_DIR}/NewClient/src/MainMenu/include
    ${CLIENT_DIR}/NewClient/src/OptionsMenu/include
    ${CLIENT_DIR}/NewClient/src/ECS/include
    ${CLIENT_DIR}/NewClient/src/ECS/Systems/include
    ${CLIENT_DIR}/NewClient/src/Game/include
    ${CLIENT_DIR}/NewClient/src/Player/include
    ${CLIENT_DIR}/NewClient/src/Shots/include
    ${CLIENT_DIR}/NewClient/src/Explosion/include
    ${MONSTERS_DIR}/include
)

#Client Sources
set(
    CLIENT_SOURCES
    ${CLIENT_DIR}/NewClient/main.cpp
    ${CLIENT_DIR}/NewClient/src/Core/Core.cpp
    ${CLIENT_DIR}/NewClient/src/Core/Input.cpp
    ${CLIENT_DIR}/NewClient/src/Core/RectButton.cpp
    ${CLIENT_DIR}/NewClient/src/Core/RessourceManager.cpp
    ${CLIENT_DIR}/NewClient/src/Core/TextScan.cpp
    ${CLIENT_DIR}/NewClient/src/Core/front_room.cpp
    ${CLIENT_DIR}/NewClient/src/MainMenu/MainMenu.cpp
    ${CLIENT_DIR}/NewClient/src/OptionsMenu/OptionMenu.cpp
    ${CLIENT_DIR}/NewClient/src/ECS/ComponentManager.cpp
    ${CLIENT_DIR}/NewClient/src/ECS/Coordinator.cpp
    ${CLIENT_DIR}/NewClient/src/ECS/EntityManager.cpp
    ${CLIENT_DIR}/NewClient/src/ECS/SystemManager.cpp
    ${CLIENT_DIR}/NewClient/src/ECS/Systems/AnimationSystem.cpp
    ${CLIENT_DIR}/NewClient/src/ECS/Systems/DrawSystem.cpp
    ${CLIENT_DIR}/NewClient/src/ECS/Systems/HandleInputSystem.cpp
    ${CLIENT_DIR}/NewClient/src/ECS/Systems/SpeedApplicationSystem.cpp
    ${CLIENT_DIR}/NewClient/src/ECS/Systems/NetworkHandlerSystem.cpp
    ${CLIENT_DIR}/NewClient/src/Game/Game.cpp
    ${CLIENT_DIR}/NewClient/src/Player/Player.cpp
    ${CLIENT_DIR}/NewClient/src/Shots/PlayerShot.cpp
    ${CLIENT_DIR}/NewClient/src/Explosion/Explosion.cpp
    ${MONSTERS_DIR}/LoadMonsters.cpp
    #${CLIENT_DIR}/client.cpp
    #${CLIENT_DIR}/menu/WaitingRoom.cpp
    #${CLIENT_DIR}/menu/room.cpp
    #${CLIENT_DIR}/menu/CreateRoom.cpp
)

#Client Executable
add_executable(
    r-type_client
    ${CLIENT_INCLUDES}
    ${CLIENT_SOURCES}
)

target_include_directories(
    r-type_client PUBLIC
    ${CLIENT_INCLUDES}
)

target_compile_definitions(r-type_client PRIVATE)
if (UNIX)
    target_link_libraries(r-type_client ${CONAN_LIBS} stdc++fs)
endif (UNIX)

if (WIN32)
    target_link_libraries(r-type_client ${CONAN_LIBS})
endif(WIN32)