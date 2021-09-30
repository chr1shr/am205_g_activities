#version 3.7;

global_settings {
    assumed_gamma 1.0
}

camera {
    location <-6,6,-20>
    up 0.22*y
    right 0.22*x*image_width/image_height
    look_at <0,0,0>
}

light_source {<-14,14,-10> color rgb <0.7,0.7,0.73>}
light_source {<14,4,-8> color rgb <0.4,0.4,0.37>}

background {rgb <0,0,0>}

#declare f1=finish {
    diffuse 1
    ambient 0.2
    phong 0.75
    phong_size 60
    reflection 0.3
}

// A key feature of POV-Ray is that it can do arbitrary set operations on
// different shapes, via the commands union, intersection, and difference.
// Here, we construct the intersection between two unions of three tori.
intersection {
    union {
        torus{2,0.8
            scale <1,0.5,1>
            texture{pigment{rgb<1,0,0>} finish{f1}}
        }
        torus{2,0.8
            scale <1,0.5,1>
            rotate <0,0,60>
            texture{pigment{rgb<1,1,0>} finish{f1}}
        }
        torus{2,0.8
            scale <1,0.5,1>
            rotate <0,0,120>
            texture{pigment{rgb<0,0,1>} finish{f1}}
        }
    }
    union{

        torus{2,0.8
            scale <1,0.5,1>
            rotate <0,0,30>
            texture{pigment{rgb<1,0.5,0>} finish{f1}}
        }

            torus{2,0.8
            scale <1,0.5,1>
            rotate <0,0,90>
            texture{pigment{rgb<0,1,0>} finish{f1}}
        }
            torus{2,0.8
            scale <1,0.5,1>
            rotate <0,0,150>
            texture{pigment{rgb<1,0,1>} finish{f1}}
        }
    }
}
