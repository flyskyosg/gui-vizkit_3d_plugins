# CMakeLists.txt has to be located in the project folder and cmake has to be
# executed from 'project/build' with 'cmake ../'.


cmake_minimum_required(VERSION 2.6)
find_package(Rock)
rock_init(vizkit_3d_plugins 0.1)
rock_standard_layout()

INSTALL(FILES  ${CMAKE_SOURCE_DIR}/viz/openstreetmap.earth DESTINATION share/osgEarth/)
