#pragma once
#include <vector>

class Settings;
class Mesh;
struct Vertex;

class Screen
{
    public:
    Screen(Settings const& settings);
    void Display() const;
    void Display(Mesh const& mesh);

    private:
    void _ProjectMesh(Mesh const& mesh);
    void _ProjectInCenterScreenSpace(Vertex& vertex);
    void _ProjectInTopLeftScreenSpace(Vertex& vertex);
    bool _IsVertexInScreen(int u, int v);

    private:
    int m_width;
    int m_height;
    float m_zPosition;
    char m_background;
    char m_meshProjection;
    float m_meshZPosition;
    std::vector<char> m_pixels;
    std::vector<float> m_oozBuffer;
};