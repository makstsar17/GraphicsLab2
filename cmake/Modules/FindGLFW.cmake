include(FindPackageHandleStandardArgs)

# Find include files
find_path(
        GLFW_INCLUDE_DIR
        NAMES GLFW/glfw3.h
        PATHS
        $ENV{PROGRAMFILES}/include
        ${GLFW_ROOT_DIR}/include
        "C:/glfw/include"
        DOC "The directory where GLFW/glfw.h resides")

# Use glfw3.lib for static library
if (GLFW_USE_STATIC_LIBS)
    set(GLFW_LIBRARY_NAME libglfw3)
else ()
    set(GLFW_LIBRARY_NAME glfw3.lib)
endif ()

# Find library files
find_library(
        GLFW_LIBRARY
        NAMES ${GLFW_LIBRARY_NAME}
        PATHS
        "C:/glfw/lib"
        $ENV{PROGRAMFILES}/lib
        ${GLFW_ROOT_DIR}/lib)

unset(GLFW_LIBRARY_NAME)


# Handle REQUIRD argument, define *_FOUND variable
find_package_handle_standard_args(GLFW DEFAULT_MSG GLFW_INCLUDE_DIR GLFW_LIBRARY)

# Define GLFW_LIBRARIES and GLFW_INCLUDE_DIRS
if (GLFW_FOUND)
    set(GLFW_LIBRARIES ${OPENGL_LIBRARIES} ${GLFW_LIBRARY})
    set(GLFW_INCLUDE_DIRS ${GLFW_INCLUDE_DIR})
endif ()

# Hide some variables
mark_as_advanced(GLFW_INCLUDE_DIR GLFW_LIBRARY)