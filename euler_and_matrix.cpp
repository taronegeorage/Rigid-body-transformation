#include <iostream>

#include <Eigen/Core>
#include <Eigen/Geometry>

using namespace std;

Eigen::Matrix3d euler2RotationMatrix(const double roll, const double pitch, const double yaw);
Eigen::Vector3d RotationMatrix2euler(Eigen::Matrix3d R)  ;

int main()
{
    Eigen::Vector3d euler_angles(1.5708, 0, 0);
    cout << "euler_angles is (yaw pitch roll) =\n" << euler_angles.transpose()<<endl;
    Eigen::Matrix3d rotation_matrix = euler2RotationMatrix(1.5708, 0, 0);
    cout << "Euler to Rotation Matrix: \n" << rotation_matrix << endl;
    Eigen::Vector3d trans_euler_angles = rotation_matrix.eulerAngles(2, 1, 0);
    cout << "Rotation Matrix to Euler: \n" << trans_euler_angles.transpose() <<endl;

    return 0;
}

Eigen::Matrix3d euler2RotationMatrix(const double roll, const double pitch, const double yaw)  
{  
    Eigen::AngleAxisd rollAngle(roll, Eigen::Vector3d::UnitZ());  
    Eigen::AngleAxisd yawAngle(yaw, Eigen::Vector3d::UnitY());  
    Eigen::AngleAxisd pitchAngle(pitch, Eigen::Vector3d::UnitX());  
  
    Eigen::Quaterniond q = rollAngle * yawAngle * pitchAngle;  
    Eigen::Matrix3d R = q.matrix();  
    cout << "Euler2RotationMatrix result is:" <<endl;  
    cout << "R = " << endl << R << endl<<endl;  
    return R;  
}  
  
Eigen::Vector3d RotationMatrix2euler(Eigen::Matrix3d R)  
{  
    Eigen::Matrix3d m;  
    m = R;  
    Eigen::Vector3d euler = m.eulerAngles(0, 1, 2);  
    cout << "RotationMatrix2euler result is: " << endl;  
    cout << "x = "<< euler[2] << endl ;  
    cout << "y = "<< euler[1] << endl ;  
    cout << "z = "<< euler[0] << endl << endl;  
    return euler;  
}  