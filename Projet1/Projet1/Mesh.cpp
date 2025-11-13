#include "Mesh.h"

void Vertex::Debug()
{
    std::cout << "{" << x << ", " << y << ", " << z << "}";
}

Mesh::Mesh(int resolution): resolution(resolution)
{
}

void Mesh::GenerateCircle(float radius)
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

void Mesh::GenerateHalfCircle(float radius)
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

void Mesh::GenerateRectangle(float width, float height)
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

void Mesh::GenerateSquare(float size)
{
    GenerateRectangle(size, size);
}

std::vector<Vertex> Mesh::GetVertices()
{
    return vertices;
}

void Mesh::Debug()
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
