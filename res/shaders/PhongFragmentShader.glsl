#version 330 core
in vec2 texCoord0;
in vec3 normal0;
in vec3 pos0;
out vec4 fragColor;
uniform sampler2D sampler;
uniform vec3 baseColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform float baseLightIntensity;
uniform float diffuseLightIntensity;
uniform float specularLightIntensity;
uniform vec3 specularLightColor;
float notNeg(float x);
void main(){
    vec3 pos=pos0;
    vec3 normal=normalize(normal0);
    vec3 toLight=normalize(lightPos-pos);
    vec3 lRef=2*dot(toLight, normal)*normal-toLight;

    vec3 color = baseLightIntensity*baseColor;
    color += diffuseLightIntensity*notNeg(dot(toLight, normal))*lightColor;
    color += specularLightIntensity*pow(notNeg(dot(-normal, lRef)), 15.0)*specularLightColor;

    fragColor=texture2D(sampler, texCoord0.xy)*vec4(color, 1);
    //fragColor=vec4(color, 1);
}

float notNeg(float x) {
    if(x>=0.0)
        return x;
    else
        return 0.0;
}

