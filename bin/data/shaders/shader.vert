#version 150

// What we send out (to our frag shader)
out vec3 vecNormal;
out vec3 vecPosition;

// available attributes using programmable renderer
in vec4 position;
in vec4 color;
in vec4 normal;
in vec2 texcoord;

// these are passed in from OF programmable renderer
uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
// Honestly? not quite sure what these are
uniform mat4 textureMatrix;
uniform mat4 normalMatrix;

void main(){
    vecNormal = normal.xzy;
    vec4 pos = position;
    vecPosition = pos.xyz;
    gl_Position = modelViewProjectionMatrix * pos;
}
