//
// Created by leo on 21/12/22.
//

#ifndef TRASHENGINE_TEXTURE_HPP
#define TRASHENGINE_TEXTURE_HPP

#endif //TRASHENGINE_TEXTURE_HPP

class incorrectFilenameException : exception {
    const char * what() const noexcept override {
        return "incorrectFilenameException";
    }
};
class incorrectFileFormatException : exception {
    const char * what() const noexcept override {
        return "incorrectFileFormatException";
    }
};

class Texture {
    GLuint id;
public:
    //void loadTexture(const string& filename);
    Texture(const string& filename);
    GLuint getId();
    void setId(GLuint newId);
    void bind();
    void unbind();
};
GLuint Texture::getId() {
    return id;
}
void Texture::setId(GLuint newId) {
    id=newId;
}
Texture::Texture(const string& filename) {
    //BMP loading
    unsigned char header[54]; // Each BMP file begins by a 54-bytes header
    unsigned int dataPos;     // Position in the file where the actual data begins
    unsigned int width, height;
    unsigned int imageSize;   // = width*height*3
    // Actual RGB data
    unsigned char * data;
    FILE * file = fopen(filename.c_str(),"rb");
    if (!file){
        cout <<"Image could not be opened" << endl;
        throw incorrectFilenameException();
    }
    if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
        printf("Not a correct BMP file\n");
        throw incorrectFilenameException();
    }
    if ( header[0]!='B' || header[1]!='M' ){
        printf("Not a correct BMP file\n");
        throw incorrectFilenameException();
    }
    // Read ints from the byte array
    dataPos    = *(int*)&(header[0x0A]);
    imageSize  = *(int*)&(header[0x22]);
    width      = *(int*)&(header[0x12]);
    height     = *(int*)&(header[0x16]);
    // Some BMP files are misformatted, guess missing information
    if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
    if (dataPos==0)      dataPos=54; // The BMP header is done that way
    // Create a buffer
    data = new unsigned char [imageSize];

    // Read the actual data from the file into the buffer
    fread(data,1,imageSize,file);

    //Everything is in memory now, the file can be closed
    fclose(file);

    GLuint textureID;
    glGenTextures(1, &textureID);
    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    id=textureID;
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, id);
}
void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}