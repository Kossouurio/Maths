#pragma once
#include <iostream>
#include <vector>

#define M_PI 3.14159265358979323846

struct Vertex
{
    float x;
    float y;
    float z;

    void Debug();
};

class Mesh
{
private:
    std::vector<Vertex> vertices;
    int resolution;

public:
    Mesh(int resolution);

    void GenerateCircle(float radius);

    void GenerateHalfCircle(float radius);

    void GenerateRectangle(float width, float height);

    void GenerateSquare(float size);

    std::vector<Vertex> GetVertices();
    
    void Debug();
};
