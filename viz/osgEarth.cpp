#include <iostream>
#include "osgEarth.hpp"
#include <osgDB/ReadFile>
#include <ogr_spatialref.h>
#include <base/Logging.hpp>

using namespace vizkit3d;


#ifndef PATH_TO_EARTH_FILE
#error "No define PATH_TO_EARTH_FILE is set"
#endif

osgEarth::osgEarth()
{
    map = 0;
    transform = new osg::MatrixTransform;
    
    if(!map.get()){
        map = osgDB::readNodeFile(PATH_TO_EARTH_FILE);
    }
    if(!map.get()){
	LOG_ERROR_S << "failed to load scenefile: \'" << PATH_TO_EARTH_FILE << "\'"<< std::endl;
    }
   
    //Setting Origin to the ROCK Developers office :-)
    setOrigin(53.111401,8.860946,0,32,true);
    transform->addChild(map);
}

osgEarth::~osgEarth()
{
}

void osgEarth::setEarthFile(std::string filename){
   
    if(map.get()){
        transform->removeChild(map);
        map = osgDB::readNodeFile(filename.c_str());
    }
    
    if(!map.get()){
	LOG_ERROR_S << "failed to load scenefile: \'" << PATH_TO_EARTH_FILE << "\'"<< std::endl;
    }
    transform->addChild(map);
    
}

osg::ref_ptr<osg::Node> osgEarth::createMainNode()
{
    //Everything is already done
    return transform;
}

void osgEarth::updateMainNode ( osg::Node* node )
{
    //Not Used
}

void osgEarth::updateDataIntern(int const& sample){
    //Not used, becase we don't need to display data, but only plugins that display data currently possible ;)
}

void osgEarth::updateOrigin(){
    OGRSpatialReference oSourceSRS;
    OGRSpatialReference oTargetSRS;
    
    oSourceSRS.SetWellKnownGeogCS( "WGS84" );
    oTargetSRS.SetWellKnownGeogCS( "WGS84" );
    oTargetSRS.SetUTM( utm_zone, utm_north );

    OGRCoordinateTransformation *coTransform;
    coTransform = OGRCreateCoordinateTransformation( &oSourceSRS, &oTargetSRS );

    if( coTransform == NULL )
    {
	LOG_ERROR_S << "failed to initialize CoordinateTransform UTM_ZONE:" << utm_zone << " UTM_NORTH:" << utm_north << std::endl;
	return;
    }
    
    double la = origin[0];
    double lo = origin[1];
    double alt = origin[2];
    coTransform->Transform(1, &lo, &la, &alt);
    transform->setMatrix(osg::Matrix::translate(-lo,-la,alt));
    LOG_DEBUG("Updated matrix with new values %f %f %f \n", la, lo, alt);

}

void osgEarth::setOrigin(double posX, double posY, double posZ, int utm_zone, bool north){
    origin[0] = posX;
    origin[1] = posY;
    origin[2] = posZ;
    this->utm_zone = utm_zone;
    this->utm_north = north;
    updateOrigin();    
}

//Macro that makes this plugin loadable in ruby, this is optional.
VizkitQtPlugin(osgEarth)

