#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

#define WIDTH 800
#define HEIGHT 600
#define MAX_ITER 100

int mandelbrot(float x, float y)
{
    float real = 0, imag = 0;
    int iter = 0;

    while (iter < MAX_ITER && (real * real + imag * imag) < 4)
    {
        float temp = real * real - imag * imag + x;
        imag = 2 * real * imag + y;
        real = temp;
        iter++;
    }

    return iter;
}

Color getColor(int iter)
{
    if (iter == MAX_ITER)
        return BLACK;

    float t = (float)iter / MAX_ITER;
    return (Color){(unsigned char)(255 * t), (unsigned char)(255 * t), (unsigned char)(255 * t), 255};
}

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "Mandelbrot Set");

    RenderTexture2D target = LoadRenderTexture(WIDTH, HEIGHT);
    SetTargetFPS(144);

    while (!WindowShouldClose())
    {
        //if (IsKeyPressed(KEY_ENTER))
        //{
            BeginTextureMode(target);

            for (int x = 0; x < WIDTH; x++)
            {
                for (int y = 0; y < HEIGHT; y++)
                {
                    float xPos = (float)x / WIDTH * 4.5 - 2.5;
                    float yPos = (float)y / HEIGHT * 2 - 1;

                    int iter = mandelbrot(xPos, yPos);
                    Color color = getColor(iter);
                    DrawPixel(x, y, color);
                }
            }

            EndTextureMode();
        //}

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTextureRec(target.texture, (Rectangle){0, 0, WIDTH, -HEIGHT}, (Vector2){0, 0}, WHITE);
       // DrawText("Press ENTER to render the Mandelbrot set", 10, 10, 20, RAYWHITE);
        EndDrawing();
    }

    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}