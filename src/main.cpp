#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include "Image.h"
using namespace std;

//gets size
unsigned int GetSize(Image::Header headerObject) {
    int size;
    size = headerObject.height * headerObject.width;
    return size;
}

//read Image file
Image ReadImage(string fileName) {
    Image image1;
    Image::Header headerObject1;
    vector<Image::Pixel> pixels;
    Image::Pixel pixel;

    ifstream inFile1(fileName, ios_base::binary);
    if (inFile1.is_open()) {
        inFile1.read(&image1.header.idLength, sizeof(image1.header.idLength));
        inFile1.read(&image1.header.colorMapType, sizeof(image1.header.colorMapType));
        inFile1.read(&image1.header.dataTypeCode, sizeof(image1.header.dataTypeCode));
        inFile1.read((char *) &image1.header.colorMapOrigin, sizeof(image1.header.colorMapOrigin));
        inFile1.read((char *) &image1.header.colorMapLength, sizeof(image1.header.colorMapLength));
        inFile1.read(&image1.header.colorMapDepth, sizeof(image1.header.colorMapDepth));
        inFile1.read((char *) &image1.header.xOrigin, sizeof(image1.header.xOrigin));
        inFile1.read((char *) &image1.header.yOrigin, sizeof(image1.header.yOrigin));
        inFile1.read((char *) &image1.header.width, sizeof(image1.header.width));
        inFile1.read((char *) &image1.header.height, sizeof(image1.header.height));
        inFile1.read(&image1.header.bitsPerPixel, sizeof(image1.header.bitsPerPixel));
        inFile1.read(&image1.header.imageDescriptor, sizeof(image1.header.imageDescriptor));
    }
    unsigned int size = GetSize(image1.header);

    for (int i = 0; i < size; ++i) {
        Image::Pixel pixel;
        inFile1.read((char *) &pixel.B, sizeof(pixel.B));

        inFile1.read((char *) &pixel.G, sizeof(pixel.G));

        inFile1.read((char *) &pixel.R, sizeof(pixel.R));

        image1.pixels.push_back(pixel);
    }
    return image1;
}

//Multiply
vector<Image::Pixel> Multiply(Image* image1, Image* image2, unsigned int size) {
    vector<Image::Pixel> newPixels1;
    Image::Pixel newPixel1;

    for (int i = 0; i < size; ++i) {
        newPixel1.B = int (((float)(image1->pixels.at(i).B * image2->pixels.at(i).B) / (255)) + 0.5f);
        newPixel1.G = int (((float)(image1->pixels.at(i).G * image2->pixels.at(i).G) / (255)) + 0.5f);
        newPixel1.R = int (((float)(image1->pixels.at(i).R * image2->pixels.at(i).R) / (255)) + 0.5f);

        newPixels1.push_back(newPixel1);
    }
    return newPixels1;
}

//Substract
vector<Image::Pixel> Substract(Image* image1, vector<Image :: Pixel>* image2, unsigned int size) {
    vector<Image::Pixel> newPixels;
    Image::Pixel newPixel;
    for (int i = 0; i < size; ++i) {
        int B = 0;
        int G = 0;
        int R = 0;
        B = (image2->at(i).B - image1->pixels.at(i).B);
        G = (image2->at(i).G - image1->pixels.at(i).G);
        R = (image2->at(i).R - image1->pixels.at(i).R);

        if(B > 255) {
            B = 255;
        }
        if (B < 0) {
            B = 0;
        }
        newPixel.B = B;

        if(G > 255) {
            G = 255;
        }
        if (G < 0) {
            G = 0;
        }
        newPixel.G = G;

        if(R > 255) {
            R = 255;
        }
        if (R < 0) {
            R = 0;
        }
        newPixel.R = R;

        newPixels.push_back(newPixel);
    }
    return newPixels;
}

//Substract images
vector<Image::Pixel> SubstractI(Image* image1, Image* image2, unsigned int size) {
    vector<Image::Pixel> newPixels;
    Image::Pixel newPixel;
    for (int i = 0; i < size; ++i) {
        int B = 0;
        int G = 0;
        int R = 0;
        B = (image2->pixels.at(i).B - image1->pixels.at(i).B);
        G = (image2->pixels.at(i).G - image1->pixels.at(i).G);
        R = (image2->pixels.at(i).R - image1->pixels.at(i).R);

        if(B > 255) {
            B = 255;
        }
        if (B < 0) {
            B = 0;
        }
        newPixel.B = B;

        if(G > 255) {
            G = 255;
        }
        if (G < 0) {
            G = 0;
        }
        newPixel.G = G;

        if(R > 255) {
            R = 255;
        }
        if (R < 0) {
            R = 0;
        }
        newPixel.R = R;

        newPixels.push_back(newPixel);
    }
    return newPixels;
}

//Screen
vector<Image::Pixel> Screen(Image* image1, vector<Image::Pixel>* image2, unsigned int size) {
    vector<Image::Pixel> newPixels;
    Image::Pixel newPixel;
    float P1;
    float P2;
    float P3;
    float P4;
    float P;

    for (int i = 0; i < size; ++i) {
        P1 = image1->pixels.at(i).B / 255.0f;
        P2 = image2->at(i).B / 255.0f;
        P3 = ((1 - P2) * (1 - P1));
        P4 = 1 - (P3);
        P = (P4 * 255) + 0.5f;
        newPixel.B = (int) P;

        P1 = image1->pixels.at(i).G / 255.0f;
        P2 = image2->at(i).G / 255.0f;
        P3 = ((1 - P2) * (1 - P1));
        P4 = 1 - (P3);
        P = (P4 * 255) + 0.5f;
        newPixel.G = (int) P;

        P1 = image1->pixels.at(i).R / 255.0f;
        P2 = image2->at(i).R / 255.0f;
        P3 = ((1 - P2) * (1 - P1));
        P4 = 1 - (P3);
        P = (P4 * 255) + 0.5f;
        newPixel.R = (int) P;

    newPixels.push_back(newPixel);
    }

    return newPixels;
}

//Overlay
vector<Image::Pixel> Overlay(Image* image1, Image* image2, unsigned int size) {
    vector<Image::Pixel> newPixels;
    Image::Pixel newPixel;

    float P1;
    float P2;
    float P3;
    float P4;
    float P5;
    float P6;
    float P7;
    float P;


    for (int i = 0; i < size; ++i) {
        int temp = 1;
        if (temp == 1) {
            P2 = (image2->pixels.at(i).B / 255.0f);
            if (P2 <= 0.5f) {
                P5 = (float)(image1->pixels.at(i).B * image2->pixels.at(i).B);
                P6 = (2 * P5);
                P7 = (P6 / 255) + 0.5f;
                newPixel.B = P7;
            }
            else if (P2 > 0.5f) {
                P6 = image1->pixels.at(i).B;
                P7 = image2->pixels.at(i).B;
                P1 = P6 / 255.0f;
                P2 = P7 / 255.0f;
                P3 = 2 * ((1 - P2) * (1 - P1));
                P4 = 1 - (P3);
                P = (P4 * 255) + 0.5f;
                newPixel.B = P;
            }
            temp = 2;
        }
        if (temp == 2) {
            P2 = (image2->pixels.at(i).G / 255.0f);
            if (P2 <= 0.5f) {
                P5 = (float)(image1->pixels.at(i).G * image2->pixels.at(i).G);
                P6 = (2 * P5);
                P7 = (P6 / 255) + 0.5f;
                newPixel.G = P7;
            }
            else if (P2 > 0.5f) {
                P6 = image1->pixels.at(i).G;
                P7 = image2->pixels.at(i).G;
                P1 = P6 / 255.0f;
                P2 = P7 / 255.0f;
                P3 = 2 * ((1 - P2) * (1 - P1));
                P4 = 1 - (P3);
                P = (P4 * 255) + 0.5f;
                newPixel.G = P;
            }
            temp = 3;
        }
        if (temp == 3) {
            P2 = (image2->pixels.at(i).R / 255.0f);
            if (P2 <= 0.5f) {
                P5 = (float)(image1->pixels.at(i).R * image2->pixels.at(i).R);
                P6 = (2 * P5);
                P7 = (P6 / 255) + 0.5f;
                newPixel.R = P7;
            }
            else if (P2 > 0.5f) {
                P6 = image1->pixels.at(i).R;
                P7 = image2->pixels.at(i).R;
                P1 = P6 / 255.0f;
                P2 = P7 / 255.0f;
                P3 = 2 * ((1 - P2) * (1 - P1));
                P4 = 1 - (P3);
                P = (P4 * 255) + 0.5f;
                newPixel.R = P;
            }
            temp = 2;
        }
        newPixels.push_back(newPixel);
    }
    return newPixels;
}

//Add 200 to green
vector<Image::Pixel> AddGreen(Image* image1, unsigned int size) {
    vector<Image::Pixel> newPixels;
    Image::Pixel newPixel;
    int G;

    for (int i = 0; i < size; ++i) {
        newPixel.B = image1->pixels.at(i).B;
        G = image1->pixels.at(i).G + 200;
        if (G > 255) {
            G = 255;
        }
        else if (G < 0) {
            G = 0;
        }
        newPixel.G = G;

        newPixel.R = image1->pixels.at(i).R;

        newPixels.push_back(newPixel);
    }
    return newPixels;
}

//Scale Multiply red by 4 and blue by 0
vector<Image::Pixel> MultiplyRedBlue(Image* image1, unsigned int size) {
    vector<Image::Pixel> newPixels;
    Image::Pixel newPixel;
    int R;

    for (int i = 0; i < size; ++i) {
        newPixel.B = int (image1->pixels.at(i).B * 0);
        newPixel.G = image1->pixels.at(i).G;
        R = int (image1->pixels.at(i).R * 4);
        if (R > 255) {
            R = 255;
        }
        else if (R < 0) {
            R = 0;
        }
        newPixel.R = R;

        newPixels.push_back(newPixel);
    }
    return newPixels;
}

//blue channel
vector<Image::Pixel> Blue(Image* image1, unsigned int size) {
    vector<Image::Pixel> newPixels;
    Image::Pixel newPixel;

    for (int i = 0; i < size; ++i) {
        newPixel.B = image1->pixels.at(i).B;
        newPixel.G = image1->pixels.at(i).B;
        newPixel.R = image1->pixels.at(i).B;

        newPixels.push_back(newPixel);
    }
    return newPixels;
}

//green channel
vector<Image::Pixel> Green(Image* image1, unsigned int size) {
    vector<Image::Pixel> newPixels;
    Image::Pixel newPixel;

    for (int i = 0; i < size; ++i) {
        newPixel.B = image1->pixels.at(i).G;
        newPixel.G = image1->pixels.at(i).G;
        newPixel.R = image1->pixels.at(i).G;

        newPixels.push_back(newPixel);
    }
    return newPixels;
}

//red channel
vector<Image::Pixel> Red(Image* image1, unsigned int size) {
    vector<Image::Pixel> newPixels;
    Image::Pixel newPixel;

    for (int i = 0; i < size; ++i) {
        newPixel.B = image1->pixels.at(i).R;
        newPixel.G = image1->pixels.at(i).R;
        newPixel.R = image1->pixels.at(i).R;

        newPixels.push_back(newPixel);
    }
    return newPixels;
}

//Combine 3 image files
vector<Image::Pixel> Combine(Image* image1B, Image* image2G, Image* image3R, unsigned int size) {
    vector<Image::Pixel> newPixels;
    Image::Pixel newPixel;

    for (int i = 0; i < size; ++i) {
        newPixel.B = image1B->pixels.at(i).B;
        newPixel.G = image2G->pixels.at(i).G;
        newPixel.R = image3R->pixels.at(i).R;

        newPixels.push_back(newPixel);
    }
    return newPixels;
}

//rotate image 180
vector<Image::Pixel> Rotate180(Image* image1, unsigned int size) {
    vector<Image::Pixel> newPixels;
    Image::Pixel newPixel;

    for (int i = size - 1; i >=0; i--) {
        newPixel.R = image1->pixels.at(i).R;
        newPixel.G = image1->pixels.at(i).G;
        newPixel.B = image1->pixels.at(i).B;

        newPixels.push_back(newPixel);
    }
    return newPixels;
}

//Write new Image file
void WriteImage(string fileName, Image* image1, unsigned int size, vector<Image::Pixel> *newPixels1) {
    ofstream newInFile1(fileName, ios_base::binary);
    if (newInFile1.is_open()) {
        newInFile1.write(&image1->header.idLength, sizeof(image1->header.idLength));
        newInFile1.write(&image1->header.colorMapType, sizeof(image1->header.colorMapType));
        newInFile1.write(&image1->header.dataTypeCode, sizeof(image1->header.dataTypeCode));
        newInFile1.write((char *) &image1->header.colorMapOrigin, sizeof(image1->header.colorMapOrigin));
        newInFile1.write((char *) &image1->header.colorMapLength, sizeof(image1->header.colorMapLength));
        newInFile1.write(&image1->header.colorMapDepth, sizeof(image1->header.colorMapDepth));
        newInFile1.write((char *) &image1->header.xOrigin, sizeof(image1->header.xOrigin));
        newInFile1.write((char *) &image1->header.yOrigin, sizeof(image1->header.yOrigin));
        newInFile1.write((char *) &image1->header.width, sizeof(image1->header.width));
        newInFile1.write((char *) &image1->header.height, sizeof(image1->header.height));
        newInFile1.write(&image1->header.bitsPerPixel, sizeof(image1->header.bitsPerPixel));
        newInFile1.write(&image1->header.imageDescriptor, sizeof(image1->header.imageDescriptor));

        for (unsigned int i = 0; i < size; i++) {
            newInFile1.write((char *) &newPixels1->at(i).B, sizeof(newPixels1->at(i).B));
            newInFile1.write((char *) &newPixels1->at(i).G, sizeof(newPixels1->at(i).G));
            newInFile1.write((char *) &newPixels1->at(i).R, sizeof(newPixels1->at(i).R));
        }
    }
}

/*/Test files
void Test(string fileExample, string file, unsigned int size) {
    //reade example file
    Image example;
    example = ReadImage(fileExample);

    //new file
    Image newImage;
    newImage = ReadImage(file);

    //compares files
    bool same = true;
    int temp = 1;
    while (temp == 1) {
        if (example.header.idLength == newImage.header.idLength) {
            same = true;
        }
        else {
            same = false;
            break;
        }
        if (example.header.colorMapType == newImage.header.colorMapType) {
            same = true;
        }
        else {
            same = false;
            break;
        }
        if (example.header.dataTypeCode == newImage.header.dataTypeCode) {
            same = true;
        }
        else {
            same = false;
            break;
        }
        if (example.header.colorMapOrigin == newImage.header.colorMapOrigin) {
            same = true;
        }
        else {
            same = false;
            break;
        }
        if (example.header.colorMapLength == newImage.header.colorMapLength) {
            same = true;
        }
        else {
            same = false;
            break;
        }
        if (example.header.colorMapDepth == newImage.header.colorMapDepth) {
            same = true;
        }
        else {
            same = false;
            break;
        }
        if (example.header.xOrigin == newImage.header.xOrigin) {
            same = true;
        }
        else {
            same = false;
            break;
        }
        if (example.header.yOrigin == newImage.header.yOrigin) {
            same = true;
        }
        else {
            same = false;
            break;
        }
        if (example.header.width == newImage.header.width) {
            same = true;
        }
        else {
            same = false;
            break;
        }
        if (example.header.height == newImage.header.height) {
            same = true;
        }
        else {
            same = false;
            break;
        }
        if (example.header.bitsPerPixel == newImage.header.bitsPerPixel) {
            same = true;
        }
        else {
            same = false;
            break;
        }
        if (example.header.imageDescriptor == newImage.header.imageDescriptor) {
            same = true;
        }
        else {
            same = false;
            break;
        }
        for (int i = 0; i < size; ++i) {
            if (example.pixels.at(i).B == newImage.pixels.at(i).B) {
                same = true;
            }
            else {
                cout << (int) example.pixels.at(380).B << endl;
                cout << (int) example.pixels.at(380).G << endl;
                cout << (int) example.pixels.at(380).R << endl;
                cout << (int) newImage.pixels.at(380).B << endl;
                cout << (int) newImage.pixels.at(380).G << endl;
                cout << (int) newImage.pixels.at(380).R << endl;
                same = false;
                break;
            }
            if (example.pixels.at(i).G == newImage.pixels.at(i).G) {
                same = true;
            }
            else {
                cout << (int) example.pixels.at(380).B << endl;
                cout << (int) example.pixels.at(380).G << endl;
                cout << (int) example.pixels.at(380).R << endl;
                cout << (int) newImage.pixels.at(380).B << endl;
                cout << (int) newImage.pixels.at(380).G << endl;
                cout << (int) newImage.pixels.at(380).R << endl;
                same = false;
                break;
            }
            if (example.pixels.at(i).R == newImage.pixels.at(i).R) {
                same = true;
            }
            else {
                cout << (int) example.pixels.at(380).B << endl;
                cout << (int) example.pixels.at(380).G << endl;
                cout << (int) example.pixels.at(380).R << endl;
                cout << (int) newImage.pixels.at(380).B << endl;
                cout << (int) newImage.pixels.at(380).G << endl;
                cout << (int) newImage.pixels.at(380).R << endl;
                same = false;
                break;
            }
        }
        temp = 0;
    }
     if (same == true) {
         cout << "passed" << endl;
     }
     else {
         cout << "failed" << endl;
     }
}
*/

//*********************************************** Main *************************************************//

int main() {

    //***************************************** Part 1 *********************************************//

    //read Image1
    string fileName = "input/layer1.tga";
    Image image1;
    image1 = ReadImage(fileName);

    //read Image2
    fileName = "input/pattern1.tga";
    Image image1_2;
    image1_2 = ReadImage(fileName);

    //get size of image 1
    unsigned int size = GetSize(image1.header);

    //multiply pixels for new image
    vector<Image::Pixel> newPixels;
    newPixels = Multiply(&image1, &image1_2, size);


    string file1 = "output/part1.tga";
    string fileExample = "examples/EXAMPLE_part1.tga";

    //create new image file 1
    WriteImage(file1, &image1, size, &newPixels);

    /*/test to see if file is equal to example file
    cout << "Part1 ....";
    Test(fileExample, file1, size);
    */


        //***************************************** Part 2 *******************************************//

    //reads Image1
    fileName = "input/layer2.tga";
    Image image2_1;
    image2_1 = ReadImage(fileName);

    //read Image2
    fileName = "input/car.tga";
    Image image2_2;
    image2_2 = ReadImage(fileName);

    //get size of image 1
    unsigned int size2 = GetSize(image2_1.header);

    //substract pixels for new image
    vector<Image::Pixel> newPixels2;
    newPixels2 = SubstractI(&image2_1, &image2_2, size2);

    string file2 = "output/part2.tga";
    string fileExample2 = "examples/EXAMPLE_part2.tga";

    //create new image 2
    WriteImage(file2, &image2_1, size2, &newPixels2);

    /*/test image 2
    cout << "Part2 ....";
    Test(fileExample2, file2, size2);
    */


    //*********************************************** Part 3 **************************************//

    //read Image1
    fileName = "input/layer1.tga";
    Image image3_1;
    image3_1 = ReadImage(fileName);

    //read Image2
    fileName = "input/pattern2.tga";
    Image image3_2;
    image3_2 = ReadImage(fileName);

    //get size of image 1
    unsigned int size3 = GetSize(image3_1.header);

    //multiply pixels for new image
    vector<Image::Pixel> newPixels3_1;
    newPixels3_1 = Multiply(&image3_1, &image3_2, size3);

    string fileExample3 = "examples/EXAMPLE_part3.tga";

    //read Image3
    fileName = "input/text.tga";
    Image image3_3;
    image3_3 = ReadImage(fileName);

    //Screen pixels for new image
    vector<Image::Pixel> newPixels3_2;
    newPixels3_2 = Screen(&image3_3, &newPixels3_1, size3);

    string file3 = "output/part3.tga";
    WriteImage(file3, &image3_3,size3, &newPixels3_2);

    /*/test to see if file is equal to example file
    cout << "Part3 ....";
    Test(fileExample3, file3, size3); //change
    */


    //************************************** Part 4 ***************************************//

    //read Image1
    fileName = "input/layer2.tga";
    Image image4_1;
    image4_1 = ReadImage(fileName);

    //read Image2
    fileName = "input/circles.tga";
    Image image4_2;
    image4_2 = ReadImage(fileName);

    //get size of image 1
    unsigned int size4 = GetSize(image4_1.header);

    //multiply pixels for new image
    vector<Image::Pixel> newPixels4_1;
    newPixels4_1 = Multiply(&image4_1, &image4_2, size4);

    string fileExample4 = "examples/EXAMPLE_part4.tga";

    //read Image3
    fileName = "input/pattern2.tga";
    Image image4_3;
    image4_3 = ReadImage(fileName);

    //Screen pixels for new image
    vector<Image::Pixel> newPixels4_2;
    newPixels4_2 = Substract(&image4_3, &newPixels4_1, size4);

    string file4 = "output/part4.tga";
    WriteImage(file4, &image4_3,size4, &newPixels4_2);

    /*/test to see if file is equal to example file
    cout << "Part4 ....";
    Test(fileExample4, file4, size4); //change
    */

    //***************************** Part 5 ******************************************//

    //read Image1
    fileName = "input/layer1.tga";
    Image image5_1;
    image5_1 = ReadImage(fileName);

    //read Image2
    fileName = "input/pattern1.tga";
    Image image5_2;
    image5_2 = ReadImage(fileName);

    //get size of image 1
    unsigned int size5 = GetSize(image5_1.header);

    //multiply pixels for new image
    vector<Image::Pixel> newPixels5_1;
    newPixels5_1 = Overlay(&image5_1, &image5_2, size5);

    string file5 = "output/part5.tga";
    string fileExample5 = "examples/EXAMPLE_part5.tga";

    //create new image file 1
    WriteImage(file5, &image5_1, size5, &newPixels5_1);

    /*cout << "Part5 ....";
    Test(fileExample5, file5, size5);
    */

    //********************************* Part 6 *********************************//

    //read Image1
    fileName = "input/car.tga";
    Image image6_1;
    image6_1 = ReadImage(fileName);

    //get size of image 1
    unsigned int size6 = GetSize(image6_1.header);

    //add 200 to green pixels for new image
    vector<Image::Pixel> newPixels6_1;
    newPixels6_1 = AddGreen(&image6_1, size6);

    string file6 = "output/part6.tga";
    string fileExample6 = "examples/EXAMPLE_part6.tga";

    //create new image file 1
    WriteImage(file6, &image6_1, size6, &newPixels6_1);

     /*cout << "Part6 ....";
     Test(fileExample6, file6, size6);
     */

     //*********************************** Part 7 *****************************************//

    //read Image1
    fileName = "input/car.tga";
    Image image7_1;
    image7_1 = ReadImage(fileName);

    //get size of image 1
    unsigned int size7 = GetSize(image7_1.header);

    //add 200 to green pixels for new image
    vector<Image::Pixel> newPixels7_1;
    newPixels7_1 = MultiplyRedBlue(&image7_1, size7);

    string file7 = "output/part7.tga";
    string fileExample7 = "examples/EXAMPLE_part7.tga";

    //create new image file 1
    WriteImage(file7, &image7_1, size7, &newPixels7_1);

    /*cout << "Part7 ....";
    Test(fileExample7, file7, size7);
    */


    //************************************ Part 8 **************************************//

    //read Image1 (Blue)
    fileName = "input/car.tga";
    Image image8_1_B;
    image8_1_B = ReadImage(fileName);

    //get size of image 1
    unsigned int size8 = GetSize(image8_1_B.header);

    //add blue pixels for new image
    vector<Image::Pixel> newPixels8_1_B;
    newPixels8_1_B = Blue(&image8_1_B, size8);

    string file8_B = "output/part8_b.tga";
    string fileExample8_B = "examples/EXAMPLE_part8_b.tga";

    //create new image file 1
    WriteImage(file8_B, &image8_1_B, size8, &newPixels8_1_B);

    /*cout << "Part8B ....";
    Test(fileExample8_B, file8_B, size8);
    */


    //read Image1 (Green)
    fileName = "input/car.tga";
    Image image8_1_G;
    image8_1_G = ReadImage(fileName);


    //add green pixels for new image
    vector<Image::Pixel> newPixels8_1_G;
    newPixels8_1_G = Green(&image8_1_B, size8);

    string file8_G = "output/part8_g.tga";
    string fileExample8_G = "examples/EXAMPLE_part8_g.tga";

    //create new image file 1
    WriteImage(file8_G, &image8_1_G, size8, &newPixels8_1_G);

    /*cout << "Part8G ....";
    Test(fileExample8_G, file8_G, size8);
    */

    //read Image1 (Red)
    fileName = "input/car.tga";
    Image image8_1_R;
    image8_1_R = ReadImage(fileName);

    //add red pixels for new image
    vector<Image::Pixel> newPixels8_1_R;
    newPixels8_1_R = Red(&image8_1_R, size8);

    string file8_R = "output/part8_r.tga";
    string fileExample8_R = "examples/EXAMPLE_part8_r.tga";

    //create new image file 1
    WriteImage(file8_R, &image8_1_R, size8, &newPixels8_1_R);

    /*cout << "Part8R ....";
    Test(fileExample8_R, file8_R, size8);
    */

    //************************************** Part 9 *************************************//

    //read Image1
    fileName = "input/layer_red.tga";
    Image image9_1;
    image9_1 = ReadImage(fileName);

    //get size of image 1
    unsigned int size9 = GetSize(image9_1.header);

    //read Image2
    fileName = "input/layer_green.tga";
    Image image9_2;
    image9_2 = ReadImage(fileName);

    //read Image3
    fileName = "input/layer_blue.tga";
    Image image9_3;
    image9_3 = ReadImage(fileName);

    vector<Image::Pixel> newPixels9_1;
    newPixels9_1 = Combine(&image9_3, &image9_2, &image9_1, size9);

    string file9 = "output/part9.tga";
    string fileExample9 = "examples/EXAMPLE_part9.tga";

    //create new image file 9
    WriteImage(file9, &image9_1, size9, &newPixels9_1);

    /*cout << "Part9 ....";
    Test(fileExample9, file9, size9);
    */


    //************************************** Part 10 ***********************************//

    //read Image1
    fileName = "input/text2.tga";
    Image image10_1;
    image10_1 = ReadImage(fileName);

    //get size of image 1
    unsigned int size10 = GetSize(image10_1.header);

    vector<Image::Pixel> newPixels10_1;
    newPixels10_1 = Rotate180(&image10_1, size10);

    string file10 = "output/part10.tga";
    string fileExample10 = "examples/EXAMPLE_part10.tga";

    //create new image file 9
    WriteImage(file10, &image10_1, size10, &newPixels10_1);

    /*cout << "Part10 ....";
    Test(fileExample10, file10, size10);
    */

}



