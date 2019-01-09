#version 330 core
out vec4 FragColor;  // 输出的颜色
in vec4 vertexColor; // 从顶点着色器传来的输入变量（名称相同、类型相同）
in vec4 vertexPos;

in vec2 TexCoord;//EBO 的数据
uniform vec4 ourColor;


uniform float zoomOffset;
uniform float alphaOffset;


uniform sampler2D texture1;
uniform sampler2D texture2;
void main()
{
//    FragColor = vertexColor;
//    FragColor = ourColor;

//FragColor = vertexColor;

//FragColor = vertexPos;

//FragColor = texture(ourTexture,TexCoord);

//    FragColor = texture(texture1, TexCoord) * vec4(vertexColor);
    FragColor = mix(texture(texture1, vec2(TexCoord.x*(1+zoomOffset),TexCoord.y*(1+zoomOffset))), texture(texture2, vec2(-TexCoord.x,TexCoord.y)), alphaOffset);
}