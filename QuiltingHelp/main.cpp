#include <stdio.h>
#include <boost/any.hpp>
#include <filesystem>
#include <windows.h>
#include <opencv2/opencv.hpp>
using namespace cv;

int edgeThresh = 1;

Mat imageSegment;
Mat image;

void onTrackbar(int, void*)
{
    Mat imageSegmentEdge;
    Canny(imageSegment, imageSegmentEdge, edgeThresh, edgeThresh*3);
    imshow("Display Image", imageSegmentEdge);
    /*std::vector< std::vector<Point> > contours;
    findContours(imageSegmentEdge, contours, RETR_TREE, CHAIN_APPROX_NONE);
    Mat mask = Mat::zeros(imageSegment.rows, imageSegment.cols, CV_8UC1);
    drawContours(mask, contours, -1, Scalar(255), LINE_AA);
    imshow("Display Image", mask);*/
}

#ifdef WIN32
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPreInst, LPSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char* argv[])
#endif
{
    const auto allArgs = std::string_view(GetCommandLineA());
    const auto firstArg = allArgs.substr(1, allArgs.size()-3);
    const auto startedAt = std::filesystem::canonical(firstArg).parent_path();
    const std::string imagePath = (startedAt / std::filesystem::path("nya2.jpg")).string();
    image = imread(imagePath, IMREAD_COLOR);
    if (!image.data)
    {
        printf("No image data \n");
        return -1;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", image);
    waitKey(0);
    int spatialRadius = 35;
    int colorRadius = 60;
    int pyramidLevels = 3;
    pyrMeanShiftFiltering(image, imageSegment, spatialRadius, colorRadius, pyramidLevels);
    imshow("Display Image", imageSegment);
    waitKey(0);
    createTrackbar("Canny threshold", "Display Image", &edgeThresh, 400, onTrackbar);
    onTrackbar(0, nullptr);
    waitKey(0);
    return 0;
}