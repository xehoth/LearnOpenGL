set(SRC_LIST main.cpp ${DEPS_SRC})
add_executable(Intro-Shaders ${SRC_LIST})
target_link_libraries(Intro-Shaders ${LIBS})