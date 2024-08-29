#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define u32 uint32_t

struct error
{
    std::string what;
} err; 

struct Box
{
    int size; //32
    std::string name; //fytp
} box;

class FtypBox
{
public:
    std::string majorBrand;
    u32 minorVersion;

    // To the end of the box
    std::string compatibleBrands;

} FileTypeBox; 

bool ReadBoxData();
bool GetLastError();
bool FindBrands(std::string buffer);

int main()
{
    if (!ReadBoxData())
    {
        std::cerr << "Reading Box Data Failed! -> " << GetLastError() << std::endl;
    }
}


// I have no idea what i am doing atp...
bool ReadBoxData()
{

    std::ifstream videoFile("C:\\Users\\Robed\\Videos\\0318.mp4", std::ios::binary);

    if (!videoFile) {
        err.what = "Failed reading video file, path could be wrong!";
        videoFile.close();
        return false;
    }


    std::cout << "Reading Data!" << std::endl;

    char buffer[32];
    videoFile.read(buffer, sizeof(buffer));

    std::string bufferString(buffer, 32);  

    std::cout << bufferString << std::endl;
    std::cout << std::endl;

                                //Chat i might have been slow lol
    if (bufferString.find("mp4") == std::string::npos)
    {
        err.what = "File was not a mp4!";
        return false;
    }

    std::cout << "Finding Brands! " << std::endl;
    std::cout << std::endl;
    if (!FindBrands(bufferString))
    {
        err.what = "Could not find Major Brand Version!";
        return false;
    }
    std::cout << "Done finding brands!" << std::endl;
    std::cout << std::endl;

    std::cout << "Box Details: " << std::endl;
    std::cout << "Box Name: " << box.name << std::endl;
    std::cout << "Major Brand Version: " << FileTypeBox.majorBrand << std::endl;
    std::cout << "Minor Brand Version: " << FileTypeBox.minorVersion << std::endl;
    std::cout << "Compatible Brands: " << FileTypeBox.compatibleBrands << std::endl;

    std::cout << std::endl;

    std::cout << "Finished Reading Data!" << std::endl;

    videoFile.close();

    return true;
}

bool GetLastError()
{
    if (err.what.empty())
    {
        std::cout << "Error is empty" << std::endl;
        return false;
    }

    std::cout << err.what;

    return true;
}

bool FindBrands(std::string buffer)
{
    // Access the string's data
    const char* data = buffer.data();

    // Read bytes from specific positions
    std::string name(data + 4, 4);   // Read 4 bytes starting from position 4 (ftyp)
    std::string major(data + 8, 4);   // Read 4 bytes starting from position 8 (isom)
    
    box.name = name;

    FileTypeBox.majorBrand = major;
    FileTypeBox.minorVersion = 0; // Until I find a fix for whitespace

    //holy sigma!
    std::string brands(data + 12, (32-12));

    FileTypeBox.compatibleBrands = brands;


    return true;
}
