#include <iostream>

#include "Mesh.h"
#include "Screen.h"
#include "Settings.h"

int main(int argc, char* argv[])
{
    Settings settings(argc,argv);
    Screen screen(settings.GetWidth(), settings.GetHeight());
    Mesh mesh(settings.GetMeshResolution());

    
    // std::cout << "=== Circle ===" << '\n';
    // mesh.GenerateCircle(1.0f);
    // mesh.Debug();
    //
    // std::cout << "\n=== Half Circle ===" << '\n';
    // mesh.GenerateHalfCircle(1.0f);
    // mesh.Debug();
    //
    std::cout << "\n=== Rectangle ===" << '\n';
    mesh.GenerateRectangle(2.0f, 1.0f);
    screen.DrawMesh(mesh);
    screen.SetPixel(0, 5, 'G');
    screen.Draw();
    
    mesh.Debug();
    //
    // std::cout << "\n=== Square ===" << '\n';
    // mesh.GenerateSquare(1.0f);
    // mesh.Debug();

    std::cin.get();
    return 0;
}
