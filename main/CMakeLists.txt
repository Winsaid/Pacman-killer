cmake_minimum_required(VERSION 3.0)
project(main)

set(CMAKE_CXX_STANDARD 14)

# Установите путь к библиотекам и заголовочным файлам SFML
set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.6.2/lib/cmake/SFML")

# Найдите компоненты SFML, которые вам необходимы
find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)

# Добавьте ваши исходные файлы
add_executable(main src/main.cpp src/class_button.cpp 
src/Map.cpp src/Bot.cpp src/Character.cpp src/Player.cpp
src/PlayerController.cpp src/Scale.cpp src/window.cpp
head/class_button.h head/class_window.h
head/main.h head/GameState.h 
head/Character.h head/Constants.h
head/Map.h head/Player.h
head/PlayerController.h
head/Scale.h head/Textures.h head/Bot.h)

# Подключите SFML библиотеки к вашему проекту
target_link_libraries(main sfml-graphics sfml-audio sfml-window sfml-system)