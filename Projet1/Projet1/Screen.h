#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>

#include "Mesh.h"

class Settings;
class Screen
{
private:
    HANDLE hConsole;
    DWORD mode;
    
    Settings* _Settings;
    std::vector<std::vector<char>> _pixels;
    int _width, _height;
public:
    Screen(Settings* settings);

    void HideCursor();

    void ShowCursor();

    void ResetCursortPosition();

    void Clear();

    void CreateScreen(int width, int height);

    void Draw();

    void SetPixel(int x, int y, char color);

    void DrawMesh(Mesh& mesh);
    
    std::vector<std::vector<char>> GetPixels();
};
