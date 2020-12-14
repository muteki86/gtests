#include <math.h>
#include "vector.h"

vect3_t vec3_rotate_x(vect3_t v, float angle){
    vect3_t rotated_v = {
        v.x,
        v.y * cos(angle) - v.z * sin(angle),
        v.y * sin(angle) + v.z * cos(angle)
    };
    return rotated_v;
}

vect3_t vec3_rotate_y(vect3_t v, float angle){
    vect3_t rotated_v = {
        v.x * cos(angle) - v.z * sin(angle),
        v.y ,
        v.x * sin(angle) + v.z * cos(angle)
    };
    return rotated_v;
}

vect3_t vec3_rotate_z(vect3_t v, float angle){
    vect3_t rotated_v = {
        v.x * cos(angle) - v.y * sin(angle),
        v.x * sin(angle) + v.y * cos(angle),
        v.z 
    };
    return rotated_v;
}