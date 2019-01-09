#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
// 底色 光色
//    FragColor = vec4(lightColor * objectColor, 1.0);


// 底色 * 环境光
    // 计算环境颜色
    // Ambient : 直接乘一个 *常量环境因子* 作为底色
    float ambientStrength = 0.1; //*常量环境因子*
    vec3 ambient = ambientStrength * lightColor;

    // 合并结果
    // vec3 result = ambient * objectColor;
    // FragColor = vec4(result, 1.0);

// 底色 * (环境光照 + 漫反射)
    // 计算漫反射 :
    // [ 法线 | 光的向量 | 漫反射颜色在方向上的夹角 | 漫反射颜色 ]
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0); // 低于90度不要了
    vec3 diffuse = diff * lightColor;

    // 合并结果
    // vec3 result = (ambient + diffuse) * objectColor;
    // FragColor = vec4(result, 1.0);

    // 计算镜面反射 :
    // [ 镜面强度(Specular Intensity) | 视线方向 | 沿法线的反射向量 | 计算镜面分量]
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);// 32 是 镜面反射高光的反光度
    vec3 specular = specularStrength * spec * lightColor;

    // 合并结果
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}

//// Gouraud
//// Fragment shader:
//// ================
//#version 330 core
//out vec4 FragColor;
//
//in vec3 LightingColor;
//
//uniform vec3 objectColor;
//
//void main()
//{
//   FragColor = vec4(LightingColor * objectColor, 1.0);
//}
