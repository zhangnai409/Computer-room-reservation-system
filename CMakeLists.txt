cmake_minimum_required(VERSION 3.24)
project()

set(CMAKE_CXX_STANDARD 17)

add_executable(main.cpp identity.h student.h teacher.h manager.h globalFile.h computerRoom.h orderFile.h)
