#pragma once
#include <cstdio>
#include <vector>

class Settings;

enum class Axis
{
    X,
    Y,
    Z
};

struct Vertex
{
    void Debug() const { std::printf("[x=%5.2f, y=%5.2f, z=%5.2f]\n", x, y, z); }
    float x;
    float y;
    float z;

    void Rotate(float angle, Axis axis);
    void RotateDegrees(float angleDeg, Axis axis);
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
    void GenerateTorus(float majorRadius, float minorRadius);
    void Debug() const;
    void Rotate(float angle, Axis axis);
    void RotateDegrees(float angleDeg, Axis axis);
    
    private:
    void _GenerateSector(float radius, float angle);

    private:
    std::vector<Vertex> m_vertices;
    int m_resolution;
};