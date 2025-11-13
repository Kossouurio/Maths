#pragma once
#include <string>

class Settings
{
private:
    int _Height = 20;
    int _Width = 100;
    int _MeshResolution = 32;
public:

    Settings(int argc, char* argv[]);

    int GetHeight() const;

    int GetWidth() const;

    int GetMeshResolution() const;
};
