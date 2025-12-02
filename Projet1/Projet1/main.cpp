#include <iostream>
#include <windows.h>
#include "Settings.h"
#include "Screen.h"
#include "Mesh.h"

void InitConsole()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hConsole, &mode);
    SetConsoleMode(hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

void ClearConsole()
{
    std::cout << "\x1b[2J"; // Remove all characters in console
    std::cout << "\x1b[H"; // Set cursor pos to "home" position (0,0)
}

void SetCursorVisible(bool visible)
{
    if (visible)
    {
        std::cout << "\x1b[?25h"; // Make cursor visible
    }
    else
    {
        std::cout << "\x1b[?25l"; // Make cursor invisible
    }
}

int main(int argc, char** argv)
{
    InitConsole();
    ClearConsole();
    SetCursorVisible(false);
    Settings settings(argc, argv);
    Screen screen(settings);
    screen.Display();
    Mesh mesh(settings);
    mesh.GenerateRectangle(10.f, 20.f);
    std::cout << "Rectangle 10x20:" << std::endl;
    screen.Display(mesh);
    mesh.GenerateSquare(20.f);
    std::cout << "Square 20x20:" << std::endl;
    screen.Display(mesh);
    mesh.GenerateCircle(15.f);
    std::cout << "Circle radius 15:" << std::endl;
    screen.Display(mesh);
    mesh.GenerateHalfCircle(15.f);
    std::cout << "Half Circle radius 15:" << std::endl;
    screen.Display(mesh);


    std::cin.get();
    return 0;
}