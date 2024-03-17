#include "raylib.h"
int main()
{
    //Window dimensions
    int width{800};
    int height{450};
    InitWindow(width,height,"hello");

    // Circle coordinates
    int circle_x{175};
    int circle_y{100};
    int circle_radius{25};
    //Circle edges
    int l_circle_x{circle_x - circle_radius};
    int r_circle_x{circle_x + circle_radius};
    int u_circle_y{circle_y - circle_radius};
    int b_circle_y{circle_y + circle_radius};

    //Rectangle coordinate
    int rectangle_x{300};
    int rectangle_y{0};
    int rectable_width{50};
    int rectangle_height{50};
    int rectangle_direction{10};
    //Rectangle edges
    int l_rectangle_x{rectangle_x};
    int r_rectangle_x{rectangle_x + rectable_width};
    int u_rectangle_y{rectangle_y};
    int b_rectangle_y{rectangle_y + rectangle_height};

    bool collision_with_rectangle = (b_rectangle_y >= u_circle_y) && (u_rectangle_y <= b_circle_y) && (r_rectangle_x >= l_circle_x) && (l_rectangle_x <= r_circle_x);


    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        if (collision_with_rectangle)
        {
            DrawText("Game Over!",400,200,20,RED);
        }
        else
        {
            // Game logic begins
            rectangle_y += rectangle_direction;
            //Update edges
            l_circle_x= circle_x - circle_radius;
            r_circle_x=circle_x + circle_radius;
            u_circle_y=circle_y - circle_radius;
            b_circle_y=circle_y + circle_radius;
            l_rectangle_x=rectangle_x;
            r_rectangle_x=rectangle_x + rectable_width;
            u_rectangle_y=rectangle_y;
            b_rectangle_y=rectangle_y + rectangle_height;

            //update collision with rectangle
            collision_with_rectangle = (b_rectangle_y >= u_circle_y) && (u_rectangle_y <= b_circle_y) && (r_rectangle_x >= l_circle_x) && (l_rectangle_x <= r_circle_x);

            DrawCircle(circle_x,circle_y,circle_radius,BLUE);
            DrawRectangle(rectangle_x,rectangle_y,rectable_width,rectangle_height,RED);

            

            if (b_rectangle_y > height || rectangle_y < 0)
            {
                rectangle_direction = -rectangle_direction;
            }
            
            
            if (IsKeyDown(KEY_D) && r_circle_x < width)
            {
                circle_x += 10;
            }
            if (IsKeyDown(KEY_A) && l_circle_x > 0)
            {
                circle_x -= 10;
            }
            // Game logic ends
        }

        

        
        EndDrawing();
    }

}