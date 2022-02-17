#include <stdio.h>
#include <boost/any.hpp>
#include <filesystem>
#include <windows.h>
#include <opencv2/opencv.hpp>
using namespace cv;

#ifdef WIN32
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPreInst, LPSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char* argv[])
#endif
{
    const auto allArgs = std::string_view(GetCommandLineA());
    const auto firstArg = allArgs.substr(1, allArgs.size()-3);
    const auto startedAt = std::filesystem::canonical(firstArg).parent_path();
    const std::string imagePath = (startedAt / std::filesystem::path("nya.jpg")).string();
    Mat image;
    image = imread(imagePath, IMREAD_COLOR);
    if (!image.data)
    {
        printf("No image data \n");
        return -1;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", image);
    waitKey(0);
    Mat imageSegment;
    int spatialRadius = 35;
    int colorRadius = 60;
    int pyramidLevels = 3;
    pyrMeanShiftFiltering(image, imageSegment, spatialRadius, colorRadius, pyramidLevels);
    imshow("Display Image", imageSegment);
    waitKey(0);
    Mat imgray;
    cvtColor(imageSegment, imgray, COLOR_BGR2GRAY);
    imshow("Display Image", imgray);
    waitKey(0);
    std::vector< std::vector<Point> > contours;
    findContours(imgray, contours, RETR_TREE, CHAIN_APPROX_NONE);
    Mat mask = Mat::zeros(image.rows, image.cols, CV_8UC1);
    drawContours(mask, contours, -1, Scalar(255), LINE_AA);
    imshow("Display Image", mask);
    waitKey(0);

    return 0;
}