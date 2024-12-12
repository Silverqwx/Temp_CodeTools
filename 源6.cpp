//加工OpenCorr和DICe的model vs non-model的对比图

//#include <iostream>
//#include <opencv2/opencv.hpp>
//
//int main()
//{
//	int sub1_y = 386, sub1_height = 920,
//		sub2_y = 1730, sub2_height = 622,
//		sub3_y = 4864, sub3_height = 2106,
//		sub4_y = 8256, sub4_height = 1561;
//	int margin = 100;
//
//	cv::Mat img = cv::imread("CombineFigure_DICe.jpg", 1);
//	cv::Mat subImg1 = img(cv::Rect(0, sub1_y, 9720, sub1_height + margin));
//	cv::Mat subImg2 = img(cv::Rect(0, sub2_y, 9720, sub2_height + margin));
//	cv::Mat subImg3 = img(cv::Rect(0, sub3_y, 9720, sub3_height + 50));
//	cv::Mat subImg4 = img(cv::Rect(0, sub4_y, 9720, sub4_height));
//
//	//cv::Mat combineImage(sub1_height + sub2_height + sub3_height + sub4_height, 9720, CV_8UC3);
//	cv::Mat combineImage;
//	cv::vconcat(subImg1, subImg2, combineImage);
//	cv::vconcat(combineImage, subImg3, combineImage);
//	cv::vconcat(combineImage, subImg4, combineImage);
//
//	cv::imwrite("CombineFigure_DICe_refined.png", combineImage);
//
//	return 0;
//}