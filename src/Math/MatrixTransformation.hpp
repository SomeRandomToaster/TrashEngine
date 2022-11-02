//
// Created by leo on 02/11/22.
//

#ifndef TRASHENGINE_MATRIXTRANSFORMER_HPP
#define TRASHENGINE_MATRIXTRANSFORMER_HPP

#endif //TRASHENGINE_MATRIXTRANSFORMER_HPP

class MatrixTransformer {
    vector3f translate;
    vector3f rotate;
    vector3f scale;
    void updateMatrix();
public:
    void setTranslation(const float x, const float y, const float z);
    void setRotation(const float x, const float y, const float z);
    void setScale(const float x, const float y, const float z);
    void addTranslation(const float x, const float y, const float z);
    matrix4f transformMatrix;
    MatrixTransformer();
    float* getMatrixData();
    matrix4f getMatrix();
};

MatrixTransformer::MatrixTransformer() :
    translate(0, 0, 0),
    rotate(0, 0, 0),
    scale(1, 1, 1)
    {
        transformMatrix.initIdentity();
        /*for(int i=0; i<16; i++) {
            cout << transformMatrix.data[i] << " ";
        }*/
    }
void MatrixTransformer::updateMatrix() {
    transformMatrix.initIdentity();
    transformMatrix.data[3]=translate.getX();
    transformMatrix.data[7]=translate.getY();
    transformMatrix.data[11]=translate.getZ();

    matrix4f rotateYZ;
    rotateYZ.initIdentity();
    rotateYZ.data[5]=cos(rotate.getX());
    rotateYZ.data[6]=-sin(rotate.getX());
    rotateYZ.data[9]=sin(rotate.getX());
    rotateYZ.data[10]=cos(rotate.getX());

    matrix4f rotateXZ;
    rotateXZ.initIdentity();
    rotateXZ.data[0]=cos(rotate.getY());
    rotateXZ.data[2]=sin(rotate.getY());
    rotateXZ.data[8]=-sin(rotate.getY());
    rotateXZ.data[10]=cos(rotate.getY());

    matrix4f rotateXY;
    rotateXY.initIdentity();
    rotateXY.data[0]=cos(rotate.getZ());
    rotateXY.data[1]=-sin(rotate.getZ());
    rotateXY.data[4]=sin(rotate.getZ());
    rotateXY.data[5]=cos(rotate.getZ());

    matrix4f scaleMatrix;
    scaleMatrix.initIdentity();
    scaleMatrix.data[0]=scale.getX();
    scaleMatrix.data[5]=scale.getY();
    scaleMatrix.data[10]=scale.getZ();

    transformMatrix=transformMatrix*rotateYZ*rotateXZ*rotateXY*scaleMatrix;
}
void MatrixTransformer::setTranslation(const float x, const float y, const float z) {
    translate=vector3f(x, y, z);
    updateMatrix();
}
void MatrixTransformer::setRotation(const float x, const float y, const float z) {
    rotate=vector3f(x, y, z);
    updateMatrix();
}
void MatrixTransformer::setScale(const float x, const float y, const float z) {
    scale=vector3f(x, y, z);
    updateMatrix();
}
void MatrixTransformer::addTranslation(const float x, const float y, const float z) {
    matrix4f translateMatrix;
    translateMatrix.initIdentity();
    translateMatrix.data[3]=x;
    translateMatrix.data[7]=y;
    translateMatrix.data[11]=z;
    translate=translate+vector3f(x, y, z);
    transformMatrix=translateMatrix*transformMatrix;
}
float* MatrixTransformer::getMatrixData() {
    return transformMatrix.data;
}
matrix4f MatrixTransformer::getMatrix() {
    return  transformMatrix;
}