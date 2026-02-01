project(DuckTales)

cmake_minimum_required(VERSION 3.5)

# Ottengo tutti i sorgenti
file(GLOB my_sources *.h *.cpp *.qrc block.cpp StaticObject.cpp)

# Attiva il Resource Compiler (RCC)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

# Aggiungo eseguibile
add_executable(DuckTales ${my_sources}
    Menu.h Menu.cpp
    Rat.h Rat.cpp)

# Imposto il percorso di Qt
set(CMAKE_PREFIX_PATH "~/Qt/6.8.2/macos")



# Verifico l'esistenza delle librerie Qt necessarie
find_package(Qt6Widgets REQUIRED)
find_package(Qt6Multimedia REQUIRED)
find_package(Qt6OpenGLWidgets REQUIRED)

# Collego le librerie Qt con l'eseguibile
target_link_libraries(DuckTales Qt6::Widgets Qt6::Multimedia Qt6::OpenGLWidgets)
