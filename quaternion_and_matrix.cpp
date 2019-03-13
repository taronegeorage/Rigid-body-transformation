#include <iostream>
#include <cmath>

#include <Eigen/Core>
#include <Eigen/Geometry>

using namespace std;

Eigen::Matrix3d QuaternionToRotationMatrix(const double x,const double y,const double z,const double w);
Eigen::Matrix3d MyQuaternionToRotationMatrix(Eigen::Quaterniond quat);
Eigen::Quaterniond MyRotationMatrixToQuaternion(Eigen::Matrix3d R);


int main()
{
    Eigen::AngleAxisd rotation_vector(M_PI/2, Eigen::Vector3d(0, 0, 1));
    Eigen::Matrix3d rotation_matrix = Eigen::Matrix3d::Identity();
    rotation_matrix = rotation_vector.toRotationMatrix();
    cout << "The rotation matrix is \n" << rotation_matrix<<endl;

    
    // Rotation Matrix to Quaternion
    clock_t time_stt = clock();
    Eigen::Quaterniond q = Eigen::Quaterniond(rotation_matrix);
    cout << "time used by Quaterniond() is "<<1000*(clock()-time_stt)/(double)CLOCKS_PER_SEC <<"ms"<<endl;
    cout<<"Matrix to Quaternion: \n"<<q.coeffs()<<endl;

    time_stt = clock();
    q = MyRotationMatrixToQuaternion(rotation_matrix);
    cout << "time used by MyRotationMatrixToQuaternion() is "<<1000*(clock()-time_stt)/(double)CLOCKS_PER_SEC <<"ms"<<endl;
    cout<<"My Matrix to Quaternion: \n"<<q.coeffs()<<endl;

    // Quaternion to Rotation Matrix
    time_stt = clock();
    rotation_matrix = q.toRotationMatrix();
    cout << "time used by toRotationMatrix() is "<<1000*(clock()-time_stt)/(double)CLOCKS_PER_SEC <<"ms"<<endl;
    cout<< "Quaternion to Matrix: \n" << rotation_matrix <<endl;

    time_stt = clock();
    rotation_matrix = MyQuaternionToRotationMatrix(q);
    cout << "time used by MyQuaternionToRotationMatrix() is "<<1000*(clock()-time_stt)/(double)CLOCKS_PER_SEC <<"ms"<<endl;
    cout<< "My Quaternion to Matrix: \n" << rotation_matrix <<endl;

    return 0;
}

// Given the Quaternion, normalization before transformation
Eigen::Matrix3d QuaternionToRotationMatrix(const double x,const double y,const double z,const double w)  
{  
    Eigen::Quaterniond q;  
    q.x() = x;  
    q.y() = y;  
    q.z() = z;  
    q.w() = w;  
    Eigen::Matrix3d R = q.normalized().toRotationMatrix();  
    return R;  
}  

Eigen::Matrix3d MyQuaternionToRotationMatrix(Eigen::Quaterniond quat)
{
    quat = quat.normalized();
    Eigen::Matrix3d rotationMatrix;
    rotationMatrix << 1-2*(quat.y()*quat.y()+quat.z()*quat.z()), 2*(quat.x()*quat.y()-quat.w()*quat.z()), 2*(quat.x()*quat.z()+quat.w()*quat.y()),
                        2*(quat.x()*quat.y()+quat.w()*quat.z()), 1-2*(quat.x()*quat.x()+quat.z()*quat.z()), 2*(quat.y()*quat.z()-quat.w()*quat.x()),
                        2*(quat.x()*quat.z()-quat.w()*quat.y()), 2*(quat.y()*quat.z()+quat.w()*quat.x()), 1-2*(quat.x()*quat.x()+quat.y()*quat.y());
    return rotationMatrix;
}

Eigen::Quaterniond MyRotationMatrixToQuaternion(Eigen::Matrix3d R)
{
    // 1 + tr(R) > 0
    Eigen::Quaterniond q;
    q.w() = sqrt(R.trace()+1) / 2;
    q.x() = (R(1, 2) - R(2, 1)) / 4 / q.w();
    q.y() = (R(2, 0) - R(0, 2)) / 4 / q.w();
    q.z() = (R(1, 0) - R(0, 1)) / 4 / q.w();
    // Else q.w() approach 0
    // three scenarios: need to find max(R(0,0), R(1,1), R(2,2))
    return q;
}