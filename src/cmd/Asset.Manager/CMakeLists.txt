file(GLOB headers "*.hpp")
file(GLOB sources "*.cpp")

if (WIN32)
  add_executable (Asset.Manager WIN32 ${sources})
else()
  add_executable (Asset.Manager ${sources})
endif()

target_link_libraries (Asset.Manager
    Abstracts Engine Models Utilities Client ${libs})