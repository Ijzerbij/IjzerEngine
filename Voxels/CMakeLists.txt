# CMakeList.txt : CMake project for Voxels, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Voxels "Voxels.cpp" "Voxels.hpp")

target_link_libraries(Voxels PRIVATE Engine)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Voxels PROPERTY CXX_STANDARD 20)
endif()

add_custom_command(TARGET Voxels POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Engine/Assets
        $<TARGET_FILE_DIR:Voxels>/Assets
)

if (MSVC)
    target_link_options(Voxels PRIVATE
        $<$<CONFIG:Release>:/SUBSYSTEM:WINDOWS>
        $<$<CONFIG:Release>:/ENTRY:mainCRTStartup>
    )
endif()