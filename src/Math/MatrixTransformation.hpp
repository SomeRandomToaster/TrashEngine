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
    matrix4f projectionMatrix;
    Camera camera;
    void updateMatrix();
public:
    void initProjection(const float fovAngle, const float screenWidth, const float screenHeight, const float zNear, const float zFar);
    void setTranslation(const float x, const float y, const float z);
    void setRotation(const float x, const float y, const float z);
    void setScale(const float x, const float y, const float z);
    void setCamera(const Camera& cam);
    void addTranslation(const float x, const float y, const float z);
    matrix4f transformMatrix;
    MatrixTransformer();
    float* getMatrixData();
    matrix4f getTransformation();
    matrix4f getProjectedTransformation();
};

MatrixTransformer::MatrixTransformer() :
    translate(0, 0, 0),
    rotate(0, 0, 0),
    scale(1, 1, 1)
    {
        projectionMatrix.initIdentity();
        transformMatrix.initIdentity();
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
    //transformMatrix=scaleMatrix*rotateXY*rotateXZ*rotateYZ*transformMatrix;
    //transformMatrix=projectionMatrix*transformMatrix;
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
matrix4f MatrixTransformer::getTransformation() {
    return  transformMatrix;
}
void MatrixTransformer::initProjection(const float fovAngle, const float screenWidth, const float screenHeight, const float zNear, const float zFar) {
    float screenRatio=screenWidth/screenHeight;
    float width=zNear*tan(fovAngle/2.0f)*screenRatio;
    float height=zNear*tan(fovAngle/2.0f);
    for(int i=0; i<16; i++) {
        projectionMatrix.data[i]=0;
    }
    projectionMatrix.data[0]=(2*zNear/width);
    projectionMatrix.data[5]=(2*zNear/height);
    projectionMatrix.data[10]=(zNear+zFar)/(zNear-zFar);
    projectionMatrix.data[11]=(2*zNear*zFar)/(zNear-zFar);
    projectionMatrix.data[14]=-1;
}
matrix4f MatrixTransformer::getProjectedTransformation() {
    //camera translation
    matrix4f cameraTranslation;
    cameraTranslation.initIdentity();
    cameraTranslation.data[3]=-camera.getPos().getX();
    cameraTranslation.data[7]=-camera.getPos().getY();
    cameraTranslation.data[11]=-camera.getPos().getZ();
    //camera rotation
    matrix4f cameraRotation;
    cameraRotation.initIdentity();
    vector3f r=camera.getRight().normalize();
    vector3f u=camera.getUp().normalize();
    vector3f f=camera.getForward().normalize();
    cameraRotation.data[0]=r.getX();
    cameraRotation.data[1]=r.getY();
    cameraRotation.data[2]=r.getZ();
    cameraRotation.data[4]=u.getX();
    cameraRotation.data[5]=u.getY();
    cameraRotation.data[6]=u.getZ();
    cameraRotation.data[8]=-f.getX();
    cameraRotation.data[9]=-f.getY();
    cameraRotation.data[10]=-f.getZ();
    //cout << camera.getForward().length() << endl
    //cout << dot(f, r) << " " << dot(u, r) << " " << dot(u, f) << endl;
    matrix4f cameraMatrix=cameraRotation*cameraTranslation;
    return projectionMatrix*cameraMatrix*transformMatrix;
}
void MatrixTransformer::setCamera(const Camera& cam) {
    camera=cam;
}