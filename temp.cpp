//#include <opencv2/opencv.hpp>
//#include <cmath>
//
//void drawDashedCircle(cv::Mat& image, cv::Point center, double _radius, int thickness, double dashAngle, double spaceAngle) 
//{
//    for (double radius = _radius - thickness + 1; radius <= _radius; radius++)
//    {
//        for (double angle = 0.0; angle < 360.0; angle += 1)
//        {
//            if (fmod(angle, (dashAngle + spaceAngle)) > dashAngle)
//                continue;
//
//            double radian = angle * CV_PI / 180;
//            int ptx = std::round(center.x + radius * cos(radian)),
//                pty = std::round(center.y + radius * sin(radian));
//
//            image.at<cv::Vec3b>(ptx, pty) = cv::Vec3b(255, 255, 255);
//        }
//    }
//}
//
//int main() {
//    // Create an empty image
//    cv::Mat image = cv::Mat::zeros(100, 100, CV_8UC3);
//
//    // Define circle parameters
//    cv::Point center(50, 50);
//    double radius = 8;
//    cv::Scalar color(255, 255, 255);  // White color
//    int thickness = 2;
//    int lineType = cv::LINE_8;
//    double dashAngle = 25;  // Length of each dash
//    double spaceAngle = 35;  // Length of space between dashes
//
//    // Draw dashed circle
//    drawDashedCircle(image, center, radius, thickness, dashAngle, spaceAngle);
//
//    // Display the image
//    /*cv::imshow("Dashed Circle", image);
//    cv::waitKey(0);*/
//
//    return 0;
//}
