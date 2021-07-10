#include <iostream>
#include <fstream>
#include "TGA.h"
using namespace std;

char imageToChar(ifstream &file);

int main() {
    //open tga file
    ifstream layer1_TGA("layer1.tga", ios::in | ios::binary);
    ifstream pattern1_TGA("pattern1.tga", ios::in | ios::binary);
    ifstream layer2_TGA("layer2.tga", ios::in | ios::binary);
    ifstream car_TGA("car.tga", ios::in | ios::binary);
    ifstream pattern2_TGA("pattern2.tga", ios::in | ios::binary);
    ifstream text_TGA("text.tga", ios::in | ios::binary);
    ifstream circles_TGA("circles.tga", ios::in | ios::binary);
    ifstream layer_red_TGA("layer_red.tga", ios::in | ios::binary);
    ifstream layer_green_TGA("layer_green.tga", ios::in | ios::binary);
    ifstream layer_blue_TGA("layer_blue.tga", ios::in | ios::binary);
    ifstream text2_TGA("text2.tga", ios::in | ios::binary);

    //open example tga file
    ifstream EXAMPLE_extracredit_TGA("EXAMPLE_extracredit.tga", ios::in | ios::binary);
    ifstream EXAMPLE_part1_TGA("EXAMPLE_part1.tga", ios::in | ios::binary);
    ifstream EXAMPLE_part2_TGA("EXAMPLE_part2.tga", ios::in | ios::binary);
    ifstream EXAMPLE_part3_TGA("EXAMPLE_part3.tga", ios::in | ios::binary);
    ifstream EXAMPLE_part4_TGA("EXAMPLE_part4.tga", ios::in | ios::binary);
    ifstream EXAMPLE_part5_TGA("EXAMPLE_part5.tga", ios::in | ios::binary);
    ifstream EXAMPLE_part6_TGA("EXAMPLE_part6.tga", ios::in | ios::binary);
    ifstream EXAMPLE_part7_TGA("EXAMPLE_part7.tga", ios::in | ios::binary);
    ifstream EXAMPLE_part8_b_TGA("EXAMPLE_part8_b.tga", ios::in | ios::binary);
    ifstream EXAMPLE_part8_g_TGA("EXAMPLE_part8_g.tga", ios::in | ios::binary);
    ifstream EXAMPLE_part8_r_TGA("EXAMPLE_part8_r.tga", ios::in | ios::binary);
    ifstream EXAMPLE_part9_TGA("EXAMPLE_part9.tga", ios::in | ios::binary);
    ifstream EXAMPLE_part10_TGA("EXAMPLE_part10.tga", ios::in | ios::binary);

    //add to TGA.h
    TGA layer1(layer1_TGA);
    TGA pattern1(pattern1_TGA);
    TGA layer2(layer2_TGA);
    TGA car(car_TGA);
    TGA pattern2(pattern2_TGA);
    TGA text(text_TGA);
    TGA circles(circles_TGA);
    TGA layer_red(layer_red_TGA);
    TGA layer_green(layer_green_TGA);
    TGA layer_blue(layer_blue_TGA);
    TGA text2(text2_TGA);

    //add example to TGA.h
    TGA EXAMPLE_extracredit(EXAMPLE_extracredit_TGA);
    TGA EXAMPLE_part1(EXAMPLE_part1_TGA);
    TGA EXAMPLE_part2(EXAMPLE_part2_TGA);
    TGA EXAMPLE_part3(EXAMPLE_part3_TGA);
    TGA EXAMPLE_part4(EXAMPLE_part4_TGA);
    TGA EXAMPLE_part5(EXAMPLE_part5_TGA);
    TGA EXAMPLE_part6(EXAMPLE_part6_TGA);
    TGA EXAMPLE_part7(EXAMPLE_part7_TGA);
    TGA EXAMPLE_part8b(EXAMPLE_part8_b_TGA);
    TGA EXAMPLE_part8g(EXAMPLE_part8_g_TGA);
    TGA EXAMPLE_part8r(EXAMPLE_part8_r_TGA);
    TGA EXAMPLE_part9(EXAMPLE_part9_TGA);
    TGA EXAMPLE_part10(EXAMPLE_part10_TGA);


    //close file
    layer1_TGA.close();
    pattern1_TGA.close();
    layer2_TGA.close();
    car_TGA.close();
    pattern2_TGA.close();
    text_TGA.close();
    circles_TGA.close();
    layer_red_TGA.close();
    layer_green_TGA.close();
    layer_blue_TGA.close();
    text2_TGA.close();

    //close example file
    EXAMPLE_extracredit_TGA.close();
    EXAMPLE_part1_TGA.close();
    EXAMPLE_part2_TGA.close();
    EXAMPLE_part3_TGA.close();
    EXAMPLE_part4_TGA.close();
    EXAMPLE_part5_TGA.close();
    EXAMPLE_part6_TGA.close();
    EXAMPLE_part7_TGA.close();
    EXAMPLE_part8_b_TGA.close();
    EXAMPLE_part8_g_TGA.close();
    EXAMPLE_part8_r_TGA.close();
    EXAMPLE_part9_TGA.close();
    EXAMPLE_part10_TGA.close();

//task:
    char* path;
    int passedCount = 0;
    TGA temp;
    TGA temp2;

    //extra credit
    path = "output/extracredit.tga";
    ofstream outExtraCredit(path, ios::binary | ios::out);
    temp.combineFourImage(car, circles, pattern1, text);
    temp.writeFile(outExtraCredit);
    outExtraCredit.close();
    temp.testImage(EXAMPLE_extracredit, 1);
    if (temp.getTestResult()){passedCount++;}

    //1
    path = "output/part1.tga";
    ofstream out(path, ios::binary | ios::out);
    temp = layer1;
    temp * pattern1;
    temp.writeFile(out);
    out.close();
    temp.testImage(EXAMPLE_part1, 2);
    if (temp.getTestResult()){passedCount++;}

    //2
    path = "output/part2.tga";
    ofstream out2(path, ios::binary | ios::out);
    temp = layer2;
    temp - car;
    temp.writeFile(out2);
    out2.close();
    temp.testImage(EXAMPLE_part2, 3);
    if (temp.getTestResult()){passedCount++;}

    //3
    path = "output/part3.tga";
    ofstream out3(path, ios::binary | ios::out);
    temp = layer1;
    temp * pattern2;
    temp2 = text;
    temp2.screenBlendingMode(temp);
    temp2.writeFile(out3);
    out3.close();
    temp2.testImage(EXAMPLE_part3, 4);
    if (temp2.getTestResult()){passedCount++;}

    //4
    path = "output/part4.tga";
    ofstream out4(path, ios::binary | ios::out);
    temp = layer2;
    temp * circles;
    temp2 = pattern2;
    temp2 - temp;
    temp2.writeFile(out4);
    out4.close();
    temp2.testImage(EXAMPLE_part4, 5);
    if (temp2.getTestResult()){passedCount++;}

    //5
    path = "output/part5.tga";
    ofstream out5(path, ios::binary | ios::out);
    temp = pattern1;
    temp.OverlayMode(layer1);
    temp.writeFile(out5);
    out5.close();
    temp.testImage(EXAMPLE_part5, 6);
    if (temp.getTestResult()){passedCount++;}

    //6
    path = "output/part6.tga";
    ofstream out6(path, ios::binary | ios::out);
    temp = car;
    temp.addGreen();
    temp.writeFile(out6);
    out6.close();
    temp.testImage(EXAMPLE_part6, 7);
    if (temp.getTestResult()){passedCount++;}

    //7
    path = "output/part7.tga";
    ofstream out7(path, ios::binary | ios::out);
    temp = car;
    temp.mulRedBy4BlueBy0();
    temp.writeFile(out7);
    out7.close();
    temp.testImage(EXAMPLE_part7, 8);
    if (temp.getTestResult()){passedCount++;}

    //8
    //Red
    path = "output/part8_r.tga";
    ofstream out8_r(path, ios::binary | ios::out);
    temp = car;
    temp.separateChannel('R');
    temp.writeFile(out8_r);
    out8_r.close();
    temp.testImage(EXAMPLE_part8r, 9);
    if (temp.getTestResult()){passedCount++;}

    //Green
    path = "output/part8_g.tga";
    ofstream out8_g(path, ios::binary | ios::out);
    temp = car;
    temp.separateChannel('G');
    temp.writeFile(out8_g);
    out8_g.close();
    temp.testImage(EXAMPLE_part8g, 10);
    if (temp.getTestResult()){passedCount++;}

    //Blue
    path = "output/part8_b.tga";
    ofstream out8_b(path, ios::binary | ios::out);
    temp = car;
    temp.separateChannel('B');
    temp.writeFile(out8_b);
    out8_b.close();
    temp.testImage(EXAMPLE_part8b, 11);
    if (temp.getTestResult()){passedCount++;}

    //9
    path = "output/part9.tga";
    ofstream out9(path, ios::binary | ios::out);
    temp = layer_red; // this step is to get header data.
    temp.addChannel(layer_red, 'R');
    temp.addChannel(layer_green, 'G');
    temp.addChannel(layer_blue, 'B');
    temp.writeFile(out9);
    out9.close();
    temp.testImage(EXAMPLE_part9, 12);
    if (temp.getTestResult()){passedCount++;}

    //10
    path = "output/part10.tga";
    ofstream out10(path, ios::binary | ios::out);
    temp = text2;
    temp.FileFlipped(text2);
    temp.writeFile(out10);
    out10.close();
    temp.testImage(EXAMPLE_part10, 13);
    if (temp.getTestResult()){passedCount++;}

    //write test result
    cout << "Test results: " << passedCount << "/" << 13 <<endl;


    return 0;
}
