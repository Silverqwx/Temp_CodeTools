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
//    std::vector<cv::Point3d> Pts(27692);
//    std::vector<cv::Point3d> Disps(27692);
//    std::vector<double> DispL2s(27692);
//    std::vector<double> PtsColor(27692);
//    std::vector<cv::Point3d> PtsMapColor(27692);
//    std::vector<std::vector<double>> PtsColorSet(27692);
//    std::vector<cv::Point3i> faces(54706);
//    std::vector<double> faceColors(54706);
//
//    //read points
//    {
//        ifstream ifile("speakerCloud.csv");
//        string linestr;
//        for (int ptIdx = 0; ptIdx < Pts.size(); ptIdx++)
//        {
//            getline(ifile, linestr);
//            stringstream ss(linestr);
//            string str;
//            std::vector<float> xyz(3);
//            for (int xyzIdx = 0; xyzIdx < 3; xyzIdx++)
//            {
//                getline(ss, str, ',');
//                stringstream ss2(str);
//                float temp = 1.0;
//                ss2 >> temp;
//                xyz[xyzIdx] = temp;
//            }
//            Pts[ptIdx].x = xyz[0];
//            Pts[ptIdx].y = xyz[1];
//            Pts[ptIdx].z = xyz[2];
//        }
//    }
//
//    //read displacements
//    {
//        ifstream ifile("displacements.csv");
//        string linestr;
//        for (int ptIdx = 0; ptIdx < Disps.size(); ptIdx++)
//        {
//            getline(ifile, linestr);
//            stringstream ss(linestr);
//            string str;
//            std::vector<float> xyz(3);
//            for (int xyzIdx = 0; xyzIdx < 3; xyzIdx++)
//            {
//                getline(ss, str, ',');
//                stringstream ss2(str);
//                float temp = 0.0;
//                ss2 >> temp;
//                xyz[xyzIdx] = temp;
//            }
//            Disps[ptIdx].x = xyz[0];
//            Disps[ptIdx].y = xyz[1];
//            Disps[ptIdx].z = xyz[2];
//        }
//    }
//
//    //read faces
//    {
//        ifstream ifile("faces.csv");
//        string linestr;
//        for (int fcIdx = 0; fcIdx < faces.size(); fcIdx++)
//        {
//            getline(ifile, linestr);
//            stringstream ss(linestr);
//            string str;
//            std::vector<int> xyz(3);
//            for (int xyzIdx = 0; xyzIdx < 3; xyzIdx++)
//            {
//                getline(ss, str, ',');
//                stringstream ss2(str);
//                int temp = 0;
//                ss2 >> temp;
//                xyz[xyzIdx] = temp;
//            }
//            faces[fcIdx].x = xyz[0];
//            faces[fcIdx].y = xyz[1];
//            faces[fcIdx].z = xyz[2];
//        }
//    }
//
//    //read face colors
//    {
//        ifstream ifile("faceColors.csv");
//        string linestr;
//        for (int fcIdx = 0; fcIdx < faceColors.size(); fcIdx++)
//        {
//            getline(ifile, linestr);
//            stringstream ss(linestr);
//            string str;
//            std::vector<double> xyz(1);
//            for (int xyzIdx = 0; xyzIdx < 1; xyzIdx++)
//            {
//                getline(ss, str, ',');
//                stringstream ss2(str);
//                double temp = 0;
//                ss2 >> temp;
//                xyz[xyzIdx] = temp;
//            }
//            faceColors[fcIdx] = xyz[0];
//        }
//    }
//
//    double maxDispL2 = 0.0,
//        minDispL2 = 9999.9;
//    for (size_t ptIdx = 0; ptIdx < Disps.size(); ptIdx++)
//    {
//        double& dispL2 = DispL2s[ptIdx];
//        const cv::Point3d& PtDisp = Disps[ptIdx];
//
//        dispL2 = cv::norm(PtDisp);
//
//        if (dispL2 > maxDispL2)
//            maxDispL2 = dispL2;
//        if (dispL2 < minDispL2)
//            minDispL2 = dispL2;
//    }
//    //minDispL2 = minDispL2 * 0.9 + maxDispL2 * 0.1;
//    maxDispL2 = minDispL2 * 0.7 + maxDispL2 * 0.3;
//
//    cv::Mat temp(1, 256, CV_8UC1);
//    uchar* pTemp = temp.data;
//    for (size_t i = 0; i < 256; i++)
//    {
//        pTemp[i] = i;
//    }
//    cv::Mat colormap;
//    cv::applyColorMap(temp, colormap, cv::COLORMAP_JET);
//    cv::Vec3b* pColormap = (cv::Vec3b*)colormap.data;
//    
//    for (size_t ptIdx = 0; ptIdx < DispL2s.size(); ptIdx++)
//    {
//        const double& dispL2 = DispL2s[ptIdx];
//        cv::Point3d& PtMapColor = PtsMapColor[ptIdx];
//
//        int cmIdx = (dispL2 - minDispL2) / (maxDispL2 - minDispL2) * 255;
//        if (cmIdx < 0)
//            cmIdx = 0;
//        if (cmIdx > 255)
//            cmIdx = 255;
//
//        PtMapColor.x = pColormap[cmIdx][2];
//        PtMapColor.y = pColormap[cmIdx][1];
//        PtMapColor.z = pColormap[cmIdx][0];
//    }
//
//    for (size_t fcIdx = 0; fcIdx < faces.size(); fcIdx++)
//    {
//        const cv::Point3i& fc = faces[fcIdx];
//        const double& fcColor = faceColors[fcIdx];
//
//        PtsColorSet[fc.x - 1].push_back(fcColor);
//        PtsColorSet[fc.y - 1].push_back(fcColor);
//        PtsColorSet[fc.z - 1].push_back(fcColor);
//    }
//
//    for (size_t ptIdx = 0; ptIdx < PtsColor.size(); ptIdx++)
//    {
//        double& ptColor = PtsColor[ptIdx];
//        const std::vector<double>& ptColorSet = PtsColorSet[ptIdx];
//
//        double csum = 0.0, cmean;
//        for (size_t cIdx = 0; cIdx < ptColorSet.size(); cIdx++)
//        {
//            csum += ptColorSet[cIdx];
//        }
//        cmean = csum / ptColorSet.size();
//
//        ptColor = cmean;
//    }
//
//	pcl::PointCloud<pcl::PointXYZRGB>::Ptr pcRef(new pcl::PointCloud<pcl::PointXYZRGB>);
//	pcl::PointCloud<pcl::PointXYZRGB>::Ptr pcDefx1(new pcl::PointCloud<pcl::PointXYZRGB>);
//	pcl::PointCloud<pcl::PointXYZRGB>::Ptr pcDefx10(new pcl::PointCloud<pcl::PointXYZRGB>);
//	pcl::PointCloud<pcl::PointXYZRGB>::Ptr pcDefx100(new pcl::PointCloud<pcl::PointXYZRGB>);
//	pcl::PointCloud<pcl::PointXYZRGB>::Ptr pcDefx300(new pcl::PointCloud<pcl::PointXYZRGB>);
//    for (size_t ptIdx = 0; ptIdx < Pts.size(); ptIdx++)
//    {
//        const cv::Point3d& pt3d = Pts[ptIdx];
//        const cv::Point3d& disp3d = Disps[ptIdx];
//        const double& ptColor = PtsColor[ptIdx];
//        const cv::Point3d& ptMapColor = PtsMapColor[ptIdx];
//        
//        pcRef->points.push_back(pcl::PointXYZRGB(pt3d.x, pt3d.y, pt3d.z, ptMapColor.x, ptMapColor.y, ptMapColor.z));
//        pcDefx1->points.push_back(pcl::PointXYZRGB(pt3d.x + disp3d.x, pt3d.y + disp3d.y, pt3d.z + disp3d.z, ptMapColor.x, ptMapColor.y, ptMapColor.z));
//        pcDefx10->points.push_back(pcl::PointXYZRGB(pt3d.x + disp3d.x * 10, pt3d.y + disp3d.y * 10, pt3d.z + disp3d.z * 10, ptMapColor.x, ptMapColor.y, ptMapColor.z));
//        pcDefx100->points.push_back(pcl::PointXYZRGB(pt3d.x + disp3d.x * 100, pt3d.y + disp3d.y * 100, pt3d.z + disp3d.z * 100, ptMapColor.x, ptMapColor.y, ptMapColor.z));
//        pcDefx300->points.push_back(pcl::PointXYZRGB(pt3d.x + disp3d.x * 300, pt3d.y + disp3d.y * 300, pt3d.z + disp3d.z * 300, ptMapColor.x, ptMapColor.y, ptMapColor.z));
//    }
//    pcRef->resize(pcRef->points.size());
//    pcDefx1->resize(pcDefx1->points.size());
//    pcDefx10->resize(pcDefx10->points.size());
//    pcDefx100->resize(pcDefx100->points.size());
//    pcDefx300->resize(pcDefx300->points.size());
//
//    pcl::io::savePLYFile("pcRef.ply", *pcRef);
//    pcl::io::savePLYFile("pcDefx1.ply", *pcDefx1);
//    pcl::io::savePLYFile("pcDefx10.ply", *pcDefx10);
//    pcl::io::savePLYFile("pcDefx100.ply", *pcDefx100);
//    pcl::io::savePLYFile("pcDefx300.ply", *pcDefx300);
//
//	return 0;
//}