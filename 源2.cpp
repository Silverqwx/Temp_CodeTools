////画左右点
// 
// #include <iostream>
//#include <fstream>
//
//#include <opencv2/opencv.hpp>
//
//using namespace std;
//
//void drawCross(cv::Mat img, cv::Point2d point, cv::Scalar color, int size, int thickness)
//{
//	//绘制横线
//	cv::line(img, cv::Point2d(point.x - size / 2, point.y), cv::Point2d(point.x + size / 2, point.y), color, thickness, cv::LINE_AA, 0);
//	//绘制竖线
//	cv::line(img, cv::Point2d(point.x, point.y - size / 2), cv::Point2d(point.x, point.y + size / 2), color, thickness, cv::LINE_AA, 0);
//
//	return;
//}
//
//void drawDashedCircle(cv::Mat& image, cv::Point2d center, double _radius, int thickness, double dashAngle, double spaceAngle)
//{
//	for (double radius = _radius - thickness + 1; radius <= _radius; radius++)
//	{
//		for (double angle = 0.0; angle < 360.0; angle += 1)
//		{
//			if (fmod(angle, (dashAngle + spaceAngle)) > dashAngle)
//				continue;
//
//			double radian = angle * CV_PI / 180;
//			int pty = std::round(center.x + radius * cos(radian)),
//				ptx = std::round(center.y + radius * sin(radian));
//
//			image.at<cv::Vec3b>(ptx, pty) = cv::Vec3b(200, 104, 186);
//		}
//	}
//}
//
//int main()
//{
//	std::string fileDir = "D://OneDrive - Hiroshima University//Doctor Program//Research//2 2D-3D fusion visualization//Experiment Task//2024.06.21 Cuboid_Z_2//Exposure42600//";
//	//std::string fileDir = "D://OneDrive - Hiroshima University//Doctor Program//Research//3 visualization (not research)//Experiment Task//2024.07.09 woodenSpeakerFront_whitepaint//ExpT1900_Gain1_L40Hz_R100Hz_volume33//results_Model3D_OpenCorr2D_sR128_denseLine//";
//	std::string method = "OpenCorr";
//
//	int ptNum = 200;
//
//	std::vector<cv::Point2d> mUVLefts(ptNum);
//	std::vector<cv::Point2d> mUVRights(ptNum);
//	std::vector<cv::Point2d> UVLefts(ptNum);
//	std::vector<cv::Point2d> UVRights(ptNum);
//	//read 2d points
//	{
//		ifstream ifile(fileDir + "results_Model3D_" + method + "2D_sR64//" + "uvLeft.csv");
//		//ifstream ifile(fileDir + "uvLeft.csv");
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
//		ifstream ifile(fileDir + "results_Model3D_" + method + "2D_sR64//" + "uvRight.csv");
//		//ifstream ifile(fileDir + "uvRight.csv");
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
//		ifstream ifile(fileDir + "results_" + method + "3D_sR64//" + "uvLeft.csv");
//		//ifstream ifile(fileDir + "uvLeft.csv");
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
//		ifstream ifile(fileDir + "results_" + method + "3D_sR64//" + "uvRight.csv");
//		//ifstream ifile(fileDir + "uvRight.csv");
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
//	cv::Mat imgLeft = cv::imread(fileDir + "left//" + "img (1).jpg"),
//		imgRight = cv::imread(fileDir + "right//" + "img (1).jpg");
//	//cv::Mat imgLeft = cv::imread("imgLeft.jpg"),
//	//	imgRight = cv::imread("imgRight.jpg");
//
//	for (size_t ptIdx = 0; ptIdx < ptNum; ptIdx++)
//	{
//		const cv::Point2d& mptLeft = mUVLefts[ptIdx],
//			& mptRight = mUVRights[ptIdx];
//
//		cv::circle(imgLeft, mptLeft, 12, cv::Scalar(246, 181, 100), -1);
//		cv::circle(imgRight, mptRight, 12, cv::Scalar(246, 181, 100), -1);
//	}
//
//	for (size_t ptIdx = 0; ptIdx < ptNum; ptIdx++)
//	{
//		const cv::Point2d& ptLeft = UVLefts[ptIdx],
//			& ptRight = UVRights[ptIdx];
//
//		//cv::circle(imgLeft, ptLeft, 12, cv::Scalar(0, 255, 0), -1);
//		cv::circle(imgRight, ptRight, 12, cv::Scalar(115, 115, 229), -1);
//	}
//
//	for (size_t ptIdx = 0; ptIdx < ptNum; ptIdx++)
//	{
//		const cv::Point2d& mptLeft = mUVLefts[ptIdx],
//			& mptRight = mUVRights[ptIdx];
//
//		double radius = 12;
//		int thickness = 6;
//		double dashAngle = 30;  // Length of each dash
//		double spaceAngle = 30;  // Length of space between dashes
//
//		// Draw dashed circle
//		drawDashedCircle(imgRight, mptRight, radius, thickness, dashAngle, spaceAngle);
//	}
//
//
//	cv::imwrite("imgLeft_withPt2d.png", imgLeft);
//	cv::imwrite("imgRight_withPt2d.png", imgRight);
//
//	return 0;
//}