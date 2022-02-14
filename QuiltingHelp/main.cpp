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
    image = imread(imagePath, 1);
    if (!image.data)
    {
        printf("No image data \n");
        return -1;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", image);
    waitKey(0);

    return 0;
}