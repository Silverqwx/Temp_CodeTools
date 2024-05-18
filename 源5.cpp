#include <iostream>
#include <fstream>

#include <opencv2/opencv.hpp>

using namespace std;

int main()
{
    std::string readDir = "d://OneDrive - Hiroshima University//Doctor Program//Research//3 visualization (not research)//Experiment Task//2024.05.02 AccuracyExperiment//2024.05.11 arrayPts_OpenCorr_subset192 (rotated to alignment)//";
    //std::string readDir = "saveCSV//";
    std::string saveDir = "saveCSV//";
    std::string ptsFileName = "calpoints.csv";
    int startFrame = 2,
        endFrame = 11;
    int dataNum = endFrame - startFrame + 1;
    int ptNum = 100;

    std::vector<cv::Point3d> calPts(ptNum);
    //std::vector<cv::Point3d> expectDisp(dataNum);
    std::vector<std::vector<cv::Point3d>> dispsSet(dataNum, std::vector<cv::Point3d>(ptNum));
    //std::vector<double> distsRef(ptNum);
    std::vector<std::vector<double>> distsPlaneSet(dataNum, std::vector<double>(ptNum));
    //std::vector<std::vector<double>> distsPlaneSet_rmRef(dataNum, std::vector<double>(ptNum));

    ////set expect disps
    //{
    //    expectDisp[0] = cv::Point3d(0.47, 0.0, 0.0);
    //    expectDisp[1] = cv::Point3d(1.02, 0.0, 0.0);
    //    expectDisp[2] = cv::Point3d(1.46, 0.0, 0.0);
    //    expectDisp[3] = cv::Point3d(1.99, 0.0, 0.0);
    //    expectDisp[4] = cv::Point3d(2.51, 0.0, 0.0);
    //    expectDisp[5] = cv::Point3d(3.01, 0.0, 0.0);
    //    expectDisp[6] = cv::Point3d(3.49, 0.0, 0.0);
    //    expectDisp[7] = cv::Point3d(3.955, 0.0, 0.0);
    //    expectDisp[8] = cv::Point3d(4.46, 0.0, 0.0);
    //    expectDisp[9] = cv::Point3d(4.995, 0.0, 0.0);
    //}
    //read cal points
    //{
    //    for (int ptIdx = 0; ptIdx < calPts.size(); ptIdx++)
    //    {
    //        calPts[ptIdx].x = ptIdx / 10;
    //        calPts[ptIdx].y = ptIdx % 10;
    //        calPts[ptIdx].z = 2;
    //    }
    //    //calPts[0].z = 1;
    //    //calPts[99].z = -1;
    //}
    {
        ifstream ifile(readDir + ptsFileName);
        string linestr;
        for (int ptIdx = 0; ptIdx < calPts.size(); ptIdx++)
        {
            getline(ifile, linestr);
            stringstream ss(linestr);
            string str;
            std::vector<float> xyz(3);
            for (int xyzIdx = 0; xyzIdx < 3; xyzIdx++)
            {
                getline(ss, str, ',');
                stringstream ss2(str);
                float temp = 1.0;
                ss2 >> temp;
                xyz[xyzIdx] = temp;
            }
            calPts[ptIdx].x = xyz[0];
            calPts[ptIdx].y = xyz[1];
            calPts[ptIdx].z = xyz[2] + 1;
        }
    }
    //read disps
    for (size_t fIdx = startFrame; fIdx <= endFrame; fIdx++)
    {
        std::stringstream ss;
        ss << fIdx;

        const int dataIdx = fIdx - startFrame;
        std::vector<cv::Point3d>& disps = dispsSet[dataIdx];
        std::string fileName = "resultF" + ss.str() + ".csv";
        {
            ifstream ifile(readDir + fileName);
            string linestr;
            for (int ptIdx = 0; ptIdx < disps.size(); ptIdx++)
            {
                getline(ifile, linestr);
                stringstream ss(linestr);
                string str;
                std::vector<float> xyz(3);
                for (int xyzIdx = 0; xyzIdx < 3; xyzIdx++)
                {
                    getline(ss, str, ',');
                    stringstream ss2(str);
                    float temp = 1.0;
                    ss2 >> temp;
                    xyz[xyzIdx] = temp;
                }
                disps[ptIdx].x = xyz[0];
                disps[ptIdx].y = xyz[1];
                disps[ptIdx].z = xyz[2];
            }
        }
    }
    //proc for each step
    for (size_t dataIdx = 0; dataIdx < dataNum; dataIdx++)
    {
        std::vector<cv::Point3d> defPts(ptNum);
        const std::vector<cv::Point3d>& disps = dispsSet[dataIdx];
        for (size_t ptIdx = 0; ptIdx < ptNum; ptIdx++)
        {
            defPts[ptIdx] = calPts[ptIdx] + disps[ptIdx];
        }

        //fit plane
        cv::Point3d abc;
        double plane_d = 1.0;
        {
            int rowNum = ptNum;

            cv::Mat A = cv::Mat::ones(rowNum, 3, CV_64FC1);
            for (size_t ptIdx = 0; ptIdx < ptNum; ptIdx++)
            {
                const cv::Point3d& pt3d = defPts[ptIdx];

                A.at<double>(ptIdx, 0) = pt3d.x;
                A.at<double>(ptIdx, 1) = pt3d.y;
                A.at<double>(ptIdx, 2) = pt3d.z;
            }
            cv::Mat B(rowNum, 1, CV_64FC1, cv::Scalar(-1.0));

            cv::Mat X = (A.t() * A).inv() * A.t() * B;

            abc = cv::Point3d(X.at<double>(0, 0), X.at<double>(1, 0), X.at<double>(2, 0));

            double abcNorm = cv::norm(abc);
            abc = abc / abcNorm;
            plane_d = plane_d / abcNorm;
        }

        //calculate distances from plane
        {
            std::vector<double>& distsPlane = distsPlaneSet[dataIdx];

            for (size_t ptIdx = 0; ptIdx < ptNum; ptIdx++)
            {
                double a = abc.x,
                    b = abc.y,
                    c = abc.z;
                const cv::Point3d& procPt = defPts[ptIdx];
                double& dist = distsPlane[ptIdx];

                dist = a * procPt.x + b * procPt.y + c * procPt.z + plane_d;
            }
        }

        //save
        {
            int fIdx = dataIdx + startFrame;
            const std::vector<double>& saveDists = distsPlaneSet[dataIdx];

            std::stringstream ss;
            ss << fIdx;

            std::string fileName = "distsPlaneF" + ss.str() + ".csv";

            std::ofstream ofile(saveDir + fileName);
            for (int xyzIdx = 0; xyzIdx < saveDists.size(); xyzIdx++)
            {
                const double& dist = saveDists[xyzIdx];

                ofile << dist;
                ofile << endl;
            }
            ofile.close();
        }

    }

	return 0;
}