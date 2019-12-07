set(SRC_LIST main.cpp ${DEPS_SRC})
add_executable(Shader ${SRC_LIST})
target_link_libraries(Shader ${LIBS})