#version 3.7;

// Right-handed coordinate system in which the z-axis points upwards
camera {
	location <30,-50,25>
	sky z
	right -0.06*x*image_width/image_height
	up 0.06*z
	look_at <0,0,0>
}

// Two lights with slightly different colors
light_source{<-8,-20,30> color rgb <0.77,0.75,0.75>}
light_source{<25,-12,12> color rgb <0.38,0.40,0.40>}

// Radius of curve
#declare r=0.07;

// Curve
union{
#include "liss_3d.inc"
    
    // Define rainbow color map
    pigment{radial
        color_map{ [0 rgb<1,0,0>]
                   [1/6. rgb<1,1,0>]
                   [2/6. rgb<0,1,0>]
                   [3/6. rgb<0,1,1>]
                   [4/6. rgb<0,0,1>]
                   [5/6. rgb<1,0,1>]
                   [1 rgb<1,0,0>]
        }
        rotate <20,38,72>
    }

    // Define surface finish properties
    finish{reflection 0.13 specular 0.8 ambient 0.22}
}
