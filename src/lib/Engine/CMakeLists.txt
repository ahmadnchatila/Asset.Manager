file(GLOB sources "*.cpp")
file(GLOB headers "*.hpp")

if (ASSETMANAGER_ADD_HEADERS)
    list(APPEND sources ${headers})
endif()

add_library(Engine STATIC ${sources})