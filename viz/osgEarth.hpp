#ifndef osgEarth_osgEarth_H
#define osgEarth_osgEarth_H

#include <boost/noncopyable.hpp>
#include <vizkit/Vizkit3DPlugin.hpp>
#include <osg/Geode>
//#include <base/samples/rigid_body_state.h>
#include <osg/MatrixTransform>
#include <osg/MatrixTransform>


namespace vizkit
{
    class osgEarth
        : public vizkit::Vizkit3DPlugin<int>
        , boost::noncopyable
    {
    Q_OBJECT
    Q_PROPERTY(double originX READ getOriginX WRITE setOriginX)
    Q_PROPERTY(double originY READ getOriginY WRITE setOriginY)
    Q_PROPERTY(double originZ READ getOriginZ WRITE setOriginZ)
    Q_PROPERTY(int   utm_zone READ getUTMZone WRITE setUTMZone)
    Q_PROPERTY(bool   utm_north READ isUTMNorth WRITE setUTMNorth)

    public:
        osgEarth();
        virtual ~osgEarth();

//    Q_INVOKABLE void updateData(void const &sample)
//    {vizkit::Vizkit3DPlugin<void>::updateData(sample);}

    protected:
        virtual osg::ref_ptr<osg::Node> createMainNode();
        virtual void updateMainNode(osg::Node* node);
       
         osg::ref_ptr<osg::MatrixTransform> transform;
         osg::ref_ptr<osg::Node> map;
         int utm_zone;
         bool utm_north;
    private:
        struct Data;
        base::Vector3d origin;
        void updateDataIntern(int const& sample);

    public slots:
        void setEarthFile(std::string filename);
        void setOrigin(double posX, double posY, double posZ, int utm_zone, bool north);
        void updateOrigin();
        double getOriginX(){return origin[0];};
        double getOriginY(){return origin[1];};
        double getOriginZ(){return origin[2];};
        int getUTMZone(){return utm_zone;};
        bool isUTMNorth(){return utm_north;};
        void setOriginX(double val){origin[0] = val; updateOrigin();};
        void setOriginY(double val){origin[1] = val; updateOrigin();};
        void setOriginZ(double val){origin[2] = val; updateOrigin();};
        void setUTMZone(int val){utm_zone = val; updateOrigin();};
        void setUTMNorth(bool val){utm_north = val; updateOrigin();};
    };
}
#endif
