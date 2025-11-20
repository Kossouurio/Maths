#include "Mesh.h"

void Vertex::Debug()
{
    std::cout << "{" << x << ", " << y << ", " << z << "}";
}

Mesh::Mesh(int resolution)
    : resolution(resolution)
{
}

void Mesh::GenerateCircle(float radius)
{
    vertices.clear();

    for (int i = 0; i < resolution; ++i)
    {
        float angle = 2.0f * M_PI * i / resolution;
        Vertex v;
        v.x = radius * cos(angle);
        v.y = radius * sin(angle);
        v.z = 0.0f;
        vertices.push_back(v);
    }
}

void Mesh::GenerateHalfCircle(float radius)
{
    vertices.clear();

    for (int i = 0; i < resolution; ++i)
    {
        float angle = M_PI * i / (resolution - 1);
        Vertex v;
        v.x = radius * cos(angle);
        v.y = radius * sin(angle);
        v.z = 0.0f;
        vertices.push_back(v);
    }
}

void Mesh::GenerateRectangle(float width, float height)
{
    vertices.clear();

    int maxPoints = resolution * resolution;
    Vertex* points = new Vertex[maxPoints];
    int pointCount = 0;

    float stepX = width / resolution;
    float stepY = height / resolution;

    for (int y = 0; y < resolution; ++y)
    {
        for (int x = 0; x < resolution; ++x)
        {
            points[pointCount].x = (x * stepX) - (width / 2.0f);
            points[pointCount].y = (y * stepY) - (height / 2.0f);
            points[pointCount].z = 0.0f;
            pointCount++;
        }
    }

    for (int i = 0; i < pointCount; ++i)
    {
        vertices.push_back(points[i]);
    }

    delete[] points;
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
    std::cout << "Mesh with " << vertices.size() << " vertices:" << '\n';
    for (int i = 0; i < vertices.size(); i++)
    {
        vertices[i].Debug();
        if (i < vertices.size() - 1)
        {
            std::cout << ", ";
        }
    }
}
