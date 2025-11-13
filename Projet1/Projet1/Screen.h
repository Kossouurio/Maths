#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>

#include "Mesh.h"

class Screen
{
private:
    HANDLE hConsole;
    DWORD mode;
    
    std::vector<char> _pixels;
    int _width, _height;
public:
    Screen(int width, int height);

    void HideCursor();

    void ShowCursor();

    void ResetCursortPosition();

    void Clear();

    void CreateScreen(int width, int height);

    void Draw();

    void SetPixel(int x, int y, char color);

    void DrawMesh(Mesh& mesh);
    
    std::vector<char> GetPixels();
};
