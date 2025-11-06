#include "File.h"
#include <iostream>

const char* File::GetModeString(FileMode mode)
{
    switch (mode)
    {
        case FileMode::Read: return "r";
        case FileMode::Write: return "w";
        case FileMode::Append: return "a";
        case FileMode::ReadBinary: return "rb";
        case FileMode::ReadWriteBinary: return "r+b";
        case FileMode::WriteBinary: return "wb";
        case FileMode::WriteReadBinary: return "w+b";
        case FileMode::AppendBinary: return "ab";
    }
    return "r";
}

File::File()
    : file(nullptr), size(0), filepath(""), filename(""), fileTypeExtension(FileType::Unknown)
{
}

File::File(const std::string& path, FileMode mode)
    : file(nullptr), size(0), filepath(""), filename(""), fileTypeExtension(FileType::Unknown)
{
    Open(path, mode);
}

File::~File()
{
    Close();
}

std::string File::GetFilename(std::string path)
{
    std::string filename;
    if (path.empty())
    {
        filename = "";
    }
    
    size_t pos = path.find_last_of("/\\");
    if (pos == std::string::npos)
    {
        filename = path;
    }
    else
    {
        filename = path.substr(pos + 1);
    }
    
    return filename;
}

FileType File::DetectFileTypeFromHeader()
{
    if (!IsOpen() || size < 4)
        return FileType::Unknown;
    
    long currentPos = Tell();
    Rewind();
    
    unsigned char header[16] = {0};
    size_t bytesRead = Read(header, 1, 16);
    
    Seek(currentPos, SEEK_SET);
    
    if (bytesRead < 4)
        return FileType::Unknown;
    
    // PNG: 89 50 4E 47
    if (header[0] == 0x89 && header[1] == 0x50 && header[2] == 0x4E && header[3] == 0x47)
        return FileType::PNG;
    
    // JPG: FF D8 FF
    if (header[0] == 0xFF && header[1] == 0xD8 && header[2] == 0xFF)
        return FileType::JPG;
    
    // GIF: 47 49 46 38
    if (header[0] == 0x47 && header[1] == 0x49 && header[2] == 0x46 && header[3] == 0x38)
        return FileType::GIF;
    
    // BMP: 42 4D
    if (header[0] == 0x42 && header[1] == 0x4D)
        return FileType::BMP;
    
    // MP3: 49 44 33 (ID3)
    if (header[0] == 0x49 && header[1] == 0x44 && header[2] == 0x33)
        return FileType::MP3;
    
    // MP3: FF FB (MPEG)
    if (header[0] == 0xFF && header[1] == 0xFB)
        return FileType::MP3;
    
    // MP4: starts with ftyp at offset 4
    if (bytesRead >= 8 && header[4] == 0x66 && header[5] == 0x74 && 
        header[6] == 0x79 && header[7] == 0x70)
        return FileType::MP4;
    
    bool isText = true;
    for (size_t i = 0; i < bytesRead && isText; i++)
    {
        if (header[i] != 0x09 && header[i] != 0x0A && header[i] != 0x0D && 
            (header[i] < 0x20 || header[i] > 0x7E))
        {
            isText = false;
        }
    }
    
    if (isText)
        return FileType::Text;
    
    return FileType::Binary;
}

FileType File::GetFileType()
{
    if (fileTypeExtension == FileType::Unknown && IsOpen())
    {
        fileTypeExtension = DetectFileTypeFromHeader();
    }
    return fileTypeExtension;
}

const char* File::GetFileTypeString(FileType type)
{
    switch (type)
    {
        case FileType::PNG: return "PNG Image";
        case FileType::JPG: return "JPEG Image";
        case FileType::GIF: return "GIF Image";
        case FileType::BMP: return "Bitmap Image";
        case FileType::MP3: return "MP3 Audio";
        case FileType::MP4: return "MP4 Video";
        case FileType::Text: return "Text File";
        case FileType::Binary: return "Binary File";
        case FileType::Unknown: return "Unknown";
        default: return "Unknown";
    }
}

FileType File::DetectType(const std::string& path)
{
    File tempFile(path, FileMode::ReadBinary);
    if (!tempFile.IsOpen())
        return FileType::Unknown;
    
    return tempFile.GetFileType();
}

bool File::Open(const std::string& path, FileMode mode)
{
    Close(); // Close previous file if it exists
    
    errno_t err = fopen_s(&file, path.c_str(), GetModeString(mode));
    
    if (err == 0 && file != nullptr)
    {
        filepath = path;
        filename = GetFilename(path);
        
        fseek(file, 0, SEEK_END);
        size = ftell(file);
        fseek(file, 0, SEEK_SET);
        
        fileTypeExtension = FileType::Unknown;
        
        return true;
    }
    
    return false;
}

void File::Close()
{
    if (file != nullptr)
    {
        fclose(file);
        file = nullptr;
        size = 0;
        filepath = "";
        filename = "";
        fileTypeExtension = FileType::Unknown;
    }
}

bool File::IsOpen() const
{
    return file != nullptr;
}

size_t File::Read(void* buffer, size_t elementSize, size_t count)
{
    if (!IsOpen())
        return 0;
    
    return fread(buffer, elementSize, count, file);
}

std::vector<char> File::ReadAll()
{
    if (!IsOpen())
        return std::vector<char>();
    
    long currentPos = ftell(file);
    
    fseek(file, 0, SEEK_END);
    size_t fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    std::vector<char> buffer(fileSize);
    fread(buffer.data(), 1, fileSize, file);
    
    fseek(file, currentPos, SEEK_SET);
    
    return buffer;
}


size_t File::Write(const void* buffer, size_t elementSize, size_t count)
{
    if (!IsOpen())
        return 0;

    size_t written = fwrite(buffer, elementSize, count, file);
    UpdateSize();
    
    return written;
}

size_t File::ModifyBlock(int offset, const void* buffer, int dataSize)
{
    if (!IsOpen())
        return 0;

    long currentPos = Tell();
    Seek(offset, SEEK_SET);
    size_t written = fwrite(buffer, 1, dataSize, file);
    Seek(currentPos, SEEK_SET);

    UpdateSize();
    
    return written;
}

bool File::Seek(long offset, int origin)
{
    if (!IsOpen())
    {
        return false;
    }
    
    return fseek(file, offset, origin) == 0;
}

long File::Tell() const
{
    if (!IsOpen())
    {
        return -1;
    }
    
    return ftell(file);
}

void File::Rewind() const
{
    if (IsOpen())
    {
        rewind(file);
    }
}

void File::Flush() const
{
    fflush(file);
}

size_t File::GetSize() const
{
    return size;
}

const std::string& File::GetPath() const
{
    return filepath;
}

FILE* File::GetHandle() const
{
    return file;
}

bool File::Exists(const std::string& path)
{
    FILE* testFile = nullptr;
    errno_t err = fopen_s(&testFile, path.c_str(), "r");
    
    if (err == 0 && testFile != nullptr)
    {
        fclose(testFile);
        return true;
    }
    
    return false;
}

void File::UpdateSize()
{
    if (!IsOpen())
        return;
    
    long currentPos = ftell(file);
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, currentPos, SEEK_SET);
}

const std::string& File::GetName() const
{
    return filename;
}
