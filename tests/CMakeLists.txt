
project(tests)
add_executable(tests)

target_sources(tests PRIVATE
    event.cpp
    main.cpp
    unique_handle.cpp
    unknown.cpp)
