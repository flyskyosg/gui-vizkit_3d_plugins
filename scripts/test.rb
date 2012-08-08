require 'vizkit'
Orocos::CORBA.name_service = "127.0.0.1"
Orocos.initialize


Vizkit.default_loader

view3d = Vizkit.vizkit3d_widget


#We want to vizualize also "our" position:
rbs_plugin = Vizkit.default_loader.RigidBodyStateVisualization
#Make the RBS larger than default...
rbs_plugin.resetModel(10)

#Load the "world" based on OpenStreetMap
world_plugin = Vizkit.default_loader.osgEarth

# you might to whish to another location?
# world_plugin.setOrigin(53.111401,8.860946,0,32,true)

#Do you don't have an GPS Device, try this:
rbs = Types::Base::Samples::RigidBodyState.new
rbs.position = Eigen::Vector3.new(10, 5 , 2)
rbs_plugin.updateData rbs

view3d.show
Vizkit.exec
