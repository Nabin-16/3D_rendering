#include <cmath>
#include <algorithm>
#include "headers/matrix.h"

void render_triangle(SDL_Renderer* renderer, const matrix &v1, const matrix &v2, const matrix &v3)
{
    // 28.4 fixed-point coordinates
    const int Y1 = round(16.0f * v1.p[1]);
    const int Y2 = round(16.0f * v2.p[1]);
    const int Y3 = round(16.0f * v3.p[1]);

    const int X1 = round(16.0f * v1.p[0]);
    const int X2 = round(16.0f * v2.p[0]);
    const int X3 = round(16.0f * v3.p[0]);

    // Deltas
    const int DX12 = X1 - X2;
    const int DX23 = X2 - X3;
    const int DX31 = X3 - X1;

    const int DY12 = Y1 - Y2;
    const int DY23 = Y2 - Y3;
    const int DY31 = Y3 - Y1;

    // Fixed-point deltas
    const int FDX12 = DX12 << 4;
    const int FDX23 = DX23 << 4;
    const int FDX31 = DX31 << 4;

    const int FDY12 = DY12 << 4;
    const int FDY23 = DY23 << 4;
    const int FDY31 = DY31 << 4;

    // Bounding rectangle
    int minx = (std::min({X1, X2, X3}) + 0xF) >> 4;
    int maxx = (std::max({X1, X2, X3}) + 0xF) >> 4;
    int miny = (std::min({Y1, Y2, Y3}) + 0xF) >> 4;
    int maxy = (std::max({Y1, Y2, Y3}) + 0xF) >> 4;

    // Half-edge constants
    int C1 = DY12 * X1 - DX12 * Y1;
    int C2 = DY23 * X2 - DX23 * Y2;
    int C3 = DY31 * X3 - DX31 * Y3;

    // Correct for fill convention
    if(DY12 < 0 || (DY12 == 0 && DX12 > 0)) C1++;
    if(DY23 < 0 || (DY23 == 0 && DX23 > 0)) C2++;
    if(DY31 < 0 || (DY31 == 0 && DX31 > 0)) C3++;

    int CY1 = C1 + DX12 * (miny << 4) - DY12 * (minx << 4);
    int CY2 = C2 + DX23 * (miny << 4) - DY23 * (minx << 4);
    int CY3 = C3 + DX31 * (miny << 4) - DY31 * (minx << 4);

    // Set the color for the triangle (white in this case)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for(int y = miny; y < maxy; y++)
    {
        int CX1 = CY1;
        int CX2 = CY2;
        int CX3 = CY3;
   
        for(int x = minx; x < maxx; x++)
        {
            if(CX1 > 0 && CX2 > 0 && CX3 > 0)
            {
                // Draw the pixel
                SDL_RenderDrawPoint(renderer, x, y);
            }

            CX1 -= FDY12;
            CX2 -= FDY23;
            CX3 -= FDY31;
        }

        CY1 += FDX12;
        CY2 += FDX23;
        CY3 += FDX31;
    }
}
