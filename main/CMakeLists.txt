cmake_minimum_required(VERSION 3.0)
project(main)

set(CMAKE_CXX_STANDARD 14)

# Установите путь к библиотекам и заголовочным файлам SFML
set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.6.2/lib/cmake/SFML")

# Найдите компоненты SFML, которые вам необходимы
find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)

# Добавьте ваши исходные файлы
add_executable(main src/main_window.cpp src/class_button.cpp)
#add_library(mainLib SHARED src/main_window.cpp src/class_button.cpp)

# Подключите SFML библиотеки к вашему проекту
target_link_libraries(main sfml-graphics sfml-audio sfml-window sfml-system)