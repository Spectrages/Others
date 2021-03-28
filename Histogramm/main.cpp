#include <iostream>
#include <vector>
#include <string>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

static void help(char* progName);
string path_file();
void DrawHist(Mat& histImg, int histSize, int bin_w, int hist_h, Mat& r_hist, Mat& g_hist, Mat& b_hist);



int main(int argc, char* argv[])
{

    help(argv[0]);
    Mat src;
    vector<Mat> planes;
    int histSize = 256;
    float range[] = {0, 256};
    const float* histRange = { range };
    bool uniform = true, accumulate = false;
    int hist_w = 900, hist_h = 600;
    int bin_w = 0;
    Mat r_hist;
    Mat g_hist;
    Mat b_hist;
    Mat histImg(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
    char ch = '0';

    do
    {
    src = imread(path_file(), IMREAD_COLOR);
    if(src.empty())
        return EXIT_FAILURE;

    split(src, planes);

    calcHist(&planes[0], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&planes[2], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);

    bin_w = cvRound((double)hist_w/histSize);

    normalize(r_hist, r_hist, 0, histImg.rows, NORM_MINMAX, -1, Mat());
    normalize(g_hist, g_hist, 0, histImg.rows, NORM_MINMAX, -1, Mat());
    normalize(b_hist, b_hist, 0, histImg.rows, NORM_MINMAX, -1, Mat());
    imshow("Source image", src);
    DrawHist(histImg, histSize, bin_w, hist_h, r_hist, g_hist, b_hist);
    cout << "Repeat? (y/n): ";
    waitKey(1000);
    cin >> ch;
    destroyAllWindows();
    }
    while(ch == 'y');
    waitKey();
    return 0;
}


static void help(char* progName)
{
    cout << progName << "\n\n";
    cout << "This program is designed to create a color histogram from\n";
    cout << "a selected image using three RGB channels. If the image is\n";
    cout << "located on the specified path, enter its full name (cat.jpg),\n";
    cout << "otherwise, enter the path yourself.";
}

string path_file()
{
    string PATH;
    bool ch;
    do
    {
        int ans;
        string StartPath = "/Images/";
        cout << "To use the file, place it at path\n --" << StartPath << "-- or specify your own path by selecting '2'\n";
        cout << "1. Continue typing\n2. Enter a new path\n3. Exit\nInput field: ";
        cin >> ans;
        switch(ans)
        {
        case 1:
        {
            string FinishPath;
            cout << "File name: ";
            cin >> FinishPath;
            PATH = StartPath + FinishPath;
            ch = false;
            system("clear");
            break;
        }
        case 2:
        {
            string fullPath;
            cout << "Path: ";
            cin >> fullPath;
            PATH = fullPath;
            ch = false;
            system("clear");
            break;
        }
        case 3:
        {
            EXIT_SUCCESS;
            break;
        }
        default:
        {
            cout << "No such file!";
            break;
        }
        }
    }
    while(ch != false);
    return PATH;
}

void DrawHist(Mat& histImg, int histSize, int bin_w, int hist_h, Mat& r_hist, Mat& g_hist, Mat& b_hist)
{
    for(int i = 0; i < histSize; ++i)
    {
        line( histImg, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ),
              Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
              Scalar( 255, 0, 0), 2, 8, 0);

        line( histImg, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ),
              Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
              Scalar( 0, 255, 0), 2, 8, 0);

        line( histImg, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ),
              Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
              Scalar( 0, 0, 255), 2, 8, 0);
    }
    imshow("Histogramm", histImg);
}
