#version 330 core
    layout (location=0) in vec3 position;
    layout (location=1) in vec2 texCoord;
    layout (location=2) in vec3 normal;
    uniform mat4 transformMatrix;
    out vec3 pos0;
    out vec2 texCoord0;
    out vec3 normal0;
    void main()
    {
        //color=vec4(clamp(position, 0.0, 1.0), 1.0);
        //color=vec4(texCoord.x, texCoord.y, 0, 0);
        pos0=position;
        texCoord0=texCoord;
        normal0=normal;
        gl_Position = vec4(position, 1.0)*transformMatrix;
    }