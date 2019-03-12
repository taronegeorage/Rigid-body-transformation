#include <iostream>
#include <ctime>
#include <cmath>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <opencv2/opencv.hpp>

using namespace std;

Eigen::Matrix3d MyRodrigues2(Eigen::Vector3d r_v);

int main()
{
    Eigen::Matrix3d rotation_matrix = Eigen::Matrix3d::Identity();
    Eigen::AngleAxisd rotation_vector1(M_PI/2, Eigen::Vector3d(0, 0, 1));
    clock_t time_stt = clock();
    rotation_matrix = rotation_vector1.matrix();
    cout << "time used by matrix() is "<<1000*(clock()-time_stt)/(double)CLOCKS_PER_SEC <<"ms"<<endl;
    cout<<"roation matrix is \n"<<rotation_matrix<<endl;
    time_stt = clock();
    rotation_matrix = rotation_vector1.toRotationMatrix();
    cout << endl << "time used by toRotationMatrix() is "<<1000*(clock()-time_stt)/(double)CLOCKS_PER_SEC <<"ms"<<endl;
    cout<<"roation matrix is \n"<<rotation_matrix<<endl;

    double rotation_vector2[3] = {0, 0, M_PI/2};
    double R_matrix[9];
    CvMat pr_vec;
    CvMat pR_matrix;
    cvInitMatHeader(&pr_vec, 1, 3, CV_64FC1, rotation_vector2, CV_AUTOSTEP);
    cvInitMatHeader(&pR_matrix,3,3,CV_64FC1,R_matrix,CV_AUTOSTEP);
    time_stt = clock();
    cvRodrigues2(&pr_vec, &pR_matrix, 0);
    cout << endl << "time used by cvRodrigues2() is "<<1000*(clock()-time_stt)/(double)CLOCKS_PER_SEC <<"ms"<<endl;
    for(int i=0; i<9; i++)
    {
        cout << R_matrix[i] << " ";
        if(i % 3 == 0)
            cout << endl;
    }

    cv::Mat_<float> rotation_vector3 = (cv::Mat_<float>(3, 1) << 0, 0, 1.5708);
    cv::Mat rotation_matrix3;
    time_stt = clock();
    Rodrigues(rotation_vector3, rotation_matrix3);
    cout << endl << "time used by Rodrigues() is "<<1000*(clock()-time_stt)/(double)CLOCKS_PER_SEC <<"ms"<<endl;
    cout << rotation_matrix3 <<endl;

    Eigen::Vector3d rotation_vector4(0, 0, M_PI/2);
    time_stt = clock();
    rotation_matrix = MyRodrigues2(rotation_vector4);
    cout << endl << "time used by MyRodrigues() is "<<1000*(clock()-time_stt)/(double)CLOCKS_PER_SEC <<"ms"<<endl;
    cout << rotation_matrix <<endl;

    return 0;
}


//R=cosθI+(1−cosθ)kkT+k×sinθ
Eigen::Matrix3d MyRodrigues2(Eigen::Vector3d r_v)
{
    double theta = 0;
    Eigen::Vector3d k(0, 0, 0);
    for(int i = 0; i < 3; i++){
        if(r_v(i) != 0){
            theta = r_v(i);
            k(i) = 1;
        }
    }
    Eigen::Matrix3d k_x;
    k_x << 0, -k(2), k(1), k(2), 0, -k(0), -k(1), k(0), 0;

    Eigen::Matrix3d rotation_matrix = Eigen::Matrix3d::Identity();
    rotation_matrix(0, 0) = rotation_matrix(1, 1) = rotation_matrix(2, 2) = cos(theta);
    rotation_matrix += k*k.transpose()*(1-cos(theta)) + k_x*sin(theta);
    return rotation_matrix;
}