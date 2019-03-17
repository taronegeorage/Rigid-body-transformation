# Rigid-body-transformation

Content
-----------------
* rotation_vector_to_matrix.cpp contains several ways to transform rotation vector to rotation matrix including my methods.
* quaternion_and_matrix.cpp includes the transformation between quaternion and rotation matrix. A wonderful project to visuilize and understand quaternion: https://eater.net/quaternions.
* euler_and_quaternion.cpp contains the transformation between euler angle and quaternions. http://quaternions.online is an awesome website to virtulize the relationship between the two.
* euler_and_matrix.cpp contains the transformation between euler angle and rotation matrix using Eigen.


Compile:  
-----------------
g++ \`pkg-config opencv --cflags\` [file to be compiled]  -o [output name] \`pkg-config opencv --libs\`   
g++ \`pkg-config --cflags --libs opencv\` [file to be compiled] -o [output name]   
or   
cmake  
