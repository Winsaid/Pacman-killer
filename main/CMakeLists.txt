cmake_minimum_required(VERSION 3.0)
project(main)

set(CMAKE_CXX_STANDARD 14)

# Установите путь к библиотекам и заголовочным файлам SFML
set(SFML_DIR "C:/Users/Winsaid/dev/tpro/Pacman-killer/main/SFML-2.6.2/lib/cmake/SFML")

# Найдите компоненты SFML, которые вам необходимы
find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)

# Добавьте ваши исходные файлы
add_executable(main src/main.cpp)
add_library(mainLib SHARED src/main.cpp)

# Подключите SFML библиотеки к вашему проекту
target_link_libraries(main sfml-graphics sfml-audio sfml-window sfml-system)