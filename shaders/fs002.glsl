#version 330 core
out vec4 FragColor;  // 输出的颜色
in vec4 vertexColor; // 从顶点着色器传来的输入变量（名称相同、类型相同）
in vec2 TexCoord;    //EBO 的数据

// 自定义 from cpp
uniform float zoomOffset;
uniform float alphaOffset;
// 贴图图 from cpp
uniform sampler2D texture1;
uniform sampler2D texture2;
void main()
{

    FragColor = mix(texture(texture1, vec2(TexCoord.x*(1+zoomOffset),TexCoord.y*(1+zoomOffset))), texture(texture2, vec2(-TexCoord.x,TexCoord.y)), alphaOffset);
}