set(SRC_LIST main.cpp)
add_executable(CreateWindow ${SRC_LIST} ${DEPS_SRC})
target_link_libraries(CreateWindow ${LIBS})
