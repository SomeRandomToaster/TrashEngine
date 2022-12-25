#version 330 core
in vec2 texCoord0;
out vec4 fragColor;
uniform sampler2D sampler;
uniform vec3 color;
void main(){
    //fragColor = vec4(0.0, 1.0, 1.0, 1.0);
    fragColor=texture2D(sampler, texCoord0.xy)*vec4(color, 1);
}

