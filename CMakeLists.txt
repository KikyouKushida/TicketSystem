project(TicketSystem)
set(CMAKE_CXX_STANDARD 20)
file(GLOB SOURCES "./*.cpp")
add_executable(code ${SOURCES})