#include <iostream>
#include <cmath>

#include <Eigen/Core>
#include <Eigen/Geometry>

using namespace std;

typedef struct
{
    float Pitch;
    float Roll;
    float Yaw;
} Euler;


typedef struct
{
	float w, x, y, z;
}Quat;


Eigen::Quaterniond EulerToQuaternion(const double roll, const double pitch, const double yaw);
Eigen::Vector3d QuaternionToEuler(const double x,const double y,const double z,const double w);

int Conversion_Euler_to_Quaternion(Quat *q1, Euler *euler_angle);

int Conversion_Quaternion_to_Euler(Quat *quat, Euler *euler);

int quat_pro(Quat *quat1, Quat *quat2, Quat *quat3);


int main()
{
    Eigen::Vector3d euler_angles(1.5708, 0, 0);
    cout << "euler_angles is (yaw pitch roll) =\n" << euler_angles.transpose()<<endl;
    Eigen::Quaterniond q1;
    q1 = Eigen::AngleAxisd(euler_angles[2], Eigen::Vector3d::UnitX()) * Eigen::AngleAxisd(euler_angles[1], Eigen::Vector3d::UnitY()) * Eigen::AngleAxisd(euler_angles[0], Eigen::Vector3d::UnitZ());
    cout << "euler to quaternion: " << q1.coeffs() << endl;
    auto euler1 = q1.toRotationMatrix().eulerAngles(2, 1, 0);
    cout << "quaternion to euler: \n" << euler1.transpose() << endl;


    return 0;
}

Eigen::Quaterniond EulerToQuaternion(const double roll, const double pitch, const double yaw)  
{  
    Eigen::AngleAxisd rollAngle(roll, Eigen::Vector3d::UnitZ());  
    Eigen::AngleAxisd yawAngle(yaw, Eigen::Vector3d::UnitY());  
    Eigen::AngleAxisd pitchAngle(pitch, Eigen::Vector3d::UnitX());  
    Eigen::Quaterniond q = rollAngle * yawAngle * pitchAngle; 
    return q;  
}  
  
Eigen::Vector3d QuaternionToEuler(const double x,const double y,const double z,const double w)  
{  
    Eigen::Quaterniond q;  
    q.x() = x;  
    q.y() = y;  
    q.z() = z;  
    q.w() = w;  
  
    Eigen::Vector3d euler = q.toRotationMatrix().eulerAngles(2, 1, 0);  
    return euler;
}  

int Conversion_Euler_to_Quaternion(Quat *q1, Euler *euler_angle)
{
	euler_angle->Yaw = euler_angle->Yaw *  M_PI / 180;
	euler_angle->Pitch = euler_angle->Pitch * M_PI / 180;
	euler_angle->Roll = euler_angle->Roll * M_PI / 180;
	double c1 = acos(euler_angle->Yaw / 2);
	double s1 = asin(euler_angle->Yaw / 2);
	double c2 = acos(euler_angle->Pitch / 2);
	double s2 = asin(euler_angle->Pitch / 2);
	double c3 = acos(euler_angle->Roll / 2);
	double s3 = asin(euler_angle->Roll / 2);
	double c1c2 = c1 * c2;
	double s1s2 = s1 * s2;
	q1->w = (c1c2 * c3 + s1s2 * s3);
	q1->x = (c1c2 * s3 - s1s2 * c3);
	q1->y = (s1 * c2 * c3 + c1 * s2 * s3);
	q1->z = (c1 * s2 * c3 - s1 * c2 * s3);
	return 0;
}

int Conversion_Quaternion_to_Euler(Quat *quat, Euler *euler)
{
	double q0, q1, q2, q3;
	q0 = quat->w;
	q1 = quat->x;
	q2 = quat->y;
	q3 = quat->z;
	euler->Pitch = (float)(asin(-2 * q1 * q3 + 2 * q0* q2)* 57.3); 
	euler->Roll = (float)(atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3); 
	euler->Yaw = (float)(atan2(2 * (q1*q2 + q0*q3), q0*q0 + q1*q1 - q2*q2 - q3*q3) * 57.3);
	return 0;
}

int quat_pro(Quat *quat1, Quat *quat2, Quat *quat3)
{
	float w1, x1, y1, z1;
	float w2, x2, y2, z2;
	w2 = quat1->w;
	x2 = quat1->x;
	y2 = quat1->y;
	z2 = quat1->z;
 
	w1 = quat2->w;
	x1 = quat2->x;
	y1 = quat2->y;
	z1 = quat2->z;
 
	quat3->w = w1*w2 - x1*x2 - y1*y2 - z1*z2;
	quat3->x = w1*x2 + x1*w2 + y1*z2 - z1*y2;
	quat3->y = w1*y2 - x1*z2 + y1*w2 + z1*x2;
	quat3->z = w1*z2 + x1*y2 - y1*x2 + z1*w2;
	return 0;
}