#ifndef SIMULATION_CONTEXT_H
#define SIMULATION_CONTEXT_H

typedef struct{
    float *x;
    float *y;
    float *fx;
    float *fy;
    float *dir;
    int num_grids;
} GridSystem;

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    GridSystem* grid_context;
    bool is_sim_active;
    Uint64 last_step;
} AppState;

// Arrows representing force color coded based on magnitude(ascending)
typedef enum{
    LVL_DB = 0x30123B, // Level Dark_Blue
    LVL_B = 0x4675ED, // Levle Blue
    LVL_CB = 0x1BCFD4, // Level Cyan_Blue
    LVL_GC = 0x24ECA6, // Level Green_Cyan
    LVL_LG = 0x61FC6C, // Level Light_Green
    LVL_YG = 0xA4FC3B, // Level Yellow_Green
    LVL_Y = 0xF3C63A, // Level Yellow
    LVL_O = 0xFE9B2D, // Level Orange
    LVL_OR = 0xF36315, // Level Orange_Red
    LVL_DR = 0x7A0402, // Level Dark_Red
}force_color;

extern GridSystem grid_context;
extern AppState as;
float* get_grid_pos(bool forX, float *grid_pos);
GridSystem* initialize_grid(GridSystem* grid_context);

#endif