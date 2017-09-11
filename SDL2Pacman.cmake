function(project_SDL2Pacman_Debug_Linux)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
  set(CMAKE_BUILD_TYPE RelWithDebInfo)

  add_definitions(
    -DDEBUG
  )

  set(SRC 
    src/Main.cpp
  )
  add_executable( SDL2Pacman_Debug_Linux ${SRC})
  set_target_properties( SDL2Pacman_Debug_Linux 
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "C:/Users/vmontero/Documents/MEGAsync/Pacman/bin/Linux/Debug"
    LIBRARY_OUTPUT_DIRECTORY "C:/Users/vmontero/Documents/MEGAsync/Pacman/bin/Linux/Debug"
    RUNTIME_OUTPUT_DIRECTORY "C:/Users/vmontero/Documents/MEGAsync/Pacman/bin/Linux/Debug"
    OUTPUT_NAME  "SDL2Pacman"
  )

  set(LIBS 
    SDL2main
    SDL2
    SDL2_image
    SDL2_ttf
  )
  target_link_libraries(SDL2Pacman_Debug_Linux ${LIBS})
endfunction(project_SDL2Pacman_Debug_Linux)
project_SDL2Pacman_Debug_Linux()

function(project_SDL2Pacman_Debug_Windows)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
  set(CMAKE_BUILD_TYPE RelWithDebInfo)

  add_definitions(
    -DDEBUG
  )

  set(INCLUD_DIRS 
    libs/SDL2-2.0.5/i686-w64-mingw32/include/SDL2
    libs/SDL2_image-2.0.1/i686-w64-mingw32/include/SDL2
    libs/SDL2_ttf-2.0.14/i686-w64-mingw32/include/SDL2
  )
  include_directories(${INCLUD_DIRS})

  set(LIB_DIRS
    libs/SDL2-2.0.5/i686-w64-mingw32/lib
    libs/SDL2_image-2.0.1/i686-w64-mingw32/lib
    libs/SDL2_ttf-2.0.14/i686-w64-mingw32/lib
  )
  link_directories(${LIB_DIRS})

  set(SRC 
    src/Main.cpp
  )
  add_executable( SDL2Pacman_Debug_Windows ${SRC})
  set_target_properties( SDL2Pacman_Debug_Windows 
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "C:/Users/vmontero/Documents/MEGAsync/Pacman/bin/Windows/Debug"
    LIBRARY_OUTPUT_DIRECTORY "C:/Users/vmontero/Documents/MEGAsync/Pacman/bin/Windows/Debug"
    RUNTIME_OUTPUT_DIRECTORY "C:/Users/vmontero/Documents/MEGAsync/Pacman/bin/Windows/Debug"
    OUTPUT_NAME  "SDL2Pacman"
  )

  set(LIBS 
    Mingw32
    SDL2main
    SDL2
    SDL2_image
    SDL2_ttf
  )
  target_link_libraries(SDL2Pacman_Debug_Windows ${LIBS})
endfunction(project_SDL2Pacman_Debug_Windows)
project_SDL2Pacman_Debug_Windows()

function(project_SDL2Pacman_Release_Linux)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
  set(CMAKE_BUILD_TYPE RelWithDebInfo)

  add_definitions(
    -DNDEBUG
  )

  set(SRC 
    src/Main.cpp
  )
  add_executable( SDL2Pacman_Release_Linux ${SRC})
  set_target_properties( SDL2Pacman_Release_Linux 
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "C:/Users/vmontero/Documents/MEGAsync/Pacman/bin/Linux/Release"
    LIBRARY_OUTPUT_DIRECTORY "C:/Users/vmontero/Documents/MEGAsync/Pacman/bin/Linux/Release"
    RUNTIME_OUTPUT_DIRECTORY "C:/Users/vmontero/Documents/MEGAsync/Pacman/bin/Linux/Release"
    OUTPUT_NAME  "SDL2Pacman"
  )

  set(LIBS 
    SDL2main
    SDL2
    SDL2_image
    SDL2_ttf
  )
  target_link_libraries(SDL2Pacman_Release_Linux ${LIBS})
endfunction(project_SDL2Pacman_Release_Linux)
project_SDL2Pacman_Release_Linux()

function(project_SDL2Pacman_Release_Windows)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
  set(CMAKE_BUILD_TYPE RelWithDebInfo)

  add_definitions(
    -DNDEBUG
  )

  set(INCLUD_DIRS 
    libs/SDL2-2.0.5/i686-w64-mingw32/include/SDL2
    libs/SDL2_image-2.0.1/i686-w64-mingw32/include/SDL2
    libs/SDL2_ttf-2.0.14/i686-w64-mingw32/include/SDL2
  )
  include_directories(${INCLUD_DIRS})

  set(LIB_DIRS
    libs/SDL2-2.0.5/i686-w64-mingw32/lib
    libs/SDL2_image-2.0.1/i686-w64-mingw32/lib
    libs/SDL2_ttf-2.0.14/i686-w64-mingw32/lib
  )
  link_directories(${LIB_DIRS})

  set(SRC 
    src/Main.cpp
  )
  add_executable( SDL2Pacman_Release_Windows ${SRC})
  set_target_properties( SDL2Pacman_Release_Windows 
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "C:/Users/vmontero/Documents/MEGAsync/Pacman/bin/Windows/Release"
    LIBRARY_OUTPUT_DIRECTORY "C:/Users/vmontero/Documents/MEGAsync/Pacman/bin/Windows/Release"
    RUNTIME_OUTPUT_DIRECTORY "C:/Users/vmontero/Documents/MEGAsync/Pacman/bin/Windows/Release"
    OUTPUT_NAME  "SDL2Pacman"
  )

  set(LIBS 
    Mingw32
    SDL2main
    SDL2
    SDL2_image
    SDL2_ttf
  )
  target_link_libraries(SDL2Pacman_Release_Windows ${LIBS})
endfunction(project_SDL2Pacman_Release_Windows)
project_SDL2Pacman_Release_Windows()
