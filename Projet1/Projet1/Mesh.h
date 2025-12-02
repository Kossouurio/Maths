#pragma once
#include <cstdio>
#include <vector>

class Settings;

struct Vertex
{
    void Debug() const { std::printf("[x=%5.2f, y=%5.2f, z=%5.2f]\n", x, y, z); }
    float x;
    float y;
    float z;
};

class Mesh
{
    public:
    Mesh(Settings const& settings);
    std::vector<Vertex> const& GetVertices() const { return m_vertices; }
    void GenerateCircle(float radius);
    void GenerateHalfCircle(float radius);
    void GenerateRectangle(float width, float height);
    void GenerateSquare(float side);
    void Debug() const;

    private:
    void _GenerateSector(float radius, float angle);

    private:
    std::vector<Vertex> m_vertices;
    int m_resolution;
};