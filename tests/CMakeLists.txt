
project(tests)
add_executable(tests)

target_sources(tests PRIVATE
    environment.cpp
    event.cpp
    main.cpp
    unique_handle.cpp
    unknown.cpp)
