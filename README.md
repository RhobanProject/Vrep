V-REP
====

V-REP version for RhobanProject (education)

Directories:
------------

- Addon: Altered files of V-REP for custom remote API commands
- Models: Robots models for V-REP
- Scenes: Simulations set up
- Client: Simple interface for communicating with V-REP running simulation
- Example: Basic example moving robot and printing all sensors values

Compiling:
----------

- mkdir Client/build/ ; cd Client/build/
- cmake .. #Build V-REP remote API custom commands
- make #Build Client into library
- mkdir Example/build ; cd Example/build/ 
- cmake ..
- make #Build example against Client library

Run:
----

- cd Example/build/
- ./vrep
- ./Client 127.0.0.1 4242

Models:
-------

- Rendered model is different than physical used dynamic model
- Prefert simple shapes (or convex) for approximating dynamic model
- Joints must be revolute, position not cyclic, mode force/torque, 
  position control enabled, force/torque regulated

