#include <cmath>
#include "Mesh.h"
#include "Settings.h"

constexpr float PI = 3.14159265f;

void Vertex::Rotate(float angle, Axis axis)
{
    float cosAngle = std::cos(angle);
    float sinAngle = std::sin(angle);
    float newX, newY, newZ;
    
    switch(axis)
    {
    case Axis::X:
        newY = y * cosAngle - z * sinAngle;
        newZ = y * sinAngle + z * cosAngle;
        y = newY;
        z = newZ;
        break;
    case Axis::Y:
        newX = x * cosAngle + z * sinAngle;
        newZ = -x * sinAngle + z * cosAngle;
        x = newX;
        z = newZ;
        break;
    case Axis::Z:
        newX = x * cosAngle - y * sinAngle;
        newY = x * sinAngle + y * cosAngle;
        x = newX;
        y = newY;
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
    // // theta goes around the cross-sectional circle of a torus
    // for (float theta=0; theta < 2*pi; theta += theta_spacing)
    // {
    //     // precompute sines and cosines of theta
    //     float costheta = cos(theta), sintheta = sin(theta);
    //
    //     // phi goes around the center of revolution of a torus
    //     for(float phi=0; phi < 2*pi; phi += phi_spacing)
    //     {
    //         // precompute sines and cosines of phi
    //         float cosphi = cos(phi), sinphi = sin(phi);
    //
    //         // the x,y coordinate of the circle, before revolving (factored
    //         // out of the above equations)
    //         float circlex = R2 + R1*costheta;
    //         float circley = R1*sintheta;
    //
    //         // final 3D (x,y,z) coordinate after rotations, directly from
    //         // our math above
    //         float x = circlex*(cosB*cosphi + sinA*sinB*sinphi)
    //           - circley*cosA*sinB; 
    //         float y = circlex*(sinB*cosphi - sinA*cosB*sinphi)
    //           + circley*cosA*cosB;
    //         float z = K2 + cosA*circlex*sinphi + circley*sinA;
    //         float ooz = 1/z;  // "one over z"
    //   
    //         // x and y projection.  note that y is negated here, because y
    //         // goes up in 3D space but down on 2D displays.
    //         int xp = (int) (screen_width/2 + K1*ooz*x);
    //         int yp = (int) (screen_height/2 - K1*ooz*y);
    //     }
    // }
    
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
        }
    }
}
