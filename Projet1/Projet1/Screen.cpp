#include "Screen.h"
#include "Mesh.h"
#include "Settings.h"

Screen::Screen(Settings* settings)
{
    _Settings = settings;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    mode = DWORD();
    _width = settings->GetWidth();
    _height = settings->GetHeight();

    GetConsoleMode(hConsole, &mode);
    SetConsoleMode(hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    CreateScreen(_width, _height);
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
        std::vector<char> temp;
        for (int x = 0; x < width; x++)
        {
            temp.push_back('.');
        }
        _pixels.push_back(temp);
    }
}

void Screen::Draw()
{
    Clear();
    ResetCursortPosition();
    HideCursor();
        
    for (int y = 0; y < _height; y++)
    {
        for (int x = 0; x < _width; x++)
        {
            std::cout << _pixels[y][x];
        }
        std::cout << '\n';
    }
        
    ShowCursor();
}

void Screen::SetPixel(int x, int y, char color)
{
    if (x >= 0 && x < _width && y >= 0 && y < _height)
        _pixels[y][x] = color;
}

void Screen::DrawMesh(Mesh& mesh)
{
    std::vector<Vertex> vertices = mesh.GetVertices();
    for (Vertex vertex : vertices)
    {
        SetPixel((int)vertex.x+20, (int)vertex.y+5, 'X');
    }
}

std::vector<std::vector<char>> Screen::GetPixels()
{
    return _pixels;
}
