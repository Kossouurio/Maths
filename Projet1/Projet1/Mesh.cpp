#include <cmath>
#include "Mesh.h"
#include "Settings.h"

constexpr float PI = 3.14159265f;

void Vertex::Rotate(float angle, Axis axis)
{
    Vertex prev = *this;
    
    float cosAngle = std::cos(angle);
    float sinAngle = std::sin(angle);
    
    switch(axis)
    {
    case Axis::X:
        y = prev.y * cosAngle - prev.z * sinAngle;
        z = prev.y * sinAngle + prev.z * cosAngle;
        break;
    case Axis::Y:
        x = prev.x * cosAngle + prev.z * sinAngle;
        z = -prev.x * sinAngle + prev.z * cosAngle;
        break;
    case Axis::Z:
        x = prev.x * cosAngle - prev.y * sinAngle;
        y = prev.x * sinAngle + prev.y * cosAngle;
        break;
    }
}

void Vertex::RotateDegrees(float angleDeg, Axis axis)
{
    Rotate(angleDeg * PI / 180.0f, axis);
}

Mesh::Mesh(Settings const& settings)
: m_resolution(settings.GetMeshResolution())
{
}

void Mesh::GenerateCircle(float radius)
{
    _GenerateSector(radius, 2 * PI);
}

void Mesh::GenerateHalfCircle(float radius)
{
    _GenerateSector(radius, PI);
}

void Mesh::GenerateRectangle(float width, float height)
{
    m_vertices.resize(m_resolution * m_resolution);
    for(int i = 0; i < m_resolution; i++)
    {
        for(int j = 0; j < m_resolution; j++)
        {
            m_vertices[m_resolution * i + j].x = (1.f*i / (m_resolution - 1) - 0.5f) * width;
            m_vertices[m_resolution * i + j].y = (1.f*j / (m_resolution - 1) - 0.5f) * height;
            m_vertices[m_resolution * i + j].z = 0.f;
        }
    }
}
void Mesh::GenerateSquare(float side)
{
    GenerateRectangle(side, side);
}

void Mesh::GenerateTorus(float majorRadius, float minorRadius)
{
    /// Parametric formula
    ///x(θ,φ)=(R+r⋅cos(φ))cos(θ)
    ///y(θ,φ)=(R+r⋅cos(φ))sin(θ)
    ///z(θ,φ)=r⋅sin(φ)
    // ( x 2 + y 2 − R ) 2 + z 2 = r 2
    
    m_vertices.resize(m_resolution * m_resolution);
    
    for (int i = 0; i < m_resolution; ++i)
    {
        float u = 2.0f * PI * i / m_resolution;
        float cosu = std::cos(u);
        float sinu = std::sin(u);

        for (int j = 0; j < m_resolution; ++j)
        {
            float v = 2.0f * PI * j / m_resolution;
            float cosv = std::cos(v);
            float sinv = std::sin(v);

            int idx = m_resolution * i + j;
            float x = (majorRadius + minorRadius * cosv) * cosu;
            float y = (majorRadius + minorRadius * cosv) * sinu;
            float z = minorRadius * sinv;

            m_vertices[idx].x = x;
            m_vertices[idx].y = y;
            m_vertices[idx].z = z;

            m_vertices[idx].nx = cosu;
            m_vertices[idx].ny = sinu;
            m_vertices[idx].nz = 0.0f;
        }
    }
}

void Mesh::Debug() const
{
    for(Vertex const& vertex : m_vertices)
    {
        vertex.Debug();
    }
}

void Mesh::Rotate(float angle, Axis axis)
{
    for(Vertex& vertex : m_vertices)
    {
        vertex.Rotate(angle, axis);
    }
}

void Mesh::RotateDegrees(float angleDeg, Axis axis)
{
    float rad = angleDeg * PI / 180.0f;
    for (Vertex& vertex : m_vertices)
    {
        vertex.Rotate(rad, axis);
    }
}

void Mesh::_GenerateSector(float radius, float angle)
{
    m_vertices.resize(m_resolution * m_resolution);
    for(int i = 0; i < m_resolution; i++)
    {
        float r = (radius * i) / (m_resolution - 1);
        for(int j = 0; j < m_resolution; j++)
        {
            float theta = (angle * j) / (m_resolution - 1);
            m_vertices[m_resolution * i + j].x = r * std::cos(theta);
            m_vertices[m_resolution * i + j].y = r * std::sin(theta);
            m_vertices[m_resolution * i + j].z = 0.f;

            m_vertices[m_resolution * i + j].nx = std::cos(theta);
            m_vertices[m_resolution * i + j].ny = std::sin(theta);
            m_vertices[m_resolution * i + j].nz = 0.f;
        }
    }
}
