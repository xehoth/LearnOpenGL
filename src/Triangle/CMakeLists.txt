set(SRC_LIST main.cpp ${DEPS_SRC})
add_executable(Triangle ${SRC_LIST})
target_link_libraries(Triangle ${LIBS})