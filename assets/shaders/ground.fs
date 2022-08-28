#version 460 core
out vec4 FragColor;

uniform sampler2D ObjColor;

void main() {
    // FragColor = vertexColor * (abs(time * 2 - 1)*0.75 + 0.25) ;
    FragColor = ObjColor;
};