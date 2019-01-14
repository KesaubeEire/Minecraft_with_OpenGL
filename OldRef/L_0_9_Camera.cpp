// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../dependencies/CMakeFiles/shader.h"

#define STB_IMAGE_IMPLEMENTATION

#include "../dependencies/CMakeFiles/stb_image.h"
#include "../dependencies/CMakeFiles/Camera.h"


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

////region Self
//
//
////region 常量 变量 区
//
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 800;
//
//
//// ✅运动变量
//float offset_X = 0;
//float offset_Y = 0;
//float offset_Zoom = 0;
//float offset_Alpha = 0;
//
//// 两个角度
//float fov = 1;
//float aspect = 45;
//
//// 位置和缓存位置
//float cameraX = 0, cameraY = 0, cameraZ = -3;
//float cameraXtmp = 0, cameraYtmp = 0, cameraZtmp = 0;
//
//// 三个本地轴
//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
//glm::vec3 cameraRight = glm::vec3(cameraFront * cameraUp);
//glm::vec3 cameraPos = glm::vec3(cameraX, cameraY, cameraZ);
//
//// DeltaTime 帧时间
//float deltaTime = 0.0f; // 当前帧与上一帧的时间差
//float lastFrame = 0.0f; // 上一帧的时间
//
////endregion
//
////region 功能函数声明
//
//// 窗口改变回调函数
//void framebuffer_size_callback(GLFWwindow *window, int width, int height)
//{
//    glViewport(0, 0, width, height);
//}
//
//// 输入检测
//void processInput(GLFWwindow *window, float &valueX, float &valueY, float &valueU, float &valueV, float &valueW)
//{
//    // 按下ESC -> 退出窗口
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//
//    // 按下空格 -> 重置窗口
//    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
//    {
//        valueX = 0;
//        valueY = 0;
//        valueU = 0;
//        valueV = 0;
//    }
//
//    // 按下方向键 -> 调节摄像机的 fov 和 scale
//    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
//        valueX -= 0.02f;
//    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
//        valueX += 0.02f;
//    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
//        valueY += 0.02f;
//    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
//        valueY -= 0.02f;
//
//
//    // 按下WASD -> 调节位置
////    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
////        valueU += 0.02f;
////    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
////        valueU -= 0.02f;
////    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
////        valueW += 0.02f;
////    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
////        valueW -= 0.02f;
////    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
////        valueV += 0.02f;
////    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
////        valueV -= 0.02f;
//}
//
//void processInput2(GLFWwindow *window)
//{
//    // adjust accordingly
//    float cameraSpeed = 0.05f;
//
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//        cameraPos += cameraSpeed * cameraFront;
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//        cameraPos -= cameraSpeed * cameraFront;
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//}
//
////endregion
//
//int main()
//{
//    // 初始化glfw
//    glfwInit();
//
//    // ✅定义宏观参数:
//    //    OpenGL主版本号 3.x
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    //    OpenGL副版本号 x.3 -> 合起来是3.3 -> 安装的是4.1就这么着吧
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    //    核心模式(Core-profile)
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    //    Mac专用代码
//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//
//
//    // ✅创建窗口对象
//    //    窗口 width height title
//    GLFWwindow *window = glfwCreateWindow
//            (SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
//    if (window == nullptr)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//
//    // ✅初始化GLAD
//    //    在之前的教程中已经提到过，
//    //    GLAD是用来管理OpenGL的函数指针的，
//    //    所以在调用任何OpenGL的函数之前我们需要初始化GLAD。
//    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//    // ✅视口配置
//    //    glViewport函数前两个参数控制窗口左下角的位置。
//    //    第三个和第四个参数控制渲染窗口的宽度和高度（像素）。
//    glViewport(0, 0, 800, 800);
//    //    也可以将视口的维度设置为比GLFW的维度小，
//    //    这样子之后所有的OpenGL渲染将会在一个更小的窗口中显示，
//    //    这样子的话我们也可以将一些其它元素显示在OpenGL视口之外。
//
//    // ✅注册回调函数
//    //    注册窗口改变回调函数
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
////Feature:纹理坐标更新
//    // ✅顶点输入
//    float vertices[] = {
//////            -- 位置 -3-      -- 颜色 -2-
//            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
//            0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
//            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
//            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
//
//            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
//            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
//            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
//            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
//            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//
//            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//            -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//
//            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//            0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//
//            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//            0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
//            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
//            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
//            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//
//            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
//            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
//            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
//    };
//
//    // ✅物体位置输入
//    glm::vec3 cubePositions[] = {
//            glm::vec3(0.0f, 0.0f, 0.0f),
//            glm::vec3(2.0f, 5.0f, -15.0f),
//            glm::vec3(-1.5f, -2.2f, -2.5f),
//            glm::vec3(-3.8f, -2.0f, -12.3f),
//            glm::vec3(2.4f, -0.4f, -3.5f),
//            glm::vec3(-1.7f, 3.0f, -7.5f),
//            glm::vec3(1.3f, -2.0f, -2.5f),
//            glm::vec3(1.5f, 2.0f, -2.5f),
//            glm::vec3(1.5f, 0.2f, -1.5f),
//            glm::vec3(-1.3f, 1.0f, -1.5f)
//    };
//
////Feature:纹理坐标更新
//
//    unsigned int VBO, VAO;
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//
//    glBindVertexArray(VAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
////    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
////    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//    // .3. 设置顶点属性指针
//
//// ⭕位置属性 : 以6个数为一个单位,从每个单位序号为0的数开始,每个单位抽3个
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) nullptr);
//    glEnableVertexAttribArray(0);
//// ⭕颜色属性 : 以6个数为一个单位,从每个单位序号为3的数开始,每个单位抽3个
////    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
////    glEnableVertexAttribArray(1);
//
//// Feature:纹理属性顶点
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
//    glEnableVertexAttribArray(2);
//// Feature:纹理声明
//
//
//    // load and create a texture
//    // -------------------------
//    unsigned int texture0, texture1;
//
//    // texture 1
//    // ---------
//    glGenTextures(1, &texture0);
//    // set the texture wrapping parameters
//    glBindTexture(GL_TEXTURE_2D, texture0);
//    // set texture wrapping to GL_REPEAT (default wrapping method)
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    // set texture filtering parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    // load image, create texture and generate mipmaps
//    int width, height, nrChannels;
//
//    // tell stb_image.h to flip loaded texture's on the y-axis.
//    stbi_set_flip_vertically_on_load(true);
//
//    unsigned char *data = stbi_load("resources/container.jpg", &width, &height,
//                                    &nrChannels, 0);
//    if (data)
//    {
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }
//    else
//    {
//        std::cout << "Failed to load texture" << std::endl;
//    }
//    stbi_image_free(data);
//
//
//    // texture 2
//    // ---------
//    glGenTextures(1, &texture1);
//    glBindTexture(GL_TEXTURE_2D, texture1);
//    // set the texture wrapping parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
//                    GL_REPEAT);    // set texture wrapping to GL_REPEAT (default wrapping method)
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    // set texture filtering parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    // load image, create texture and generate mipmaps
//
//    data = stbi_load("resources/awesomeface.png", &width, &height, &nrChannels, 0);
//    if (data)
//    {
//        // note that the awesomeface.png has transparency and thus an alpha channel,
//        // so make sure to tell OpenGL the data type is of GL_RGBA
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }
//    else
//    {
//        std::cout << "Failed to load texture" << std::endl;
//    }
//    stbi_image_free(data);
//
//
//    // 创造Shader01
//    Shader shaderProgram("shaders/vs08.glsl", "shaders/fs08.glsl");
//    shaderProgram.use();
//    glUniform1i(glGetUniformLocation(shaderProgram.ID, "texture1"), 0);
//    glUniform1i(glGetUniformLocation(shaderProgram.ID, "texture2"), 1);
//
//
//
//
//
//    // 取消注释可以画线框图 : 应该是强制改变渲染模式为线框
//    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//    // 开启深度缓冲
//    glEnable(GL_DEPTH_TEST);
//
//    // ✅渲染循环
//    while (!glfwWindowShouldClose(window))
//    {
//        // 输入检查
//        processInput(window, fov, aspect, cameraX, cameraY, cameraZ);
//        processInput2(window);
//        // 定义清空颜色值
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        // 清空颜色缓冲 | 深度缓冲
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        //==========渲染指令==========//
//        glActiveTexture(GL_TEXTURE0);//这是死的
//        glBindTexture(GL_TEXTURE_2D, texture0);
//        glActiveTexture(GL_TEXTURE1);//这是死的
//        glBindTexture(GL_TEXTURE_2D, texture1);
//
//        // ✅渲染着色器
//        shaderProgram.use();
//
//        shaderProgram.setFloat("xOffset", offset_X);
//        shaderProgram.setFloat("yOffset", offset_Y);
//        shaderProgram.setFloat("zoomOffset", offset_Zoom);
//        shaderProgram.setFloat("alphaOffset", offset_Alpha);
//
//        // 帧时间
////        float currentFrame = glfwGetTime();
////        deltaTime = currentFrame - lastFrame;
////        lastFrame = currentFrame;
//
//        // ✅绘制物体
//        glBindVertexArray(VAO);
//        for (unsigned int i = 0; i < 10; i++)
//        {
//            // local
//            glm::mat4 trans;
//            if (i <= 3)
//            {
//                trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
//                trans = glm::rotate(trans, (float) glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
//            }
//            shaderProgram.setMat4("transform", trans);
//
//            // model
//            glm::mat4 model;
//            // 在这里为不同的物体分配不同的位置
//            model = glm::translate(model, cubePositions[i]);
//            if (i <= 3)
//            {
//                float angle = 20.0f * i;
//                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//            }
//            shaderProgram.setMat4("model", model);
//
//
//            // NewFeature:Camera系统
//            // view
//            if (cameraPos.x != cameraXtmp || cameraPos.y != cameraYtmp || cameraPos.z != cameraZtmp)
//            {
//                std::cout << "Camera Position: x:" << cameraX << " y:" << cameraY << " z:" << cameraZ
//                          << std::endl;
//                cameraPos.x = cameraX;
//                cameraPos.y = cameraY;
//                cameraPos.z = cameraZ;
//            }
//            glm::mat4 view;
//            view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
//
//
//            // glm::LookAt函数需要一个位置、目标和上向量。
//            shaderProgram.setMat4("view", view);
//            // NewFeature:Camera系统8
//
//            // projection
//            glm::mat4 projection;
////            float fov = (float) SCR_WIDTH / SCR_HEIGHT;
//            projection = glm::perspective(glm::radians(aspect * 10), fov, 0.1f, 100.0f);
//            shaderProgram.setMat4("projection", projection);
//
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//        }
//
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        //==========渲染指令==========//
//
//
//        // 交换颜色缓冲
//        glfwSwapBuffers(window);
//        // 检查触发事件
//        glfwPollEvents();
//
//
//    }
//
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//
//    // ✅正确释放/删除之前的分配的所有资源
//    glfwTerminate();
//
//
//    return 0;
//}
//
////endregion

////region 教程
//
//// 回调函数
//// 窗口|键盘|鼠标|滚轮
//void framebuffer_size_callback(GLFWwindow *window, int width, int height);
//
//void processInput(GLFWwindow *window);
//
//void mouse_callback(GLFWwindow *window, double xpos, double ypos);
//
//void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
//
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//// camera
//float fov = 45;
//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
//
//// Eular Angle
//glm::float32 pitch;
//glm::float32 roll;
//glm::float32 yaw;
//glm::vec3 direction;
//
//
//// timing
//float deltaTime = 0.0f;    // time between current frame and last frame
//float lastFrame = 0.0f;
//
//int main()
//{
//    // glfw: initialize and configure
//    // ------------------------------
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
//#endif
//
//    // glfw window creation
//    // --------------------
//    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
//    if (window == nullptr)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//
//    // 回调函数:窗口|键盘|鼠标|滚轮
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//    glfwSetCursorPosCallback(window, mouse_callback);
//    glfwSetScrollCallback(window, scroll_callback);
//
//    // glad: load all OpenGL function pointers
//    // ---------------------------------------
//    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//    // configure global opengl state
//    // -----------------------------
//    glEnable(GL_DEPTH_TEST);
//
//    // build and compile our shader zprogram
//    // ------------------------------------
//    Shader ourShader("shaders/vs09.glsl", "shaders/fs09.glsl");
//
//    // set up vertex data (and buffer(s)) and configure vertex attributes
//    // ------------------------------------------------------------------
//    float vertices[] = {
//            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
//            0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
//            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
//            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
//
//            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
//            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
//            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
//            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
//            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//
//            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//            -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//
//            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//            0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//
//            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//            0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
//            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
//            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
//            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//
//            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
//            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
//            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
//    };
//    // world space positions of our cubes
//    glm::vec3 cubePositions[] = {
//            glm::vec3(0.0f, 0.0f, 0.0f),
//            glm::vec3(2.0f, 5.0f, -15.0f),
//            glm::vec3(-1.5f, -2.2f, -2.5f),
//            glm::vec3(-3.8f, -2.0f, -12.3f),
//            glm::vec3(2.4f, -0.4f, -3.5f),
//            glm::vec3(-1.7f, 3.0f, -7.5f),
//            glm::vec3(1.3f, -2.0f, -2.5f),
//            glm::vec3(1.5f, 2.0f, -2.5f),
//            glm::vec3(1.5f, 0.2f, -1.5f),
//            glm::vec3(-1.3f, 1.0f, -1.5f)
//    };
//    unsigned int VBO, VAO;
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//
//    glBindVertexArray(VAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    // position attribute
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) nullptr);
//    glEnableVertexAttribArray(0);
//    // texture coord attribute
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//
//
//    // load and create a texture
//    // -------------------------
//    unsigned int texture1, texture2;
//    // texture 1
//    // ---------
//    glGenTextures(1, &texture1);
//    glBindTexture(GL_TEXTURE_2D, texture1);
//    // set the texture wrapping parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    // set texture filtering parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    // load image, create texture and generate mipmaps
//    int width, height, nrChannels;
//    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
//    unsigned char *data = stbi_load("resources/container.jpg", &width, &height, &nrChannels, 0);
//
//
//    if (data)
//    {
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }
//    else
//    {
//        std::cout << "Failed to load texture" << std::endl;
//    }
//    stbi_image_free(data);
//    // texture 2
//    // ---------
//    glGenTextures(1, &texture2);
//    glBindTexture(GL_TEXTURE_2D, texture2);
//    // set the texture wrapping parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    // set texture filtering parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    // load image, create texture and generate mipmaps
//    data = stbi_load("resources/awesomeface.png", &width, &height, &nrChannels, 0);
//    if (data)
//    {
//        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }
//    else
//    {
//        std::cout << "Failed to load texture" << std::endl;
//    }
//    stbi_image_free(data);
//
//    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
//    // -------------------------------------------------------------------------------------------
//    ourShader.use();
//    ourShader.setInt("texture1", 0);
//    ourShader.setInt("texture2", 1);
//
//
//
//    // Camera parameters
//    // 译注：direction代表摄像机的前轴(Front)，这个前轴是和本文第一幅图片的第二个摄像机的方向向量是相反的
////    direction.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
////    direction.y = sin(glm::radians(pitch));
////    direction.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
//
//    // render loop
//    // -----------
//    while (!glfwWindowShouldClose(window))
//    {
//        // per-frame time logic
//        // --------------------
//        float currentFrame = glfwGetTime();
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//
//        // input
//        // -----jianpan s
//        processInput(window);
//        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//        // render
//        // ------
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        // bind textures on corresponding texture units
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, texture1);
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, texture2);
//
//        // activate shader
//        ourShader.use();
//
//        // camera/view transformation
//        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
//        ourShader.setMat4("view", view);
//
//        // pass projection matrix to shader (as projection matrix rarely changes there's no need to do this per frame)
//        // -----------------------------------------------------------------------------------------------------------
////    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.0f);
//        glm::mat4 projection = glm::perspective(glm::radians(fov), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f,
//                                                100.0f);
//        ourShader.setMat4("projection", projection);
//
//        // render boxes
//        glBindVertexArray(VAO);
//        for (unsigned int i = 0; i < 10; i++)
//        {
//            // calculate the model matrix for each object and pass it to shader before drawing
//            glm::mat4 model;
//            model = glm::translate(model, cubePositions[i]);
//            float angle = 20.0f * i;
//            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//            ourShader.setMat4("model", model);
//
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//        }
//
//        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//        // -------------------------------------------------------------------------------
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    // optional: de-allocate all resources once they've outlived their purpose:
//    // ------------------------------------------------------------------------
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//
//    // glfw: terminate, clearing all previously allocated GLFW resources.
//    // ------------------------------------------------------------------
//    glfwTerminate();
//    return 0;
//}
//
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
//void processInput(GLFWwindow *window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//
//    float cameraSpeed = 2.5 * deltaTime;
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//        cameraPos += cameraSpeed * cameraFront;
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//        cameraPos -= cameraSpeed * cameraFront;
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
//        cameraPos -= glm::normalize(cameraUp) * cameraSpeed;
//    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
//        cameraPos += glm::normalize(cameraUp) * cameraSpeed;
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow *window, int width, int height)
//{
//    // make sure the viewport matches the new window dimensions; note that width and
//    // height will be significantly larger than specified on retina displays.
//    glViewport(0, 0, width, height);
//}
//
//// mousu_move_Callback
//float lastX = 400, lastY = 300;
//bool firstMouse = true;
//
//void mouse_callback(GLFWwindow *window, double xpos, double ypos)
//{
//
////    // 防止第一次进入跳
////    if (firstMouse)
////    {
////        lastX = xpos;
////        lastY = ypos;
////        firstMouse = false;
////    }
////
//////    在处理FPS风格摄像机的鼠标输入的时候，我们必须在最终获取方向向量之前做下面这几步：
//////    - 计算鼠标距上一帧的偏移量。
//////    - 把偏移量添加到摄像机的俯仰角和偏航角中。
//////    - 对偏航角和俯仰角进行最大和最小值的限制。
//////    - 计算方向向量。
////    float xoffset = xpos - lastX;
////    float yoffset = lastY - ypos; // 注意这里是相反的，因为y坐标是从底部往顶部依次增大的
////    lastX = xpos;
////    lastY = ypos;
////
////    float sensitivity = 0.05;
////    xoffset *= sensitivity;
////    yoffset *= sensitivity;
////
////    yaw += xoffset;
////    pitch += yoffset;
////
////    if (pitch > 89.0f)
////        pitch = 89.0f;
////    if (pitch < -89.0f)
////        pitch = -89.0f;
////
////    glm::vec3 front;
////    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
////    front.y = sin(glm::radians(pitch));
////    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
////    cameraFront = glm::normalize(front);
//
//
//    if (firstMouse)
//    {
//        lastX = xpos;
//        lastY = ypos;
//        firstMouse = false;
//    }
//
//    float xoffset = xpos - lastX;
//    float yoffset = lastY - ypos;
//    lastX = xpos;
//    lastY = ypos;
//
//    float sensitivity = 0.05;
//    xoffset *= sensitivity;
//    yoffset *= sensitivity;
//
//    yaw += xoffset;
//    pitch += yoffset;
//
//    if (pitch > 89.0f)
//        pitch = 89.0f;
//    if (pitch < -89.0f)
//        pitch = -89.0f;
//
//    glm::vec3 front;
//    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//    front.y = sin(glm::radians(pitch));
//    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//    cameraFront = glm::normalize(front);
//}
//
//
//void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
//{
//    if (fov >= 1.0f && fov <= 45.0f)
//        fov -= yoffset;
//    if (fov <= 1.0f)
//        fov = 1.0f;
//    if (fov >= 45.0f)
//        fov = 45.0f;
//}
////endregion

//region 教程最终 -> 使用Camera类进行操作

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
double lastX = SCR_WIDTH / 2.0f;
double lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float currentFrame;
float lastFrame;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("shaders/vs09.glsl", "shaders/fs09.glsl");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
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
    // world space positions of our cubes
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
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // load and create a texture
    // -------------------------
    unsigned int texture1, texture2;
    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char *data = stbi_load("resources/container.jpg", &width, &height, &nrChannels, 0);
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
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load("resources/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        currentFrame = (float) glfwGetTime(); // 获取游戏运行时间
        deltaTime = currentFrame - lastFrame; // 每帧计算运行时间差 算得每帧时间
        lastFrame = currentFrame;
        std::cout << "FPS:\t" << (int) (1 / deltaTime) << std::endl;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // activate shader
        ourShader.use();

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f,
                                                100.0f);
        ourShader.setMat4("projection", projection);

        // render boxes
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model;
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            ourShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard_Move(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard_Move(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard_Move(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard_Move(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
//endregion



