#include "Screen.h"
#include "Mesh.h"

Screen::Screen(int width, int height)
{
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    mode = DWORD();
    _width = width;
    _height = height;

    GetConsoleMode(hConsole, &mode);
    SetConsoleMode(hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    CreateScreen(width, height);
    Draw();
}

void Screen::HideCursor()
{
    std::cout << "\033[?25l";
}

void Screen::ShowCursor()
{
    std::cout << "\033[?25h";
}

void Screen::ResetCursortPosition()
{
    std::cout << "\033[H";
}

void Screen::Clear()
{
    std::cout << "\033[2J";
}

void Screen::CreateScreen(int width, int height)
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

void Screen::Draw()
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

void Screen::SetPixel(int x, int y, char color)
{
    if (x < 0 || x >= _width || y < 0 || y >= _height)
        return;
    _pixels[x + y * _width] = color;
}

void Screen::DrawMesh(Mesh& mesh)
{
    std::vector<Vertex> vertices = mesh.GetVertices();
    for (Vertex vertex : vertices)
    {
        SetPixel(vertex.x+10, vertex.y+5, 'Q');
    }
}

std::vector<char> Screen::GetPixels()
{
    return _pixels;
}
