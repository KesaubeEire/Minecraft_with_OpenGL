#version 330 core
layout (location = 0) in vec3 vec_Pos;  // 位置变量
layout (location = 1) in vec3 vec_Col;  // 颜色变量
layout (location = 2) in vec2 aTexCoord;// 贴图变量

out vec4 vertexColor; // 为片段着色器指定一个颜色输出
out vec4 vertexPos;
uniform float xOffset;
uniform float yOffset;

out vec2 TexCoord;

void main()
{
    gl_Position = vec4(vec_Pos.x+xOffset,vec_Pos.y+yOffset,vec_Pos.z, 1.0); //
//    gl_Position = vec4(vec_Pos.x,vec_Pos.y,vec_Pos.z, 1.0); //
    vertexPos = gl_Position;
    vertexColor = vec4(vec_Col, 1.0); //
    TexCoord = aTexCoord;
}