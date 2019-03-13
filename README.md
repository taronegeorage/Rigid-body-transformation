# Rigid-body-transformation

Content
-----------------
* rotation_vector_to_matrix.cpp contains several ways to transform rotation vector to rotation matrix including my methods.
* quaternion_and_matrix.cpp includes the transformation between quaternion and rotation matrix. A wonderful project to visuilize and understand quaternion: https://eater.net/quaternions.


Compile:  
-----------------
g++ \`pkg-config opencv --cflags\` [file to be compiled]  -o [output name] \`pkg-config opencv --libs\`   
g++ \`pkg-config --cflags --libs opencv\` [file to be compiled] -o [output name]   
or   
cmake  
