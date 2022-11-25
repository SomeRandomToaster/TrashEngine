//
// Created by leo on 24/11/22.
//

#ifndef TRASHENGINE_VECTORTRANSFORMATION_HPP
#define TRASHENGINE_VECTORTRANSFORMATION_HPP

#endif //TRASHENGINE_VECTORTRANSFORMATION_HPP

vector3f rotate(const vector3f& vInput, const vector3f& axis, const float angle) {
    vector3f a=axis.normalize();
    float vAngle = acos(dot(a, vector3f(0, 0, 1)));
    vector3f aXY=a-vector3f(0, 0, a.getZ());
    if(aXY.length()==0) {
        aXY=vector3f(1, 0, 0);
    }
    aXY=aXY.normalize();
    float hAngle = acos(dot(aXY, vector3f(1, 0, 0)));
    vector<float> rotateXY_vec(9, 0);
    rotateXY_vec[0]=cos(-hAngle);
    rotateXY_vec[1]=-sin(-hAngle);
    rotateXY_vec[3]=sin(-hAngle);
    rotateXY_vec[4]=cos(-hAngle);
    rotateXY_vec[8]=1;
    //a=a*matrix3f(rotateXY_vec);
    vector<float> rotateXZ_vec(9, 0);
    rotateXZ_vec[0]=cos(-vAngle);
    rotateXZ_vec[2]=sin(-vAngle);
    rotateXZ_vec[6]=-sin(-vAngle);
    rotateXZ_vec[8]=cos(-vAngle);
    rotateXZ_vec[4]=1;
    a=a*matrix3f(rotateXY_vec)*matrix3f(rotateXZ_vec);
    vector3f v=(vInput*matrix3f(rotateXY_vec)*matrix3f(rotateXZ_vec)).normalize();
    rotateXY_vec[0]=cos(angle);
    rotateXY_vec[1]=-sin(angle);
    rotateXY_vec[3]=sin(angle);
    rotateXY_vec[4]=cos(angle);
    rotateXY_vec[8]=1;
    v=v*matrix3f(rotateXY_vec);
    //reverse rotation
    rotateXZ_vec[0]=cos(vAngle);
    rotateXZ_vec[2]=sin(vAngle);
    rotateXZ_vec[6]=-sin(vAngle);
    rotateXZ_vec[8]=cos(vAngle);
    rotateXZ_vec[4]=1;

    rotateXY_vec[0]=cos(hAngle);
    rotateXY_vec[1]=-sin(hAngle);
    rotateXY_vec[3]=sin(hAngle);
    rotateXY_vec[4]=cos(hAngle);
    rotateXY_vec[8]=1;

    v=v*matrix3f(rotateXZ_vec)*matrix3f(rotateXY_vec);
    v=(v.normalize())*vInput.length();
    return v;
}