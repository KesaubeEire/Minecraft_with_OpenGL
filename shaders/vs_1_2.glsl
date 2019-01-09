#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    FragPos = vec3(model * vec4(aPos, 1.0));

    // 防止aNormal因为非对称变化丢失发现正确方向 : 法线矩阵是变换矩阵的逆矩阵的转置矩阵
    Normal = mat3(transpose(inverse(model))) * aNormal;

    TexCoords = aTexCoords;
}