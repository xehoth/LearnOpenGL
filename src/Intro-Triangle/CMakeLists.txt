set(SRC_LIST main.cpp ${DEPS_SRC})
add_executable(Intro-Triangle ${SRC_LIST})
target_link_libraries(Intro-Triangle ${LIBS})