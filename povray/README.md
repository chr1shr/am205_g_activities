# Introduction to POV-Ray 
This directory contains several example scenes for the AM205 POV-Ray tutorial:

- **intro_scene.pov** introduces many of the basic POV-Ray commands for creating
  a objects and applying textures to them

- **set_operations.pov** demonstrates POV-Ray's ability to perform set operations
  on the basic object types

- **liss_3d.py** calculates a variation of a
  [Lissajous curve](https://en.wikipedia.org/wiki/Lissajous_curve). It creates
  a POV-Ray file called **liss_3d.inc** that defines a sequence of spheres and
  cylinders along the curve. The POV-Ray file **liss_3d.pov** then sets up a
  scene, and imports the **liss_3d.inc** definitions.

POV-Ray is installed as a command-line utility. A typical command to render an
image is
```Shell
povray +H768 +W1024 +Ointro_scene.png intro_scene.pov
```
Switching on anti-aliasing and removing jitter can be done via
```Shell
povray +H768 +W1024 +A0.1 -J +Ointro_scene.png intro_scene.pov
```
