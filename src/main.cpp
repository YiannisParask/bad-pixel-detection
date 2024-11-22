#include <opencv2/opencv.hpp>
#include <iostream>

/**
 * @brief Detects and corrects dead pixels in an RGB image
 * 
 * @param image The input BGR image
 */
void detectAndCorrectDeadPixelsBgr(cv::Mat &image)
{
    if (image.channels() != 3)
    {
        std::cerr << "The image must be an BGR image for dead pixel detection!" << std::endl;
        return;
    }

    std::vector<cv::Mat> channels;
    cv::split(image, channels);

    // Detect Dead Pixels (if all its BGR channels are equal to 0 or 255, then the pixel is dead)
    cv::Mat mask = (image == cv::Vec3b(0, 0, 0)) | (image == cv::Vec3b(255, 255, 255));

    // Correct Dead Pixels (Apply median blur with a 3x3 kernel)
    std::vector<cv::Mat> correctedChannels(3);
    for (int i = 0; i < 3; i++)
    {
        cv::medianBlur(channels[i], correctedChannels[i], 3);
    }

    cv::Mat correctedImage;
    cv::merge(correctedChannels, correctedImage);

    correctedImage.copyTo(image, mask);
}

void detectAndCorrectDeadPixelsGrayscale(cv::Mat &image)
{
    if (image.channels() != 1) {
        std::cerr << "The image must be in grayscale for dead pixel detection!" << std::endl;
        return;
    }

    // Detect Dead Pixels
    cv::Mat mask = (image == 0) | (image == 255); // Detect pixels that are either 0 (black) or 255 (white)

    // Correct Dead Pixels
    cv::Mat correctedImage;
    cv::medianBlur(image, correctedImage, 3); // Apply median blur with a 3x3 kernel

    correctedImage.copyTo(image, mask);
}

int main()
{
    cv::Mat image = cv::imread("../data/sample.png", cv::IMREAD_UNCHANGED);
    if (image.empty())
    {
        std::cerr << "Error loading image!" << std::endl;
        return -1;
    }

    if (image.channels() == 1)
    {
        std::cout << "Selected image is in Grayscale format" << std::endl;
        detectAndCorrectDeadPixelsGrayscale(image);
    }
    else if (image.channels() == 3)
    {
        std::cout << "Selected image is in BGR format" << std::endl;
        detectAndCorrectDeadPixelsBgr(image);
    }

    cv::imwrite("corrected.jpg", image);
    cv::imshow("Corrected Image", image);
    cv::waitKey(0);

    return 0;
}
