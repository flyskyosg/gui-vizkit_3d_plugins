require 'vizkit'
Orocos::CORBA.name_service = "127.0.0.1"
Orocos.initialize


Orocos.run "gps::GPSDTask" => 'task' do

    task = Orocos::TaskContext.get "task"

    #Setting the GPS Device to the same origin that is set to the map (in UTM Coordinates!)
    o =  task.origin
    o[0]= 490692.074367
    o[1]= 5884672.120927
    o[2]= 0.0
    task.origin = o
    
    
    task.configure
    task.start

    Vizkit.default_loader

    view3d = Vizkit.vizkit3d_widget


    #We want to vizualize also "our" position:
    rbs_plugin = Vizkit.default_loader.RigidBodyStateVisualization
    #Make the RBS larger than default...
    rbs_plugin.resetModel(10)

    #Load the "world" based on OpenStreetMap
    world_plugin = Vizkit.default_loader.osgEarth

    #maybe you want to load another earth file?
    #world_plugin.setEarthFile("/home/user/some/path/to/rocking_file.earth")

    # you might to whish to another location?
    # world_plugin.setOrigin(53.111401,8.860946,0,32,true)

    task.position_samples.connect_to rbs_plugin

    view3d.show
    Vizkit.exec
end
