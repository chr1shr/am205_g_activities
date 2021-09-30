// Version statement. The current version of POV-Ray is 3.7, and some features
// of the language changed slightly. The version statement is required to
// identify this file as designed for version 3.7. Without it, POV-Ray will
// give a warning.
#version 3.7;

// Standard include files that contain color names and preset stone and wood
// textures
#include "colors.inc"
#include "stones.inc"
#include "woods.inc"

// The assumed_gamma value sets the overall lightness or darkness of the scene.
// This default value changed in version 3.7. If it is not specified, POV-Ray
// will give a warning.
global_settings {
    assumed_gamma 1
}

// Sets up the camera position. By default POV-Ray uses a left-handed
// coordinate system where the x and y axes point right and up, respectively,
// and the z axis points into the screen. The minimal camera setup requires
// specifying the location of the camera, and vectors that describe up and
// right on the canvas to be rendered. The look_at command is a useful
// additional command that takes the current up/right definitions, and
// rotates/pans the camera to point in a specific direction.
camera {
    location <-9,9,-25>
    right 0.22*x*image_width/image_height
    up 0.22*y
    look_at <0,0,0>
}

// Define two light sources: one strong light in the top left, and one fill
// light in the mid-right. Often two or more lights can create more natural
// lighting, and avoid very harsh shadows. Making them slightly different
// colors can also improve realism.
light_source {<-10,10,-15> color rgb <0.7,0.7,0.8>}
light_source {<10,5,-10> color rgb <0.4,0.4,0.3>}

// If rays don't hit any object, they are colored according to this background
// color
background {
    rgb <1,1,1>
}

// POV-Ray allows arbitrary textures, objects, and variables to be defined.
// This is very useful if a certain definition is used many times.
#declare f1=finish {
    diffuse 0.8
    ambient 0.2
    phong 0.7
    reflection 0.05
}

// Make a lilac-colored sphere at the origin. A sphere is specified in terms of
// the position of its center, and its radius
sphere {
    <0,0,0>,1
    texture {
        finish {f1}
        pigment { color rgb <0.8,0.5,1>}
    }
}

// Make a small blue sphere that is semi-transparent
sphere {
    <1.2,1.2,-1.2>,0.5
    texture {
        finish {f1}
        pigment { color rgbft <0,0,1,0.2,0.4>}
    }
}

// A rectangular box is specified by the lower and upper coordinate values in
// the x, y, and z coordinate directions
box {
    <-1.7,0.7,-1.7>,<-0.7,1.7,-0.7>
    texture {
        finish {f1}
        pigment { color Yellow}
    }
}

// A plane is specified by giving a normal vector, and then a displacement of
// the plane along that normal vector
plane {
    y, -1
    texture {
        pigment {checker White Tan}
    }
}

// A torus is given in terms of its major and minor radii. It is introduced at
// at the origin, but it can be rotated and translated afterward.
torus {
    3, 0.4
    texture {
        finish {f1}
        pigment { color rgb <1,1,1>}
    }
}

// A cylinder is given by its two end points, and its radius
cylinder {
    <3,0,0>,<-3,0,0>,0.4
    texture {
        finish {f1}
        pigment { color rgb <1,1,1>}
    }
}

// A cone is given by its two end points, and its radius at both ends
cone {
    <-3,-1,-3>,0.4,<-3,2,-3>,0
    texture {
        finish {f1}
        pigment { color rgb <0,0,1>}
    }
}
