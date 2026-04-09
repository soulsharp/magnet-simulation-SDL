#define SDL_MAIN_USE_CALLBACKS 1
#include <stdio.h>
#include <SDL3/SDL.h>
#include <math.h>
#include "utils.h"

#define STEP_RATE_IN_MILLISECONDS  125
#define SIMULATION_WIDTH 720U
#define SIMULATION_HEIGHT 540U
#define GRID_SIZE 20U
#define SIMULATION_MATRIX_SIZE ((SIMULATION_WIDTH / GRID_SIZE)* (SIMULATION_HEIGHT) / GRID_SIZE)
#define DELAY_TIME 1000U
#define MAX_FORCE 100

// One struct to define the entire GridSystem. Better for AVX2 instructions
typedef struct{
    float *x;
    float *y;
    float *fx;
    float *fy;
    int num_grids;
} GridSystem;

// Gets x or y coordinates of all grid points based on flag forY
int* get_grid_pos(bool forX, int *grid_pos){
    int i, j, dim;
    int count=0;
    int x_step = SIMULATION_WIDTH / GRID_SIZE;
    int y_step = SIMULATION_HEIGHT / GRID_SIZE;
    int min_limit = GRID_SIZE / 2;

    if (forX){
        dim = SIMULATION_WIDTH;
        int max_limit = dim - min_limit;
        for (i=0; i<y_step; i++){
            for(j=min_limit; j<=max_limit; j+=x_step){
                grid_pos[count] = j;
            }
        }
    }
    else{
        dim = SIMULATION_HEIGHT;
        int max_limit = dim - min_limit;
        for (i=min_limit; i<max_limit; i+=y_step){
            for(j=0; j<x_step; j++){
                grid_pos[count] = i;
            }
        }
    }
    return grid_pos;
}

GridSystem* initialize_grid(GridSystem* grid_context){
    // Define X positions and Y positions
    int i, force, direction;
    int x_step = SIMULATION_WIDTH / GRID_SIZE;
    int y_step = SIMULATION_HEIGHT / GRID_SIZE;
    int num_grids = x_step * y_step;
    int grid_x[x_step];
    int grid_y[y_step];
    int force_x[x_step * y_step];
    int force_y[x_step * y_step]; 

    // Initialize the force field
    for (i=0; i<num_grids; i++){
        force = generate_random_force(MAX_FORCE);
        direction = generate_random_direction();

        force_x[i] = force * cos(direction);
        force_y[i] = force * sin(direction);
    }
    
    grid_context -> x = get_grid_pos(true , grid_x);
    grid_context -> y = get_grid_pos(false, grid_y);
    grid_context -> fx = force_x;
    grid_context -> fy = force_y;
    grid_context -> num_grids = num_grids;

    return grid_context;
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{   
    printf("Simulation matrix size : %i", SIMULATION_MATRIX_SIZE);
    return SDL_APP_CONTINUE;
}