//#include <iostream>
//#include <fstream>
//
//#include <opencv2/opencv.hpp>
//
//using namespace std;
//
//int main()
//{
//	int ptNum = 100;
//
//	std::vector<cv::Point2d> mUVLefts(ptNum);
//	std::vector<cv::Point2d> mUVRights(ptNum);
//	std::vector<cv::Point2d> UVLefts(ptNum);
//	std::vector<cv::Point2d> UVRights(ptNum);
//	//read 2d points
//	{
//		ifstream ifile("muvLeft.csv");
//		string linestr;
//		for (int ptIdx = 0; ptIdx < mUVLefts.size(); ptIdx++)
//		{
//			getline(ifile, linestr);
//			stringstream ss(linestr);
//			string str;
//			std::vector<float> xyz(2);
//			for (int xyzIdx = 0; xyzIdx < 2; xyzIdx++)
//			{
//				getline(ss, str, ',');
//				stringstream ss2(str);
//				float temp = 0.0;
//				ss2 >> temp;
//				xyz[xyzIdx] = temp;
//			}
//			mUVLefts[ptIdx].x = xyz[0];
//			mUVLefts[ptIdx].y = xyz[1];
//		}
//	}
//	{
//		ifstream ifile("muvRight.csv");
//		string linestr;
//		for (int ptIdx = 0; ptIdx < mUVRights.size(); ptIdx++)
//		{
//			getline(ifile, linestr);
//			stringstream ss(linestr);
//			string str;
//			std::vector<float> xyz(2);
//			for (int xyzIdx = 0; xyzIdx < 2; xyzIdx++)
//			{
//				getline(ss, str, ',');
//				stringstream ss2(str);
//				float temp = 0.0;
//				ss2 >> temp;
//				xyz[xyzIdx] = temp;
//			}
//			mUVRights[ptIdx].x = xyz[0];
//			mUVRights[ptIdx].y = xyz[1];
//		}
//	}
//	{
//		ifstream ifile("uvLeft.csv");
//		string linestr;
//		for (int ptIdx = 0; ptIdx < UVLefts.size(); ptIdx++)
//		{
//			getline(ifile, linestr);
//			stringstream ss(linestr);
//			string str;
//			std::vector<float> xyz(2);
//			for (int xyzIdx = 0; xyzIdx < 2; xyzIdx++)
//			{
//				getline(ss, str, ',');
//				stringstream ss2(str);
//				float temp = 0.0;
//				ss2 >> temp;
//				xyz[xyzIdx] = temp;
//			}
//			UVLefts[ptIdx].x = xyz[0];
//			UVLefts[ptIdx].y = xyz[1];
//		}
//	}
//	{
//		ifstream ifile("uvRight.csv");
//		string linestr;
//		for (int ptIdx = 0; ptIdx < UVRights.size(); ptIdx++)
//		{
//			getline(ifile, linestr);
//			stringstream ss(linestr);
//			string str;
//			std::vector<float> xyz(2);
//			for (int xyzIdx = 0; xyzIdx < 2; xyzIdx++)
//			{
//				getline(ss, str, ',');
//				stringstream ss2(str);
//				float temp = 0.0;
//				ss2 >> temp;
//				xyz[xyzIdx] = temp;
//			}
//			UVRights[ptIdx].x = xyz[0];
//			UVRights[ptIdx].y = xyz[1];
//		}
//	}
//
//	cv::Mat imgLeft = cv::imread("fstFrameLeft.png"),
//		imgRight = cv::imread("fstFrameRight.png");
//
//	for (size_t ptIdx = 0; ptIdx < ptNum; ptIdx++)
//	{
//		const cv::Point2d& mptLeft = mUVLefts[ptIdx],
//			& mptRight = mUVRights[ptIdx];
//		const cv::Point2d& ptLeft = UVLefts[ptIdx],
//			& ptRight = UVRights[ptIdx];
//
//		//cv::circle(imgLeft, ptLeft, 8, cv::Scalar(0, 255, 0), -1);
//		cv::circle(imgRight, ptRight, 8, cv::Scalar(0, 255, 0), -1);
//		cv::circle(imgLeft, mptLeft, 8, cv::Scalar(255, 0, 0), -1);
//		cv::circle(imgRight, mptRight, 8, cv::Scalar(255, 0, 0), -1);
//	}
//
//
//	return 0;
//}