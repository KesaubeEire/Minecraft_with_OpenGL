// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../dependencies/CMakeFiles/shader.h"

#define STB_IMAGE_IMPLEMENTATION

#include "../dependencies/CMakeFiles/stb_image.h"


// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


//region 常量区

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

//endregion

//region 功能函数声明

// 窗口改变回调函数
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// 输入检测
void processInput(GLFWwindow *window, float &valueX, float &valueY, float &valueU, float &valueV, float &valueW)
{
    // 按下ESC -> 退出窗口
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // 按下空格 -> 重置窗口
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        valueX = 0;
        valueY = 0;
        valueU = 0;
        valueV = 0;
    }

    // 按下方向键 -> 调节位置
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        valueX -= 0.02f;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        valueX += 0.02f;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        valueY += 0.02f;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        valueY -= 0.02f;


    // 按下WASD -> 调节位置
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        valueU += 0.02f;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        valueU -= 0.02f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        valueW += 0.02f;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        valueW -= 0.02f;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        valueV += 0.02f;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        valueV -= 0.02f;


    // 按下QE -> 调节缩放
//    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
//        valueZ -= 0.01f;
//        if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
//        valueZ += 0.01f;

    // 按下 up down -> 调节Alpha
}

//endregion

int main()
{
    // 初始化glfw
    glfwInit();

    // ✅定义宏观参数:
    //    OpenGL主版本号 3.x
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //    OpenGL副版本号 x.3 -> 合起来是3.3 -> 安装的是4.1就这么着吧
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //    核心模式(Core-profile)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //    Mac专用代码
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


    // ✅创建窗口对象
    //    窗口 width height title
    GLFWwindow *window = glfwCreateWindow
            (SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // ✅初始化GLAD
    //    在之前的教程中已经提到过，
    //    GLAD是用来管理OpenGL的函数指针的，
    //    所以在调用任何OpenGL的函数之前我们需要初始化GLAD。
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // ✅视口配置
    //    glViewport函数前两个参数控制窗口左下角的位置。
    //    第三个和第四个参数控制渲染窗口的宽度和高度（像素）。
    glViewport(0, 0, 800, 800);
    //    也可以将视口的维度设置为比GLFW的维度小，
    //    这样子之后所有的OpenGL渲染将会在一个更小的窗口中显示，
    //    这样子的话我们也可以将一些其它元素显示在OpenGL视口之外。

    // ✅注册回调函数
    //    注册窗口改变回调函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

//Feature:纹理坐标更新
    // ✅顶点输入
    float vertices[] = {
////            -- 位置 -3-      -- 颜色 -2-
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
    };

    // ✅物体位置输入
    glm::vec3 cubePositions[] = {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(2.0f, 5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f, 3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f, 2.0f, -2.5f),
            glm::vec3(1.5f, 0.2f, -1.5f),
            glm::vec3(-1.3f, 1.0f, -1.5f)
    };

//Feature:纹理坐标更新

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // .3. 设置顶点属性指针

// ⭕位置属性 : 以6个数为一个单位,从每个单位序号为0的数开始,每个单位抽3个
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);
// ⭕颜色属性 : 以6个数为一个单位,从每个单位序号为3的数开始,每个单位抽3个
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
// Feature:纹理属性顶点
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(2);



// Feature:纹理声明


    // load and create a texture
    // -------------------------
    unsigned int texture0, texture1;

    // texture 1
    // ---------
    glGenTextures(1, &texture0);
    // set the texture wrapping parameters
    glBindTexture(GL_TEXTURE_2D, texture0);
    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;

    // tell stb_image.h to flip loaded texture's on the y-axis.
    stbi_set_flip_vertically_on_load(true);

    unsigned char *data = stbi_load("resources/container.jpg", &width, &height,
                                    &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    // texture 2
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    GL_REPEAT);    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps

    data = stbi_load("resources/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    // 创造Shader01
    Shader shaderProgram("shaders/vs08.glsl", "shaders/fs08.glsl");
    shaderProgram.use();
    glUniform1i(glGetUniformLocation(shaderProgram.ID, "texture1"), 0);
    glUniform1i(glGetUniformLocation(shaderProgram.ID, "texture2"), 1);


    // ✅运动变量
    float offset_X = 0;
    float offset_Y = 0;
    float offset_Zoom = 0;
    float offset_Alpha = 0;

    float fov = 1;
    float aspect = 45;

    float cameraX, cameraY, cameraZ = 0;


    // 取消注释可以画线框图 : 应该是强制改变渲染模式为线框
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // 开启深度缓冲
    glEnable(GL_DEPTH_TEST);

    // ✅渲染循环
    while (!glfwWindowShouldClose(window))
    {

        // 输入检查
        processInput(window, fov, aspect, cameraX, cameraY, cameraZ);
        // 定义清空颜色值
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // 清空颜色缓冲 | 深度缓冲
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        //==========渲染指令==========//
        glActiveTexture(GL_TEXTURE0);//这是死的
        glBindTexture(GL_TEXTURE_2D, texture0);
        glActiveTexture(GL_TEXTURE1);//这是死的
        glBindTexture(GL_TEXTURE_2D, texture1);


        // NewFeature:坐标系统



        // NewFeature:坐标系统


        // ✅渲染着色器
        shaderProgram.use();

        shaderProgram.setFloat("xOffset", offset_X);
        shaderProgram.setFloat("yOffset", offset_Y);
        shaderProgram.setFloat("zoomOffset", offset_Zoom);
        shaderProgram.setFloat("alphaOffset", offset_Alpha);


        // ✅绘制物体
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++)
        {

            // local
            glm::mat4 trans;
            if (i <= 3)
            {

                trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
                trans = glm::rotate(trans, (float) glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
            }
            shaderProgram.setMat4("transform", trans);

            // model
            glm::mat4 model;
            // 在这里为不同的物体分配不同的位置
            model = glm::translate(model, cubePositions[i]);
            if (i <= 3)
            {
                float angle = 20.0f * i;
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            }
            shaderProgram.setMat4("model", model);

            // view
            glm::mat4 view;
            // 注意，我们将矩阵向我们要进行移动场景的反方向移动。
            view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
            view = glm::translate(view, glm::vec3(cameraX, cameraY, cameraZ));
            shaderProgram.setMat4("view", view);

            // projection
            glm::mat4 projection;
//            float fov = (float) SCR_WIDTH / SCR_HEIGHT;
            projection = glm::perspective(glm::radians(aspect * 10), fov, 0.1f, 100.0f);
            shaderProgram.setMat4("projection", projection);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glDrawArrays(GL_TRIANGLES, 0, 36);
        //==========渲染指令==========//


        // 交换颜色缓冲
        glfwSwapBuffers(window);
        // 检查触发事件
        glfwPollEvents();


    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // ✅正确释放/删除之前的分配的所有资源
    glfwTerminate();


    return 0;
}