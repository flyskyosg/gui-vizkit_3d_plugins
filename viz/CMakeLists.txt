find_package(GDAL REQUIRED)
add_definitions(${GDAL_CFLAGS})
include_directories(${GDAL_INCLUDE_DIRS})
link_directories(${GDAL_LIBRARY_DIRS})

ADD_DEFINITIONS(
    -DPATH_TO_EARTH_FILE="${CMAKE_INSTALL_PREFIX}/share/osgEarth/openstreetmap.earth"
)



rock_vizkit_plugin(osgEarth-viz
    osgEarth.cpp
    #    DEPS osgEarth
    MOC osgEarth.hpp
    DEPS_PKGCONFIG base-types
    HEADERS osgEarth.hpp)

target_link_libraries(osgEarth-viz
     ${GDAL_LIBRARIES}
)
