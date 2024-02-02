

set (SOURSES 
"main.cpp" 
"game.h" 
"game.cpp" 
"game_exception.h" 
"position.h" 
"position.cpp"
)

add_executable (chess ${SOURSES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET chess PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
