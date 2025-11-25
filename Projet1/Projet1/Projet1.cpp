#include <iostream>

#include "Mesh.h"
#include "Screen.h"
#include "Settings.h"

int main(int argc, char* argv[])
{
    Settings settings(argc,argv);
    Screen screen(&settings);
    Mesh mesh(settings.GetMeshResolution());

    
    //std::cout << "=== Circle ===" << '\n';
    //mesh.GenerateCircle(3.0f);
    //screen.DrawMesh(mesh);
    //screen.Draw();
    //
    // std::cout << "\n=== Half Circle ===" << '\n';
    // mesh.GenerateHalfCircle(3.0f);
    // screen.DrawMesh(mesh);
    // screen.Draw();
    //
     std::cout << "\n=== Rectangle ===" << '\n';
     mesh.GenerateRectangle(4.0f, 3.0f);
     screen.DrawMesh(mesh);
     screen.Draw();
    //
    // std::cout << "\n=== Square ===" << '\n';
    // mesh.GenerateSquare(5.0f);
    // screen.DrawMesh(mesh);
    // screen.SetPixel(1, 1, 'G');
    // screen.Draw();

    std::cin.get();
    return 0;
}
