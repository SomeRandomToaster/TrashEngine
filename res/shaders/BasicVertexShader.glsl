#version 330 core
    layout (location=0) in vec3 position;
    layout (location=1) in vec2 texCoord;
    uniform mat4 transformMatrix;
    out vec2 texCoord0;
    void main()
    {
        //color=vec4(clamp(position, 0.0, 1.0), 1.0);
        //color=vec4(texCoord.x, texCoord.y, 0, 0);
        texCoord0=texCoord;
        gl_Position = vec4(position, 1.0)*transformMatrix;
    }