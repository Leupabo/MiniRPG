# CMakeLists.txt pour le projet LIFAPCD
cmake_minimum_required(VERSION 3.10)
project(LIFAPCD VERSION 1.0)

if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")
endif()

if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mconsole")
endif()

find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
    
    # Ajouter une cible pour nettoyer la documentation
    add_custom_target(clean_doc
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/doc/doxygen
        COMMENT "Cleaning documentation directories" VERBATIM
    )
endif()

# Définir le standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Définir les options de compilation
# if(MSVC)
#     add_compile_options(/W4)
# else()
#     add_compile_options(-Wall -Wextra)
# endif()

# Définir les chemins des dossiers
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(CORE_DIR ${SRC_DIR}/core)
set(INCLUDE_DIR ${SRC_DIR}/include)
set(TXT_DIR ${SRC_DIR}/txt)
set(SDL_DIR ${SRC_DIR}/sld2)
set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)

# Définir le répertoire de sortie pour les exécutables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})


# Ajouter le répertoire d'include
include_directories(${INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/external/json/include)
include_directories(${PROJECT_SOURCE_DIR}/external/SDL2)

# Créer l'exécutable maptest
add_executable(maptest 
    ${CORE_DIR}/maptest.cpp
    ${CORE_DIR}/map.cpp
)

# Créer l'exécutable main_txt
add_executable(zelda_txt
    ${TXT_DIR}/main_txt.cpp
    ${TXT_DIR}/mapTxt.cpp
    ${TXT_DIR}/winTxt.cpp

    # Fichiers du core
    ${CORE_DIR}/game.cpp
    ${CORE_DIR}/map.cpp
    ${CORE_DIR}/entity.cpp
    ${CORE_DIR}/player.cpp
    ${CORE_DIR}/enemy.cpp
    ${CORE_DIR}/enemyManager.cpp
    ${CORE_DIR}/arrow.cpp
    ${CORE_DIR}/arrowManager.cpp
    ${CORE_DIR}/bomb.cpp
    ${CORE_DIR}/bombManager.cpp
    ${CORE_DIR}/item.cpp
    ${CORE_DIR}/itemManager.cpp


)

add_executable(zelda_sdl
    ${SDL_DIR}/main_sdl.cpp
    ${SDL_DIR}/mapSdl.cpp
    ${SDL_DIR}/sprite.cpp

    # Fichiers du core
    ${CORE_DIR}/game.cpp
    ${CORE_DIR}/map.cpp
    ${CORE_DIR}/entity.cpp
    ${CORE_DIR}/player.cpp
    ${CORE_DIR}/enemy.cpp
    ${CORE_DIR}/enemyManager.cpp
    ${CORE_DIR}/arrow.cpp
    ${CORE_DIR}/arrowManager.cpp
    ${CORE_DIR}/bomb.cpp
    ${CORE_DIR}/bombManager.cpp
    ${CORE_DIR}/item.cpp
    ${CORE_DIR}/itemManager.cpp
)

if(WIN32)
    target_link_libraries(zelda_sdl mingw32 SDL2main SDL2 SDL2_image)
else()
    target_link_libraries(zelda_sdl SDL2 SDL2_image)
endif()

# Ajoutez ces lignes pour définir le sous-système Windows
if(MINGW)
    set_target_properties(zelda_sdl PROPERTIES
        LINK_FLAGS "-mconsole"
    )
endif()

add_executable(test_regression
    ${TEST_DIR}/all_tests.cpp
    ${CORE_DIR}/entity.cpp
    ${CORE_DIR}/arrow.cpp
    ${CORE_DIR}/bomb.cpp
    ${CORE_DIR}/item.cpp
    ${CORE_DIR}/player.cpp
    ${CORE_DIR}/enemy.cpp
    ${CORE_DIR}/map.cpp
)
set_target_properties(test_regression
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${BIN_DIR}/tests"
)

# Créer le dossier bin s'il n'existe pas
file(MAKE_DIRECTORY ${BIN_DIR})

