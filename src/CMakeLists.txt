

set (SOURSES "game.h" "game.cpp" "main.cpp")

add_executable (chess ${SOURSES} "misc.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET chess PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
