
project(tests)
add_executable(tests)

target_sources(tests PRIVATE
    console.cpp
    environment.cpp
    event.cpp
    main.cpp
    unique_handle.cpp
    unknown.cpp)
