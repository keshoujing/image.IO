#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <sstream>

using namespace std;

class TGA{

    struct Header
    {
        char idLength;
        char colorMapType;
        char dataTypeCode;
        short colorMapOrigin;
        short colorMapLength;
        char colorMapDepth;
        short xOrigin;
        short yOrigin;
        short width;
        short height;
        char bitsPerPixel;
        char imageDescriptor;
    };

    Header headerObject;

    struct RGB
    {
        unsigned char R;
        unsigned char G;
        unsigned char B;
    };

    RGB rgb;

    vector<RGB> pixel;

    bool testResult = true;

public:
    TGA();
    TGA(ifstream &file);
    void writeHeaderData(ofstream &out);
    void writeRBGdata(ofstream &out);
    void copyHeaderData(TGA copyFrom);
    TGA& operator=(const TGA& second);
    TGA& operator*(const TGA& second);
    TGA& operator-(const TGA& second);
    TGA& screenBlendingMode(const TGA& second);
    TGA& OverlayMode(const TGA& second);
    TGA& addGreen();
    TGA& mulRedBy4BlueBy0();
    TGA& separateChannel(char channel);
    TGA& addChannel(const TGA& copyFrom, char channel);
    TGA& FileFlipped(const TGA& original);
    void writeFile(ofstream &out);
    TGA& testImage(const TGA& object, int testNumber);
    bool getTestResult();
    string getFailedTestDetail(const TGA& newFile, const TGA& object);
    TGA& combineFourImage(const TGA& imageTopLeft,const TGA& imageTopRight,const TGA& imageButtonLeft,const TGA& imageButtonRight);
    //My test methods below, can be ignored
    string printRGB_test();
    void createTGAFile_test();

};