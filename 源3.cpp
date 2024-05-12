//#include <iostream>
//#include <fstream>
//
//#include <opencv2/opencv.hpp>
//
//using namespace std;
//
//int main()
//{
//	int imgStart = 1,
//		imgEnd = 11;
//
//	std::string fileDir = "d://OneDrive - Hiroshima University//Doctor Program//Research//2 2D-3D fusion visualization//Experiment Task//2024.05.02 AccuracyExperiment_copy//right//";
//	for (size_t imgIdx = imgStart; imgIdx <= imgEnd; imgIdx++)
//	{
//		std::stringstream ss;
//		ss << imgIdx;
//		std::string filePath = fileDir + "img (" + ss.str() + ").png";
//
//		cv::Mat img = cv::imread(filePath);
//
//		for (size_t col = 0; col < img.cols; col++)
//		{
//			for (size_t row = 0; row < img.rows; row++)
//			{
//				if (col >= 707 && col <= 1448 &&
//					row >= 325 && row <= 1238)
//					continue;
//
//				img.at<cv::Vec3b>(row, col) = cv::Vec3b(0, 0, 0);
//			}
//		}
//
//		cv::imwrite(filePath, img);
//
//		//std::cout << std::endl;
//	}
//
//	
//
//
//	return 0;
//}