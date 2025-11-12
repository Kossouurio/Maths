#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include "File.h"

#define M_PI 3.14159265358979323846

class Settings
{
private:
    int _Height = 20;
    int _Width = 100;
    int _MeshResolution = 32;
public:

    Settings(int argc, char* argv[])
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
        }
    }
    
    int GetHeight() const
    {
        return _Height;
    }
    
    int GetWidth() const
    {
        return _Width;
    }

    int GetMeshResolution() const
    {
        return _MeshResolution;
    }
};

class Screen
{
private:
    HANDLE hConsole;
    DWORD mode;
    
    std::vector<char> _pixels;
public:
    Screen(int width, int height)
    {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        mode = DWORD();

        GetConsoleMode(hConsole, &mode);
        SetConsoleMode(hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

        CreateScreen(width, height);
        Draw();
    }

    void HideCursor()
    {
        std::cout << "\033[?25l";
    }

    void ShowCursor()
    {
        std::cout << "\033[?25h";
    }
    
    void ResetCursortPosition()
    {
        std::cout << "\033[H";
    }
    
    void Clear()
    {
        std::cout << "\033[2J";
    }
    
    void CreateScreen(int width, int height)
    {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                _pixels.push_back('.');
            }
            _pixels.push_back('\n');
        }
    }
    
    void Draw()
    {
        Clear();
        ResetCursortPosition();
        HideCursor();
        
        for (char pixel : _pixels)
        {
            std::cout << pixel;
        }
        
        ShowCursor();
    }
    
    std::vector<char> GetPixels()
    {
        return _pixels;
    }
};

struct Vertex
{
    float x;
    float y;
    float z;

    void Debug()
    {
        std::cout << "{" << x << ", " << y << ", " << z << "}";
    }
};
class Mesh
{
private:
    std::vector<Vertex> vertices;
    int resolution;

public:
    Mesh(int resolution)
        : resolution(resolution)
    {
    }

    void GenerateCircle(float radius)
    {
        vertices.clear();
        const float step = 2.0f * M_PI / resolution;

        for (int i = 0; i <= resolution; ++i)
        {
            float angle = i * step;
            Vertex v;
            v.x = radius * cos(angle);
            v.y = radius * sin(angle);
            vertices.push_back(v);
        }
    }

    void GenerateHalfCircle(float radius)
    {
        vertices.clear();
        const float step = M_PI / resolution;

        for (int i = 0; i <= resolution; ++i)
        {
            float angle = i * step;
            Vertex v;
            v.x = radius * cos(angle);
            v.y = radius * sin(angle);
            vertices.push_back(v);
        }
    }

    void GenerateRectangle(float width, float height)
    {
        vertices.clear();

        float halfW = width / 2.0f;
        float halfH = height / 2.0f;

        vertices.push_back({-halfW, -halfH, 0});
        vertices.push_back({halfW, -halfH, 0});
        vertices.push_back({halfW, halfH, 0});
        vertices.push_back({-halfW, halfH, 0});
        vertices.push_back({-halfW, -halfH, 0});
    }

    void GenerateSquare(float size)
    {
        GenerateRectangle(size, size);
    }
    
    void Debug()
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            vertices[i].Debug();
            if (i < vertices.size() - 1)
            {
                std::cout << ", ";
            }
        }
    }
};

int main(int argc, char* argv[])
{
    Settings settings(argc,argv);
    Screen screen(settings.GetWidth(), settings.GetHeight());
    Mesh mesh(settings.GetMeshResolution());
    
    // std::cout << "=== Circle ===" << std::endl;
    // mesh.GenerateCircle(1.0f);
    // mesh.Debug();
    //
    // std::cout << "\n=== Half Circle ===" << std::endl;
    // mesh.GenerateHalfCircle(1.0f);
    // mesh.Debug();
    //
    // std::cout << "\n=== Rectangle ===" << std::endl;
    // mesh.GenerateRectangle(2.0f, 1.0f);
    // mesh.Debug();
    //
    // std::cout << "\n=== Square ===" << std::endl;
    // mesh.GenerateSquare(1.0f);
    // mesh.Debug();
    
    return 0;
}
