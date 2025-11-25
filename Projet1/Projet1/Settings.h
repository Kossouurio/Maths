#pragma once
#include <string>

class Settings
{
private:
    int _Height = 20;
    int _Width = 100;
    int _MeshResolution = 32;

    char _ScreenBackground = ' ';
    char _ScreenMeshProjection = 'X';
    float _ScreenPosition = 3.33f;
    int _MeshPosition = 5;

public:

    Settings(int argc, char* argv[]);

    int GetHeight() const;
    int GetWidth() const;
    int GetMeshResolution() const;
    int GetScreenBackground() const;
    int GetScreenMeshProjection() const;
    int GetScreenPosition() const;
    int GetMeshPosition() const;
};
