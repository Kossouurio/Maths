#include "Settings.h"

Settings::Settings(int argc, char* argv[])
{
    _Height = 20;
    _Width = 100;
    _MeshResolution = 32;
        
    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];
        if (arg == "-h" && i+1 < argc)
        {
            _Height = std::atoi(argv[i+1]);
            i++;
        }
        else if (arg == "-w" && i+1 < argc)
        {
            _Width = std::atoi(argv[i+1]);
            i++;
        }
        else if (arg == "-r" && i+1 < argc)
        {
            _MeshResolution = std::atoi(argv[i+1]);
        }
        else if (arg == "-b" && i+1 < argc)
        {
            _ScreenBackground = std::atoi(argv[i+1]);
            i++;
        }
        else if (arg == "-p" && i+1 < argc)
        {
            _ScreenMeshProjection = std::atoi(argv[i+1]);
        }
        else if (arg == "-s" && i+1 < argc)
        {
            _ScreenPosition = std::atoi(argv[i+1]);
            i++;
        }
        else if (arg == "-m" && i+1 < argc)
        {
            _MeshPosition = std::atoi(argv[i+1]);
        }
    }
}

int Settings::GetHeight() const
{
    return _Height;
}

int Settings::GetWidth() const
{
    return _Width;
}

int Settings::GetMeshResolution() const
{
    return _MeshResolution;
}

int Settings::GetScreenBackground() const
{
    return _ScreenBackground;
}

int Settings::GetScreenMeshProjection() const
{
    return _ScreenMeshProjection;
}

int Settings::GetScreenPosition() const
{
    return _ScreenPosition;
}

int Settings::GetMeshPosition() const
{
    return _MeshPosition;
}
