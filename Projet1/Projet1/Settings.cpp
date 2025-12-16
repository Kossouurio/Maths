#include "Settings.h"
#include <string>

Settings::Settings(int argc, char** argv)
: m_screenWidth(100)
, m_screenHeight(20)
, m_screenBackground(' ')
, m_screenMeshProjection('X')
, m_screenPosition(30.f)
, m_meshResolution(128)
, m_meshPosition(10.f)
, m_xAxis(0.02f)
, m_yAxis(0.04f)
, m_zAxis(0.0f)
, m_frameDuration(1)
{
    _ParseArguments(argc, argv);
}

void Settings::_ParseArguments(int argc, char** argv)
{
    // Elegant solution from @T.Rosselet
    for (int i = 1; i < argc; i++) //i starts at 1 because command line arguments start with argv[1] (argv[0] is the name of the exe)
    {
        std::string arg = argv[i];
        if (arg == "-w" && i + 1 < argc)
        {
            m_screenWidth = std::atoi(argv[i+1]);
            i++;
        }
        else if (arg == "-h" && i + 1 < argc)
        {
            m_screenHeight = std::atoi(argv[i+1]);
            i++;
        }
        else if (arg == "-b" && i + 1 < argc)
        {
            m_screenBackground = argv[i+1][0];
            i++;
        }
        else if (arg == "-p" && i + 1 < argc)
        {
            m_screenMeshProjection = argv[i+1][0];
            i++;
        }
        else if (arg == "-s" && i + 1 < argc)
        {
            m_screenPosition = std::atof(argv[i+1]);
            i++;
        }
        else if (arg == "-r" && i + 1 < argc)
        {
            m_meshResolution = std::atoi(argv[i+1]);
            i++;
        }
        else if (arg == "-m" && i + 1 < argc)
        {
            m_meshPosition = std::atof(argv[i+1]);
            i++;
        }
        else if (arg == "-x" && i + 1 < argc)
        {
            m_xAxis = std::atof(argv[i+1]);
            i++;
        }
        else if (arg == "-y" && i + 1 < argc)
        {
            m_yAxis = std::atof(argv[i+1]);
            i++;
        }
        else if (arg == "-z" && i + 1 < argc)
        {
            m_zAxis = std::atof(argv[i+1]);
            i++;
        }
        else if (arg == "-f" && i + 1 < argc)
        {
            m_frameDuration = std::atoi(argv[i+1]);
            i++;
        }
    }
}