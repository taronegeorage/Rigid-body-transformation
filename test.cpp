#include <iostream>
#include <cmath>

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>
using namespace std;

int main(int argc, char** argv)
{
    /*
    // Rotation 
    Eigen::Matrix3d rotation_matrix = Eigen::Matrix3d::Identity();
    // Roation Vector
    Eigen::AngleAxisd rotation_vector(M_PI/4, Eigen::Vector3d(0, 0, 1));
    cout .precision(3);
    cout<<"roation matrix \n"<<rotation_vector.matrix()<<endl;
    rotation_matrix = rotation_vector.toRotationMatrix();

    // use AngleAxis to transform
    Eigen::Vector3d v(1, 0, 0);
    Eigen::Vector3d v_rotated = rotation_vector * v;
    cout << "(1, 0, 0) after rotation \n"<<v_rotated.transpose()<<endl;
    //or use rotation matrix
    v_rotated = rotation_matrix * v;
    cout << "(1, 0, 0) after rotation \n"<<v_rotated.transpose()<<endl;

    // Euler angle
    Eigen::Vector3d euler_angles = rotation_matrix.eulerAngles(2, 1, 0);
    cout << "yaw pitch roll =\n" << euler_angles.transpose()<<endl;

    // Transform matrix
    Eigen::Isometry3d T = Eigen::Isometry3d::Identity();
    T.rotate(rotation_vector);
    T.pretranslate(Eigen::Vector3d(1, 3, 4));
    cout << "Transformation Matrix = \n"<<T.matrix()<<endl;
    //Transform
    Eigen::Vector3d v_transformed = T * v;
    cout << "v transformed = \n"<<v_transformed.transpose()<<endl;

    //Eigen::Affine3d and Eigen::Projective3d 

    //Quaterniond
    Eigen::Quaterniond q = Eigen::Quaterniond(rotation_vector);
    cout<<"quaternion = \n"<<q.coeffs()<<endl;
    q = Eigen::Quaterniond(rotation_matrix);
    cout<<"quaternion = \n"<<q.coeffs()<<endl;
    v_rotated = q * v;
    cout << "(1, 0, 0) after rotation \n"<<v_rotated.transpose()<<endl;
    */
   Eigen::Vector3d v(0.2, 0.3, 3.0);
   Eigen::AngleAxisd r1(M_PI*5.2/180, Eigen::Vector3d(0, 1, 0));
   Eigen::AngleAxisd r2(M_PI*0.3/180, Eigen::Vector3d(0, 0, 1));
   Eigen::AngleAxisd r3(M_PI*3.1/180, Eigen::Vector3d(1, 0, 0));
   cout<<(r3 * r2 * r1).matrix()<<endl;
   //Eigen::Vector3d v_rotated = r3 * r2 * r1 * v;
   Eigen::Vector3d t(0.01, 0.02, 0.5);
   Eigen::Isometry3d T = Eigen::Isometry3d::Identity();
   T.rotate(r3 * r2 * r1);
   T.pretranslate(t);

   //cout<<v_rotated+t<<endl;
   return 0;

}
