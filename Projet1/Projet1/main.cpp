#include <iostream>
#include <signal.h>
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

void OnKill(int signum)
{
    ClearConsole();
    SetCursorVisible(true);
}

int main(int argc, char** argv)
{
    signal(SIGINT, OnKill);
    InitConsole();
    ClearConsole();
    SetCursorVisible(false);
    Settings settings(argc, argv);
    Screen screen(settings);
    screen.Display();
    Mesh mesh(settings);
    std::cout << "Rectangle 10x20:" << '\n';
    mesh.GenerateRectangle(10.f, 20.f);
    screen.Display(mesh);
    std::cout << "Square 20x20:" << '\n';
    mesh.GenerateSquare(20.f);
    mesh.RotateDegrees(45.f, Axis::Z);
    screen.Display(mesh);
    std::cout << "Circle radius 15:" << '\n';
    mesh.GenerateCircle(15.f);
    screen.Display(mesh);
    std::cout << "Half Circle radius 15:" << '\n';
    mesh.GenerateHalfCircle(15.f);
    mesh.RotateDegrees(90.f, Axis::Z);
    screen.Display(mesh);
    ClearConsole();
    std::cout << "Torus radius 10:" << '\n';
    mesh.GenerateTorus(4.f, 0.9f);
    int frame = 0;
    while (true)
    {
        Sleep(settings.GetFrameDuration());

        mesh.Rotate(settings.GetMeshRotationXPerFrame(), Axis::X);
        mesh.Rotate(settings.GetMeshRotationYPerFrame(), Axis::Y);
        mesh.Rotate(settings.GetMeshRotationZPerFrame(), Axis::Z);
        screen.Display(mesh);
        std::cout << "\x1b[H"; // Set cursor pos to "home" position (0,0)
    }

    std::cin.get();
    return 0;
}