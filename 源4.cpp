//转移坐标系，测量平面对齐到与z轴垂直
 
 #include <iostream>
#include <fstream>

#include <opencv2/opencv.hpp>

using namespace std;

int main()
{
    const cv::Point3d Pt_LU(-6.33994827420876e+01, 2.77722466488697e+01, -3.28756782408648e+01),
        Pt_RU(7.66828169444782e+01, 2.99380352397075e+01, -4.45475654210797e+01),
        Pt_LD(-6.33631701750515e+01, -3.74873001103480e+01, -4.25147344306132e+01),
        Pt_RD(7.73314148134802e+01, -3.53636116390787e+01, -5.43457794932436e+01);

    //cv::Point3d _vec_x = Pt_RU - Pt_LU;
    //cv::Point3d _vec_y = Pt_LD - Pt_LU;

    /*double temp = vec_x.dot(vec_y);
    double temp2 = vec_x.x*vec_y.x+ vec_x.y * vec_y.y + vec_x.z * vec_y.z;*/

    cv::Mat A = cv::Mat::ones(4, 3, CV_64FC1);
    A.at<double>(0, 0) = Pt_LU.x;
    A.at<double>(0, 1) = Pt_LU.y;
    A.at<double>(0, 2) = Pt_LU.z;
    A.at<double>(1, 0) = Pt_RU.x;
    A.at<double>(1, 1) = Pt_RU.y;
    A.at<double>(1, 2) = Pt_RU.z;
    A.at<double>(2, 0) = Pt_LD.x;
    A.at<double>(2, 1) = Pt_LD.y;
    A.at<double>(2, 2) = Pt_LD.z;
    A.at<double>(3, 0) = Pt_RD.x;
    A.at<double>(3, 1) = Pt_RD.y;
    A.at<double>(3, 2) = Pt_RD.z;
    cv::Mat B(4, 1, CV_64FC1, cv::Scalar(-1.0));

    cv::Mat X = (A.t() * A).inv() * A.t() * B;
    cv::Point3d vec_z(X.at<double>(0, 0), X.at<double>(1, 0), X.at<double>(2, 0));

    //double temp = vec_z.dot(vec_x);

    cv::Point3d pPt_LU, pPt_RU, pPt_LD, pPt_RD;
    double a = vec_z.x,
        b = vec_z.y,
        c = vec_z.z;
    {
        const cv::Point3d& pt3d = Pt_LU;
        cv::Point3d& pPt = pPt_LU;

        double x0 = pt3d.x,
            y0 = pt3d.y,
            z0 = pt3d.z;
        double k = -(a * x0 + b * y0 + c * z0 + 1) / (a * a + b * b + c * c);
        pPt = pt3d + k * vec_z;
    }
    {
        const cv::Point3d& pt3d = Pt_RU;
        cv::Point3d& pPt = pPt_RU;

        double x0 = pt3d.x,
            y0 = pt3d.y,
            z0 = pt3d.z;
        double k = -(a * x0 + b * y0 + c * z0 + 1) / (a * a + b * b + c * c);
        pPt = pt3d + k * vec_z;
    }
    {
        const cv::Point3d& pt3d = Pt_LD;
        cv::Point3d& pPt = pPt_LD;

        double x0 = pt3d.x,
            y0 = pt3d.y,
            z0 = pt3d.z;
        double k = -(a * x0 + b * y0 + c * z0 + 1) / (a * a + b * b + c * c);
        pPt = pt3d + k * vec_z;
    }
    {
        const cv::Point3d& pt3d = Pt_RD;
        cv::Point3d& pPt = pPt_RD;

        double x0 = pt3d.x,
            y0 = pt3d.y,
            z0 = pt3d.z;
        double k = -(a * x0 + b * y0 + c * z0 + 1) / (a * a + b * b + c * c);
        pPt = pt3d + k * vec_z;
    }

    cv::Point3d pPt_mid = (pPt_LU + pPt_RU + pPt_LD + pPt_RD) / 4;
    cv::Point3d vec_x = pPt_RU - pPt_LU;
    vec_z = vec_z;

    vec_x = vec_x / cv::norm(vec_x);
    vec_z = vec_z / cv::norm(vec_z);
    cv::Point3d vec_y = vec_z.cross(vec_x);

    double temp = vec_z.dot(vec_x);
    double temp2 = vec_z.dot(vec_y);
    double temp3 = vec_x.dot(vec_y);

    cv::Mat R(3, 3, CV_64FC1);
    R.at<double>(0, 0) = vec_x.x;
    R.at<double>(0, 1) = vec_x.y;
    R.at<double>(0, 2) = vec_x.z;
    R.at<double>(1, 0) = vec_y.x;
    R.at<double>(1, 1) = vec_y.y;
    R.at<double>(1, 2) = vec_y.z;
    R.at<double>(2, 0) = vec_z.x;
    R.at<double>(2, 1) = vec_z.y;
    R.at<double>(2, 2) = vec_z.z;
    //R = R.inv();
    cv::Mat t(3, 1, CV_64FC1);
    t.at<double>(0, 0) = pPt_mid.x;
    t.at<double>(1, 0) = pPt_mid.y;
    t.at<double>(2, 0) = pPt_mid.z;
    cv::Mat T = cv::Mat::eye(4, 4, CV_64FC1);
    R.copyTo(T(cv::Rect(0, 0, 3, 3)));
    cv::Mat newt = -R * t;
    newt.copyTo(T(cv::Rect(3, 0, 1, 3)));

    cv::Mat pPt_LU_m = cv::Mat::ones(4, 1, CV_64FC1);
    pPt_LU_m.at<double>(0, 0) = pPt_LU.x;
    pPt_LU_m.at<double>(1, 0) = pPt_LU.y;
    pPt_LU_m.at<double>(2, 0) = pPt_LU.z;
    cv::Mat pPt_RU_m = cv::Mat::ones(4, 1, CV_64FC1);
    pPt_RU_m.at<double>(0, 0) = pPt_RU.x;
    pPt_RU_m.at<double>(1, 0) = pPt_RU.y;
    pPt_RU_m.at<double>(2, 0) = pPt_RU.z;
    cv::Mat pPt_LD_m = cv::Mat::ones(4, 1, CV_64FC1);
    pPt_LD_m.at<double>(0, 0) = pPt_LD.x;
    pPt_LD_m.at<double>(1, 0) = pPt_LD.y;
    pPt_LD_m.at<double>(2, 0) = pPt_LD.z;
    cv::Mat pPt_RD_m = cv::Mat::ones(4, 1, CV_64FC1);
    pPt_RD_m.at<double>(0, 0) = pPt_RD.x;
    pPt_RD_m.at<double>(1, 0) = pPt_RD.y;
    pPt_RD_m.at<double>(2, 0) = pPt_RD.z;

    cv::Mat tpPt_LU_m = T * pPt_LU_m;
    cv::Mat tpPt_RU_m = T * pPt_RU_m;
    cv::Mat tpPt_LD_m = T * pPt_LD_m;
    cv::Mat tpPt_RD_m = T * pPt_RD_m;

    {
        cv::FileStorage xfsl("T_m2w.xml", cv::FileStorage::WRITE);
        xfsl << "T_m2w" << T;
        xfsl.release();
    }

    std::string readDir = "d://PhD_Engineering//3 visualization (not research)//Experiment Task//2024.07.09 woodenSpeakerFront_whitepaint//ExpT1900_Gain1_L40Hz_R100Hz_volume33//results_OpenCorr3D_sR128_frontVertices//";
    std::string saveDir = "saveCSV//";
    int startFrame = 2001,
        endFrame = 3500;
    int ptNum = 130569;
    {
        std::string fileName = "points.csv";
        std::vector<cv::Point3d> calPts(ptNum);
        std::vector<cv::Point3d> tCalPts(ptNum);
        {
            ifstream ifile(readDir + fileName);
            string linestr;
            for (int ptIdx = 0; ptIdx < calPts.size(); ptIdx++)
            {
                getline(ifile, linestr);
                stringstream ss(linestr);
                string str;
                std::vector<float> xyz(4);
                for (int xyzIdx = 0; xyzIdx < 4; xyzIdx++)
                {
                    getline(ss, str, ',');
                    stringstream ss2(str);
                    float temp = 1.0;
                    ss2 >> temp;
                    xyz[xyzIdx] = temp;
                }
                calPts[ptIdx].x = xyz[1];
                calPts[ptIdx].y = xyz[2];
                calPts[ptIdx].z = xyz[3];
            }
        }
        // process
        for (size_t ptIdx = 0; ptIdx < calPts.size(); ptIdx++)
        {
            const cv::Point3d& pt3d = calPts[ptIdx];
            cv::Point3d& tpt3d = tCalPts[ptIdx];

            cv::Mat pt_m = cv::Mat::ones(4, 1, CV_64FC1);
            pt_m.at<double>(0, 0) = pt3d.x;
            pt_m.at<double>(1, 0) = pt3d.y;
            pt_m.at<double>(2, 0) = pt3d.z;
            cv::Mat tPt_m = T * pt_m;

            tpt3d.x = tPt_m.at<double>(0, 0);
            tpt3d.y = tPt_m.at<double>(1, 0);
            tpt3d.z = tPt_m.at<double>(2, 0);
        }
        //save
        {
            std::ofstream ofile(saveDir + fileName);
            for (int xyzIdx = 0; xyzIdx < tCalPts.size(); xyzIdx++)
            {
                const cv::Point3d& xyz = tCalPts[xyzIdx];

                ofile << xyz.x << "," << xyz.y << "," << xyz.z;
                ofile << endl;
            }
            ofile.close();
        }
    }
    {
        std::string fileName = "calpoints.csv";
        std::vector<cv::Point3d> calPts(ptNum);
        std::vector<cv::Point3d> tCalPts(ptNum);
        {
            ifstream ifile(readDir + fileName);
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
                calPts[ptIdx].z = xyz[2];
            }
        }
        // process
        for (size_t ptIdx = 0; ptIdx < calPts.size(); ptIdx++)
        {
            const cv::Point3d& pt3d = calPts[ptIdx];
            cv::Point3d& tpt3d = tCalPts[ptIdx];

            cv::Mat pt_m = cv::Mat::ones(4, 1, CV_64FC1);
            pt_m.at<double>(0, 0) = pt3d.x;
            pt_m.at<double>(1, 0) = pt3d.y;
            pt_m.at<double>(2, 0) = pt3d.z;
            cv::Mat tPt_m = T * pt_m;

            tpt3d.x= tPt_m.at<double>(0, 0);
            tpt3d.y= tPt_m.at<double>(1, 0);
            tpt3d.z= tPt_m.at<double>(2, 0);
        }
        //save
        {
            std::ofstream ofile(saveDir + fileName);
            for (int xyzIdx = 0; xyzIdx < tCalPts.size(); xyzIdx++)
            {
                const cv::Point3d& xyz = tCalPts[xyzIdx];

                ofile << xyz.x << "," << xyz.y << "," << xyz.z;
                ofile << endl;
            }
            ofile.close();
        }
    }
    for (size_t fIdx = startFrame; fIdx <= endFrame; fIdx++)
    {
        std::stringstream ss;
        ss << fIdx;

        std::string fileName = "resultF" + ss.str() + ".csv";
        std::vector<cv::Point3d> disps(ptNum);
        std::vector<cv::Point3d> tDisps(ptNum);
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
        // process
        for (size_t ptIdx = 0; ptIdx < disps.size(); ptIdx++)
        {
            const cv::Point3d& disp3d = disps[ptIdx];
            cv::Point3d& tDisp3d = tDisps[ptIdx];

            cv::Mat disp_m = cv::Mat::ones(3, 1, CV_64FC1);
            disp_m.at<double>(0, 0) = disp3d.x;
            disp_m.at<double>(1, 0) = disp3d.y;
            disp_m.at<double>(2, 0) = disp3d.z;
            cv::Mat tDisp_m = R * disp_m;

            tDisp3d.x = tDisp_m.at<double>(0, 0);
            tDisp3d.y = tDisp_m.at<double>(1, 0);
            tDisp3d.z = tDisp_m.at<double>(2, 0);
        }
        //save
        {
            std::ofstream ofile(saveDir + fileName);
            for (int xyzIdx = 0; xyzIdx < tDisps.size(); xyzIdx++)
            {
                const cv::Point3d& dxyz = tDisps[xyzIdx];

                ofile << dxyz.x << "," << dxyz.y << "," << dxyz.z;
                ofile << endl;
            }
            ofile.close();
        }
    }

	return 0;
}