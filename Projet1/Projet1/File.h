#pragma once
#include <string>
#include <vector>


enum class FileMode
{
    Read,           // "r"
    Write,          // "w"
    Append,         // "a"
    ReadBinary,     // "rb"
    ReadWriteBinary, // "r+b"
    WriteBinary,    // "wb"
    WriteReadBinary,    // "w+b"
    AppendBinary    // "ab"
};

enum class FileType
{
    Unknown,
    PNG,        // 89 50 4E 47
    JPG,        // FF D8 FF
    GIF,        // 47 49 46 38
    BMP,        // 42 4D
    MP3,        // 49 44 33 or FF FB
    MP4,        // 66 74 79 70
    Text,       // ASCII text
    Binary      // Generic binary
};

class File
{
private:
    FILE* file = nullptr;
    size_t size = 0;
    std::string filepath = "";
    std::string filename = "";
    FileType fileTypeExtension = FileType::Unknown;
    
    static const char* GetModeString(FileMode mode);
    
    FileType DetectFileTypeFromHeader();
    
public:
    File();
    File(const std::string& path, FileMode mode);
    ~File();
    
    bool Open(const std::string& path, FileMode mode);
    void Close();
    bool IsOpen() const;
    
    size_t Read(void* buffer, size_t elementSize, size_t count);
    std::vector<char> ReadAll();
    
    size_t Write(const void* buffer, size_t elementSize, size_t count);
    size_t ModifyBlock(int offset, const void* buffer, int dataSize);
    
    bool Seek(long offset, int origin);
    long Tell() const;
    void Rewind() const;
    void Flush() const;
    
    void UpdateSize();
    const std::string& GetName() const;
    
    size_t GetSize() const;
    const std::string& GetPath() const;
    FILE* GetHandle() const;
    FileType GetFileType();
    
    static const char* GetFileTypeString(FileType type);
    static bool Exists(const std::string& path);
    static FileType DetectType(const std::string& path);
    static std::string GetFilename(std::string path);
};

