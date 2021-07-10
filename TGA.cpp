#include "TGA.h"

using namespace std;

TGA::TGA()
{
    headerObject.idLength = ' ';
    headerObject.colorMapType = ' ';
    headerObject.dataTypeCode = ' ';
    headerObject.colorMapOrigin = 0;
    headerObject.colorMapLength = 0;
    headerObject.colorMapDepth = ' ';
    headerObject.xOrigin = 0;
    headerObject.yOrigin = 0;
    headerObject.width = 0;
    headerObject.height = 0;
    headerObject.bitsPerPixel = ' ';
    headerObject.imageDescriptor = ' ';
    rgb.B = ' ';
    rgb.G = ' ';
    rgb.R = ' ';
}

TGA::TGA(ifstream &file) {
    file.read(&headerObject.idLength, sizeof(headerObject.idLength));
    file.read(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
    file.read(&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
    file.read((char *) &headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
    file.read((char *) &headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
    file.read(&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
    file.read((char *) &headerObject.xOrigin, sizeof(headerObject.xOrigin));
    file.read((char *) &headerObject.yOrigin, sizeof(headerObject.yOrigin));
    file.read((char *) &headerObject.width, sizeof(headerObject.width));
    file.read((char *) &headerObject.height, sizeof(headerObject.height));
    file.read(&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
    file.read(&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));
    int length = headerObject.width * headerObject.height;
    for (int i = 0; i < length; ++i) {
        file.read((char *) &rgb.B, sizeof(rgb.B));
        file.read((char *) &rgb.G, sizeof(rgb.G));
        file.read((char *) &rgb.R, sizeof(rgb.R));
        pixel.push_back(rgb);
    }
}

void TGA::writeHeaderData(ofstream &out)
{
    out.write(&headerObject.idLength, sizeof(headerObject.idLength));
    out.write(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
    out.write(&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
    out.write((char *)&headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
    out.write((char *)&headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
    out.write(&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
    out.write((char *)&headerObject.xOrigin, sizeof(headerObject.xOrigin));
    out.write((char *)&headerObject.yOrigin, sizeof(headerObject.yOrigin));
    out.write((char *)&headerObject.width, sizeof(headerObject.width));
    out.write((char *)&headerObject.height, sizeof(headerObject.height));
    out.write(&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
    out.write(&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));
}

void TGA::writeRBGdata(ofstream &out)
{
    for (unsigned int i = 0; i < pixel.size(); ++i) {
        out.write((char *)&pixel.at(i).B, sizeof(pixel.at(i).B));
        out.write((char *)&pixel.at(i).G, sizeof(pixel.at(i).G));
        out.write((char *)&pixel.at(i).R, sizeof(pixel.at(i).R));
    }
}

void TGA::copyHeaderData(TGA copyFrom)
{
    this->headerObject.idLength = copyFrom.headerObject.idLength;
    this->headerObject.colorMapType = copyFrom.headerObject.colorMapType;
    this->headerObject.dataTypeCode = copyFrom.headerObject.dataTypeCode;
    this->headerObject.colorMapOrigin = copyFrom.headerObject.colorMapOrigin;
    this->headerObject.colorMapLength = copyFrom.headerObject.colorMapLength;
    this->headerObject.colorMapDepth = copyFrom.headerObject.colorMapDepth;
    this->headerObject.xOrigin = copyFrom.headerObject.xOrigin;
    this->headerObject.yOrigin = copyFrom.headerObject.yOrigin;
    this->headerObject.width = copyFrom.headerObject.width;
    this->headerObject.height = copyFrom.headerObject.height;
    this->headerObject.bitsPerPixel = copyFrom.headerObject.bitsPerPixel;
    this->headerObject.imageDescriptor = copyFrom.headerObject.imageDescriptor;
}

TGA& TGA::operator=(const TGA& second)
{
    this->headerObject = second.headerObject;
    this->pixel = second.pixel;
    return* this;
}

TGA& TGA::operator*(const TGA& second)
{
    for (int i = 0; i < this->pixel.size(); ++i) {
        this->pixel.at(i).B = (unsigned char)(((float)((float)this->pixel.at(i).B * (float)second.pixel.at(i).B) / 255) + 0.5f);
        this->pixel.at(i).G = (unsigned char)(((float)((float)this->pixel.at(i).G * (float)second.pixel.at(i).G) / 255) + 0.5f);
        this->pixel.at(i).R = (unsigned char)(((float)((float)this->pixel.at(i).R * (float)second.pixel.at(i).R) / 255) + 0.5f);
    }
    return* this;
}

TGA& TGA::operator-(const TGA& second)
{
    int temp;
    int temp2;
    int temp3;
    for (int i = 0; i < this->pixel.size(); ++i) {
        //B
        temp = (int)this->pixel.at(i).B;
        temp2 = (int)second.pixel.at(i).B;
        temp3 = temp2 - temp;
        if (temp3 < 0){ temp3 = 0; }
        this->pixel.at(i).B = (unsigned char) temp3;
        //G
        temp = (int)this->pixel.at(i).G;
        temp2 = (int)second.pixel.at(i).G;
        temp3 = temp2 - temp;
        if (temp3 < 0){ temp3 = 0;}
        this->pixel.at(i).G = (unsigned char) temp3;
        //R
        temp = (int)this->pixel.at(i).R;
        temp2 = (int)second.pixel.at(i).R;
        temp3 = temp2 - temp;
        if (temp3 < 0){ temp3 = 0; }
        this->pixel.at(i).R = (unsigned char) temp3;
    }
    return* this;
}

TGA& TGA::screenBlendingMode(const TGA& second)
{
    for (int i = 0; i < this->pixel.size(); ++i) {
        this->pixel.at(i).B = (unsigned char)(255 - (((255.0 - (float) this->pixel.at(i).B) * (255 - (float) second.pixel.at(i).B)) / 255.0 - 0.5f));
        this->pixel.at(i).G = (unsigned char)(255 - (((255.0 - (float) this->pixel.at(i).G) * (255 - (float) second.pixel.at(i).G)) / 255.0 - 0.5f));
        this->pixel.at(i).R = (unsigned char)(255 - (((255.0 - (float) this->pixel.at(i).R) * (255 - (float) second.pixel.at(i).R)) / 255.0 - 0.5f));
    }
    return* this;
}

TGA& TGA::OverlayMode(const TGA& second)
{
    float temp = 0.0;
    float temp2 = 0.0;
    for (int i = 0; i < this->pixel.size(); ++i) {
        //B
        temp = (float) this->pixel.at(i).B / 255;
        temp2 = (float) second.pixel.at(i).B / 255;

        if (temp <= 0.5f)
        {
            this->pixel.at(i).B = (unsigned char) (2 * temp * temp2 * 255 + 0.5f);
        } else{
            this->pixel.at(i).B = (unsigned char) ((1 - 2 * (1 - temp) * (1 - temp2)) * 255 + 0.5f);
        }

        temp = (float) this->pixel.at(i).G / 255;
        temp2 = (float) second.pixel.at(i).G / 255;

        //G
        if (temp <= 0.5f)
        {
            this->pixel.at(i).G = (unsigned char) (2 * temp * temp2 * 255 + 0.5f);
        } else{
            this->pixel.at(i).G = (unsigned char) ((1 - 2 * (1 - temp) * (1 - temp2)) * 255 + 0.5f);
        }

        temp = (float) this->pixel.at(i).R / 255;
        temp2 = (float) second.pixel.at(i).R / 255;

        //R
        if (temp <= 0.5f)
        {
            this->pixel.at(i).R = (unsigned char) (2 * temp * temp2 * 255 + 0.5f);
        } else{
            this->pixel.at(i).R = (unsigned char) ((1 - 2 * (1 - temp) * (1 - temp2)) * 255 + 0.5f);
        }
    }
    return* this;
}

TGA& TGA::addGreen()
{
    for (int i = 0; i < this->pixel.size(); ++i) {
        if (((int)this->pixel.at(i).G + 200) > 255){
            this->pixel.at(i).G = (unsigned char) 255;
        } else{
            this->pixel.at(i).G = (unsigned char) ((int)this->pixel.at(i).G + 200);
        }
    }
    return* this;
}

TGA& TGA::mulRedBy4BlueBy0()
{
    for (int i = 0; i < this->pixel.size(); ++i) {
        this->pixel.at(i).B = (unsigned char) 0;
        if ((int)this->pixel.at(i).R * 4 > 255){
            this->pixel.at(i).R = (unsigned char) 255;
        } else{
            this->pixel.at(i).R = (unsigned char) ((int) this->pixel.at(i).R * 4);
        }
    }
    return* this;
}

TGA& TGA::separateChannel(char channel)
{
    for (int i = 0; i < this->pixel.size(); ++i) {
        if (channel == 'B'){
            this->pixel.at(i).G = this->pixel.at(i).B;
            this->pixel.at(i).R = this->pixel.at(i).B;
        } else if (channel == 'G'){
            this->pixel.at(i).R = this->pixel.at(i).G;
            this->pixel.at(i).B = this->pixel.at(i).G;
        } else if (channel == 'R'){
            this->pixel.at(i).G = this->pixel.at(i).R;
            this->pixel.at(i).B = this->pixel.at(i).R;
        }
    }
    return* this;
}

TGA& TGA::addChannel(const TGA& copyFrom, char channel)
{
    for (int i = 0; i < this->pixel.size(); ++i) {
        if (channel == 'R'){
            this->pixel.at(i).R = copyFrom.pixel.at(i).R;
        } else if (channel == 'G'){
            this->pixel.at(i).G = copyFrom.pixel.at(i).G;
        } else if (channel == 'B'){
            this->pixel.at(i).B = copyFrom.pixel.at(i).B;
        }
    }
    return* this;
}

TGA& TGA::FileFlipped(const TGA& original)
{
    this->headerObject = original.headerObject;
    int count = 0;
    for (int i = this->pixel.size() - 1; i >= 0; i--) {
        this->pixel.at(count).R = original.pixel.at(i).R;
        this->pixel.at(count).G = original.pixel.at(i).G;
        this->pixel.at(count).B = original.pixel.at(i).B;
        count++;
    }
    return* this;
}

void TGA::writeFile(ofstream &out)
{
    this->writeHeaderData(out);
    this->writeRBGdata(out);
}

TGA& TGA::testImage(const TGA& object, int testNumber)
{
    testResult = true;
    if (this->headerObject.idLength != object.headerObject.idLength){testResult = false;}
    if (this->headerObject.colorMapType != object.headerObject.colorMapType){testResult = false;}
    if (this->headerObject.dataTypeCode != object.headerObject.dataTypeCode){testResult = false;}
    if (this->headerObject.colorMapOrigin != object.headerObject.colorMapOrigin){testResult = false;}
    if (this->headerObject.colorMapLength != object.headerObject.colorMapLength){testResult = false;}
    if (this->headerObject.colorMapDepth != object.headerObject.colorMapDepth){testResult = false;}
    if (this->headerObject.xOrigin != object.headerObject.xOrigin){testResult = false;}
    if (this->headerObject.yOrigin != object.headerObject.yOrigin){testResult = false;}
    if (this->headerObject.width != object.headerObject.width){testResult = false;}
    if (this->headerObject.height != object.headerObject.height){testResult = false;}
    if (this->headerObject.bitsPerPixel != object.headerObject.bitsPerPixel){testResult = false;}
    if (this->headerObject.imageDescriptor != object.headerObject.imageDescriptor){testResult = false;}

    if (testResult){
        for (int i = 0; i < this->pixel.size(); ++i) {
            if (this->pixel.at(i).R != object.pixel.at(i).R || this->pixel.at(i).G != object.pixel.at(i).G || this->pixel.at(i).B != object.pixel.at(i).B){
                testResult = false;
                break;
            }
        }
    }

    cout << "Test #" << testNumber << "...... ";
    if (testResult){cout << "Passed!" << endl;}
    else{cout << "Failed!" << endl;}

    return* this;
}

bool TGA::getTestResult()
{
    return testResult;
}

string TGA::getFailedTestDetail(const TGA& newFile, const TGA& object)
{
    ostringstream output;
    for (int i = 0; i < object.pixel.size(); ++i) {
        if (newFile.pixel.at(i).R != object.pixel.at(i).R || newFile.pixel.at(i).G != object.pixel.at(i).G || newFile.pixel.at(i).B != object.pixel.at(i).B){
            output << endl;
            output << "index: " << i << endl;
            output << "This               |                  object" << endl;
            output << "R: " << (float)this->pixel.at(i).R << "\t" << (float)object.pixel.at(i).R << endl;
            output << "G: " << (float)this->pixel.at(i).G << "\t" << (float)object.pixel.at(i).G << endl;
            output << "B: " << (float)this->pixel.at(i).B << "\t" << (float)object.pixel.at(i).B << endl;
        }
    }
    return output.str();
}

TGA& TGA::combineFourImage(const TGA& imageTopLeft,const TGA& imageTopRight,const TGA& imageButtonLeft,const TGA& imageButtonRight)
{
    this->headerObject = imageButtonRight.headerObject;
    this->headerObject.width = 1024;
    this->headerObject.height = 1024;

    int currentCount = 0;
    int currentCount2 = 0;
    int currentCount3 = 0;
    int currentCount4 = 0;

    for (int i = 0; i < 1024; i++) {
        if (i < 512){
            for (int j = 0; j < 512; ++j) {
                this->rgb = imageButtonRight.pixel.at(currentCount);
                this->pixel.push_back(this->rgb);
                currentCount++;
            }
            for (int j = 0; j < 512; ++j) {
                this->rgb = imageButtonLeft.pixel.at(currentCount2);
                this->pixel.push_back(this->rgb);
                currentCount2++;
            }
            }else{
            for (int j = 0; j < 512; ++j) {
                this->rgb = imageTopLeft.pixel.at(currentCount3);
                this->pixel.push_back(this->rgb);
                currentCount3++;
            }
            for (int j = 0; j < 512; ++j) {
                this->rgb = imageTopRight.pixel.at(currentCount4);
                this->pixel.push_back(this->rgb);
                currentCount4++;
            }
        }
    }
}

//my test methods below.

string TGA::printRGB_test()
{
    cout << to_string(pixel.at(0).R) <<endl;
    cout << to_string(pixel.at(0).G) <<endl;
    cout << to_string(pixel.at(0).B) <<endl;
}

void TGA::createTGAFile_test()//test passed
{
    char* path = "2.tga";
    ofstream out(path, ios::binary | ios::out);

    out.write(&headerObject.idLength, sizeof(headerObject.idLength));
    out.write(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
    out.write(&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
    out.write((char *)&headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
    out.write((char *)&headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
    out.write(&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
    out.write((char *)&headerObject.xOrigin, sizeof(headerObject.xOrigin));
    out.write((char *)&headerObject.yOrigin, sizeof(headerObject.yOrigin));
    out.write((char *)&headerObject.width, sizeof(headerObject.width));
    out.write((char *)&headerObject.height, sizeof(headerObject.height));
    out.write(&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
    out.write(&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));
    for (unsigned int i = 0; i < pixel.size(); ++i) {
        out.write((char *)&pixel.at(i).B, sizeof(pixel.at(i).B));
        out.write((char *)&pixel.at(i).G, sizeof(pixel.at(i).G));
        out.write((char *)&pixel.at(i).R, sizeof(pixel.at(i).R));
    }
    out.close();

}

