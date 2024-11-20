cmake_minimum_required(VERSION 3.0)
project(Main)

set(CMAKE_CXX_STANDARD 14)

# Установите путь к библиотекам и заголовочным файлам SFML
set(SFML_DIR "C:/Users/Winsaid/dev/tpro/Pacman-killer/Pacman-killer///Main/SFML-2.6.2/lib/cmake/SFML")

# Найдите компоненты SFML, которые вам необходимы
find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)

# Добавьте ваши исходные файлы
add_executable(Main src/main.cpp)
add_library(MainLib SHARED src/main.cpp)

# Подключите SFML библиотеки к вашему проекту
target_link_libraries(Main sfml-graphics sfml-audio sfml-window sfml-system)