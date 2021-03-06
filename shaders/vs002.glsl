#version 330 core
layout (location = 0) in vec3 aPos;  // 位置变量
layout (location = 1) in vec3 vec_Col;  // 颜色变量
layout (location = 2) in vec2 aTexCoord;// 贴图变量

out vec4 vertexColor; // 为片段着色器指定一个颜色输出
out vec2 TexCoord;    // EBO

// 自定义 from cpp
uniform float xOffset;
uniform float yOffset;

// 矩阵 from cpp
uniform mat4 transform;

void main()
{
    // 移动
//    gl_Position = vec4(aPos.x+xOffset,aPos.y+yOffset,aPos.z, 1.0);
     gl_Position = transform * vec4(aPos, 1.0f);

    // 着色
    vertexColor = vec4(vec_Col, 1.0);

    // 输出EBO
//    TexCoord = aTexCoord;
  TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
}