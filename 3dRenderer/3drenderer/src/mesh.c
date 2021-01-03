
#include <stdio.h>
#include "mesh.h" 

mesh_t mesh = {
    .vertices = NULL,
    .faces = NULL,
    .rotation = {0,0,0}
};

vect3_t cube_vertices[N_CUBE_VERTICES] = 
{
    {-1,-1,-1},
    {-1,1,-1},
    {1,1,-1},
    {1,-1,-1},
    {1,1,1},
    {1,-1,1},
    {-1,1,1},
    {-1,-1,1}
};

face_t cube_faces[N_CUBE_FACES] = {
    //front
    {1,2,3},{1,3,4},
    //right
    {4,3,5},{4,5,6},
    //back
    {6,5,7},{6,7,8},
    //left
    {8,7,2},{8,2,1},
    //top
    {2,7,5},{2,5,3},
    //botton
    {6,8,1},{6,1,4}
};

void load_cube_mesh_data(void){
    for(int i = 0; i< N_CUBE_VERTICES; ++i){
        array_push(mesh.vertices, cube_vertices[i]);
    }
    for(int j = 0; j< N_CUBE_FACES; ++j){
        array_push(mesh.faces, cube_faces[j]);
    }
}
