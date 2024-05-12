//#include <iostream>
//#include <fstream>
//
//#include <pcl/point_cloud.h>
//#include <pcl/point_types.h>
//#include <pcl/io/ply_io.h>
//
//#include <opencv2/opencv.hpp>
//
//using namespace std;
//
//int main()
//{
//	int ptNum = 765029;
//
//	pcl::PointCloud<pcl::PointXYZRGB>::Ptr pcRef(new pcl::PointCloud<pcl::PointXYZRGB>);
//	pcl::io::loadPLYFile("SpeakerTexture.ply", *pcRef);
//
//	ptNum = pcRef->points.size();
//	std::vector<cv::Point3d> Disps(ptNum);
//	std::vector<double> DispL2s(ptNum);
//	std::vector<cv::Point3d> PtsMapColor(ptNum);
//	//read displacements
//	{
//		ifstream ifile("resultF2.csv");
//		string linestr;
//		for (int ptIdx = 0; ptIdx < Disps.size(); ptIdx++)
//		{
//			getline(ifile, linestr);
//			stringstream ss(linestr);
//			string str;
//			std::vector<float> xyz(3);
//			for (int xyzIdx = 0; xyzIdx < 3; xyzIdx++)
//			{
//				getline(ss, str, ',');
//				stringstream ss2(str);
//				float temp = 0.0;
//				ss2 >> temp;
//				xyz[xyzIdx] = temp;
//			}
//			Disps[ptIdx].x = xyz[0];
//			Disps[ptIdx].y = xyz[1];
//			Disps[ptIdx].z = xyz[2];
//		}
//	}
//
//	double maxDispL2 = 0.0,
//		minDispL2 = 9999.9;
//	for (size_t ptIdx = 0; ptIdx < Disps.size(); ptIdx++)
//	{
//		double& dispL2 = DispL2s[ptIdx];
//		const cv::Point3d& PtDisp = Disps[ptIdx];
//
//		dispL2 = cv::norm(PtDisp);
//
//		if (dispL2 == 0.0)
//			continue;
//
//		if (dispL2 > maxDispL2)
//			maxDispL2 = dispL2;
//		if (dispL2 < minDispL2)
//			minDispL2 = dispL2;
//	}
//	//minDispL2 = minDispL2 * 0.9 + maxDispL2 * 0.1;
//	//maxDispL2 = minDispL2 * 0.2 + maxDispL2 * 0.8;
//
//	cv::Mat temp(1, 256, CV_8UC1);
//	uchar* pTemp = temp.data;
//	for (size_t i = 0; i < 256; i++)
//	{
//		pTemp[i] = i;
//	}
//	cv::Mat colormap;
//	cv::applyColorMap(temp, colormap, cv::COLORMAP_JET);
//	cv::Vec3b* pColormap = (cv::Vec3b*)colormap.data;
//
//	for (size_t ptIdx = 0; ptIdx < DispL2s.size(); ptIdx++)
//	{
//		const double& dispL2 = DispL2s[ptIdx];
//		cv::Point3d& PtMapColor = PtsMapColor[ptIdx];
//
//		int cmIdx = (dispL2 - minDispL2) / (maxDispL2 - minDispL2) * 255;
//		if (cmIdx < 0)
//			cmIdx = 0;
//		if (cmIdx > 255)
//			cmIdx = 255;
//
//		//PtMapColor.x = cmIdx;
//		//PtMapColor.y = cmIdx;
//		//PtMapColor.z = cmIdx;
//		PtMapColor.x = pColormap[cmIdx][2];
//		PtMapColor.y = pColormap[cmIdx][1];
//		PtMapColor.z = pColormap[cmIdx][0];
//	}
//
//	pcl::PointCloud<pcl::PointXYZRGB>::Ptr dsPcRef(new pcl::PointCloud<pcl::PointXYZRGB>);
//	pcl::PointCloud<pcl::PointXYZRGB>::Ptr dsPcDefx1(new pcl::PointCloud<pcl::PointXYZRGB>);
//	pcl::PointCloud<pcl::PointXYZRGB>::Ptr dsPcDefx10(new pcl::PointCloud<pcl::PointXYZRGB>);
//	pcl::PointCloud<pcl::PointXYZRGB>::Ptr dsPcDefx100(new pcl::PointCloud<pcl::PointXYZRGB>);
//	pcl::PointCloud<pcl::PointXYZRGB>::Ptr dsPcDefx300(new pcl::PointCloud<pcl::PointXYZRGB>);
//	for (size_t ptIdx = 0; ptIdx < pcRef->points.size(); ptIdx+=2)
//	{
//		pcl::PointXYZRGB ptRef = pcRef->points[ptIdx];
//		const cv::Point3d& ptDisp = Disps[ptIdx];
//		const cv::Point3d& ptMapColor = PtsMapColor[ptIdx];
//
//		ptRef.r = ptMapColor.x;
//		ptRef.g = ptMapColor.y;
//		ptRef.b = ptMapColor.z;
//		dsPcRef->points.push_back(ptRef);
//		pcl::PointXYZRGB ptDefx1 = ptRef;
//		ptDefx1.x += ptDisp.x;
//		ptDefx1.y += ptDisp.y;
//		ptDefx1.z += ptDisp.z;
//		dsPcDefx1->points.push_back(ptDefx1);
//		pcl::PointXYZRGB ptDefx10 = ptRef;
//		ptDefx10.x += ptDisp.x * 10;
//		ptDefx10.y += ptDisp.y * 10;
//		ptDefx10.z += ptDisp.z * 10;
//		dsPcDefx10->points.push_back(ptDefx10);
//		pcl::PointXYZRGB ptDefx100 = ptRef;
//		ptDefx100.x += ptDisp.x * 100;
//		ptDefx100.y += ptDisp.y * 100;
//		ptDefx100.z += ptDisp.z * 100;
//		dsPcDefx100->points.push_back(ptDefx100);
//		pcl::PointXYZRGB ptDefx300 = ptRef;
//		ptDefx300.x += ptDisp.x * 300;
//		ptDefx300.y += ptDisp.y * 300;
//		ptDefx300.z += ptDisp.z * 300;
//		dsPcDefx300->points.push_back(ptDefx300);
//	}
//	dsPcRef->resize(dsPcRef->points.size());
//	dsPcDefx1->resize(dsPcDefx1->points.size());
//	dsPcDefx10->resize(dsPcDefx10->points.size());
//	dsPcDefx100->resize(dsPcDefx100->points.size());
//	dsPcDefx300->resize(dsPcDefx300->points.size());
//
//	pcl::io::savePLYFile("dsModelRef.ply", *dsPcRef);
//	pcl::io::savePLYFile("dsModelDef1.ply", *dsPcDefx1);
//	pcl::io::savePLYFile("dsModelDef10.ply", *dsPcDefx10);
//	pcl::io::savePLYFile("dsModelDef100.ply", *dsPcDefx100);
//	pcl::io::savePLYFile("dsModelDef300.ply", *dsPcDefx300);
//
//	return 0;
//}