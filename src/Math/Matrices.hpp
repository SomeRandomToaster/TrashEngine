//
// Created by leo on 29/10/22.
//

#ifndef TRASHENGINE_MATRICES_HPP
#define TRASHENGINE_MATRICES_HPP

#endif //TRASHENGINE_MATRICES_HPP

class IncorrectMatrixDataSizeException: public exception {
    const char * what() const noexcept override {
        return "Incorrect data size was given to matrix constructor/setter";
    }
};

class matrix4f {
public:
    float* data; //refactor me later
    matrix4f();
    matrix4f(const vector<float>& v);
    matrix4f(const vector<vector<float>>& v);
    matrix4f(const matrix4f& A);
    ~matrix4f();
    void initIdentity();
    vector <vector<float>> getData();
    void setData(vector<float>& v);
    void setData(vector<vector<float>>& v);
    matrix4f& operator=(const matrix4f& A);
    friend matrix4f operator* (const matrix4f& A, const matrix4f& B);
};
class matrix3f {
    float* data;
public:
    matrix3f();
    matrix3f(const vector<float>& v);
    matrix3f(const vector<vector<float>>& v);
    matrix3f(const matrix3f& A);
    ~matrix3f();
    void initIdentity();
    vector <vector<float>> getData() const;
    void setData(vector<float>& v);
    void setData(vector<vector<float>>& v);
    matrix3f& operator=(const matrix3f& A);
    friend matrix3f operator* (const matrix3f& A, const matrix3f& B);
};
matrix3f::matrix3f() {
    data=new float[9];
}
matrix3f::matrix3f(const vector<float>& v) {
    if(v.size()!=9) {
        cerr << "Error: trying to set matrix data from incorrect size vector" << endl;
        throw IncorrectMatrixDataSizeException();
    }
    data=new float[9];
    for(int i=0; i<9; i++) {
        data[i]=v[i];
    }
}
matrix3f::matrix3f(const vector<vector<float>>& v) {
    if(v.size()!=3) {
        cerr << "Error: trying to set matrix data from incorrect size vector" << endl;
        throw IncorrectMatrixDataSizeException();
    }
    for(int i=0; i<3; i++) {
        if(v[i].size()!=3) {
            cerr << "Error: trying to set matrix data from incorrect size vector" << endl;
            throw IncorrectMatrixDataSizeException();
        }
    }
    data=new float[9];
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            data[i*3+j]=v[i][j];
        }
    }
}
matrix3f::~matrix3f() {
    delete[] data;
}

void matrix3f::initIdentity() {
    data[0]=1; data[1]=0; data[2]=0;
    data[3]=0; data[4]=1; data[5]=0;
    data[6]=0; data[7]=0; data[8]=1;
}
vector <vector<float>> matrix3f::getData() const {
    vector<vector<float>> res(3, vector<float> (3));
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            res[i][j]=data[i*3+j];
        }
    }
    return res;
}
void matrix3f::setData(vector<float>& v) {
    if(v.size()!=9) {
        cerr << "Error: trying to set matrix data from incorrect size vector" << endl;
        throw IncorrectMatrixDataSizeException();
    }
    for(int i=0; i<9; i++) {
        data[i]=v[i];
    }
}
void matrix3f::setData(vector<vector<float>>& v) {
    if(v.size()!=3) {
        cerr << "Error: trying to set matrix data from incorrect size vector" << endl;
        throw IncorrectMatrixDataSizeException();
    }
    for(int i=0; i<3; i++) {
        if(v[i].size()!=3) {
            cerr << "Error: trying to set matrix data from incorrect size vector" << endl;
            throw IncorrectMatrixDataSizeException();
        }
    }
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            data[i*3+j]=v[i][j];
        }
    }
}

matrix3f operator* (const matrix3f& A, const matrix3f& B) {
    matrix3f ans;
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            float sum=0;
            for(int r=0; r<3; r++) {
                sum+=A.data[i*3+r]*B.data[r*3+j];
            }
            ans.data[i*3+j]=sum;
        }
    }
    return ans;
}
matrix3f::matrix3f(const matrix3f &A) {
    data=new float[9];
    for(int i=0; i<9; i++) {
        data[i]=A.data[i];
    }
}
matrix3f& matrix3f::operator=(const matrix3f& A) {
    for(int i=0; i<9; i++) {
        data[i]=A.data[i];
    }
    return *this;
}

matrix4f::matrix4f() {
    data=new float[16];
}
matrix4f::matrix4f(const vector<float>& v) {
    if(v.size()!=16) {
        cerr << "Error: trying to set matrix data from incorrect size vector" << endl;
        throw IncorrectMatrixDataSizeException();
    }
    data=new float[16];
    for(int i=0; i<16; i++) {
        data[i]=v[i];
    }
}
matrix4f::matrix4f(const vector<vector<float>>& v) {
    if(v.size()!=4) {
        cerr << "Error: trying to set matrix data from incorrect size vector" << endl;
        throw IncorrectMatrixDataSizeException();
    }
    for(int i=0; i<4; i++) {
        if(v[i].size()!=4) {
            cerr << "Error: trying to set matrix data from incorrect size vector" << endl;
            throw IncorrectMatrixDataSizeException();
        }
    }
    data=new float[16];
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            data[i*4+j]=v[i][j];
        }
    }
}
matrix4f::~matrix4f() {
    delete[] data;
}

void matrix4f::initIdentity() {
    data[0]=1; data[1]=0; data[2]=0; data[3]=0;
    data[4]=0; data[5]=1; data[6]=0; data[7]=0;
    data[8]=0; data[9]=0; data[10]=1; data[11]=0;
    data[12]=0; data[13]=0; data[14]=0; data[15]=1;
}
vector <vector<float>> matrix4f::getData() {
    vector<vector<float>> res(4, vector<float> (4));
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            res[i][j]=data[i*4+j];
        }
    }
    return res;
}
void matrix4f::setData(vector<float>& v) {
    if(v.size()!=16) {
        cerr << "Error: trying to set matrix data from incorrect size vector" << endl;
        throw IncorrectMatrixDataSizeException();
    }
    for(int i=0; i<16; i++) {
        data[i]=v[i];
    }
}
void matrix4f::setData(vector<vector<float>>& v) {
    if(v.size()!=4) {
        cerr << "Error: trying to set matrix data from incorrect size vector" << endl;
        throw IncorrectMatrixDataSizeException();
    }
    for(int i=0; i<4; i++) {
        if(v[i].size()!=4) {
            cerr << "Error: trying to set matrix data from incorrect size vector" << endl;
            throw IncorrectMatrixDataSizeException();
        }
    }
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            data[i*4+j]=v[i][j];
        }
    }
}

matrix4f operator* (const matrix4f& A, const matrix4f& B) {
    matrix4f ans;
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            float sum=0;
            for(int r=0; r<4; r++) {
                sum+=A.data[i*4+r]*B.data[r*4+j];
            }
            ans.data[i*4+j]=sum;
        }
    }
    return ans;
}
matrix4f::matrix4f(const matrix4f &A) {
    data=new float[16];
    for(int i=0; i<16; i++) {
        data[i]=A.data[i];
    }
}
matrix4f& matrix4f::operator=(const matrix4f& A) {
    for(int i=0; i<16; i++) {
        data[i]=A.data[i];
    }
    return *this;
}