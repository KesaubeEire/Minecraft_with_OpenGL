// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../dependencies/shader.h"

#define STB_IMAGE_IMPLEMENTATION

#include "../dependencies/stb_image.h"


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
void processInput(GLFWwindow *window, float &valueX, float &valueY, float &valueZoom, float &valueAlpha)
{
    // 按下ESC -> 退出窗口
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // 按下空格 -> 重置窗口
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        valueX = 0;
        valueY = 0;
        valueZoom = 0;
        valueAlpha = 0;
    }

    // 按下WASD -> 调节位置
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        valueX -= 0.02f;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        valueX += 0.02f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        valueY += 0.02f;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        valueY -= 0.02f;

    // 按下QE -> 调节缩放
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        valueZoom -= 0.01f;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        valueZoom += 0.01f;

    // 按下 up down -> 调节Alpha
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        valueAlpha -= 0.01f;
        if (valueAlpha <= 0)
            valueAlpha = 0;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        valueAlpha += 0.01f;
        if (valueAlpha >= 1.0f)
            valueAlpha = 1.0f;
    }
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
//             ---- 位置 ----     ---- 颜色 ----   - 纹理坐标 -
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 2.0f,   // 右上
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 2.0f, 0.0f,   // 右下
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // 左下
            -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 2.0f    // 左上
    };

    unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };
//Feature:纹理坐标更新

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // .3. 设置顶点属性指针
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
//    glEnableVertexAttribArray(0);

// ⭕位置属性 : 以6个数为一个单位,从每个单位序号为0的数开始,每个单位抽3个
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);
// ⭕颜色属性 : 以6个数为一个单位,从每个单位序号为3的数开始,每个单位抽3个
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
// Feature:纹理属性顶点
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
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
    Shader shaderProgram("shaders/vs002.glsl",
                         "shaders/fs002.glsl");
    shaderProgram.use();
    glUniform1i(glGetUniformLocation(shaderProgram.ID, "texture1"), 0);
    glUniform1i(glGetUniformLocation(shaderProgram.ID, "texture2"), 1);
    // 创造Shader02
    Shader shaderProgram2("shaders/vs0021.glsl",
                          "shaders/fs002.glsl");
    shaderProgram2.use();
    glUniform1i(glGetUniformLocation(shaderProgram2.ID, "texture1"), 0);
    glUniform1i(glGetUniformLocation(shaderProgram2.ID, "texture2"), 1);


    // ✅运动变量
    float offset_X = 0;
    float offset_Y = 0;
    float offset_Zoom = 0;
    float offset_Alpha = 0;


    // 取消注释可以画线框图 : 应该是强制改变渲染模式为线框
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // ✅渲染循环
    while (!glfwWindowShouldClose(window))
    {

        // 输入检查
        processInput(window, offset_X, offset_Y, offset_Zoom, offset_Alpha);
        // 定义清空颜色值
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // 清空颜色
        glClear(GL_COLOR_BUFFER_BIT);


        //==========渲染指令==========//
        glActiveTexture(GL_TEXTURE0);//这是死的
        glBindTexture(GL_TEXTURE_2D, texture0);
        glActiveTexture(GL_TEXTURE1);//这是死的
        glBindTexture(GL_TEXTURE_2D, texture1);


        // NewFeature:矩阵
        glm::mat4 trans;

        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, (float) glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        GLint transformLoc = glGetUniformLocation(shaderProgram.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        // NewFeature:矩阵


        // ✅渲染着色器
        shaderProgram.use();

        shaderProgram.setFloat("xOffset", offset_X);
        shaderProgram.setFloat("yOffset", offset_Y);
        shaderProgram.setFloat("zoomOffset", offset_Zoom);
        shaderProgram.setFloat("alphaOffset", offset_Alpha);

        // ✅绘制物体
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        //==========渲染指令==========//

        // NewFeature:矩阵
        glm::mat4 trans2;
        trans2 = glm::translate(trans2, glm::vec3(-0.5f, +0.5f, 0.0f));
        glm::vec3 sinVec3 = glm::vec3(1.0f, 1.0f, 1.0f) * glm::abs(glm::sin(glm::vec3((float) glfwGetTime())));
        trans2 = glm::scale(trans2, sinVec3);
        GLint transformLoc2 = glGetUniformLocation(shaderProgram2.ID, "transform");
        glUniformMatrix4fv(transformLoc2, 1, GL_FALSE, glm::value_ptr(trans2));
        // NewFeature:矩阵


        shaderProgram2.use();
        shaderProgram2.setFloat("xOffset", offset_X);
        shaderProgram2.setFloat("yOffset", offset_Y);
        shaderProgram2.setFloat("zoomOffset", offset_Zoom);
        shaderProgram2.setFloat("alphaOffset", offset_Alpha);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);


        // 交换颜色缓冲
        glfwSwapBuffers(window);
        // 检查触发事件
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // ✅正确释放/删除之前的分配的所有资源
    glfwTerminate();


    return 0;
}


// 教程的
//
//void framebuffer_size_callback(GLFWwindow *window, int width, int height);
//
//void processInput(GLFWwindow *window);
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
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
//    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//    // glad: load all OpenGL function pointers
//    // ---------------------------------------
//    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//    // build and compile our shader zprogram
//    // ------------------------------------
//    Shader ourShader("shaders/vs0021.glsl", "shaders/fs002.glsl");
//
//    // set up vertex data (and buffer(s)) and configure vertex attributes
//    // ------------------------------------------------------------------
//    float vertices[] = {
//            // positions           // texture coords
//            0.5f, 0.5f, 0.0f, 1.0f, 1.0f, // top right
//            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
//            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
//            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f  // top left
//    };
//    unsigned int indices[] = {
//            0, 1, 3, // first triangle
//            1, 2, 3  // second triangle
//    };
//    unsigned int VBO, VAO, EBO;
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);
//
//    glBindVertexArray(VAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//    // position attribute
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
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
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
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
//    // render loop
//    // -----------
//    while (!glfwWindowShouldClose(window))
//    {
//        // input
//        // -----
//        processInput(window);
//
//        // render
//        // ------
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        // bind textures on corresponding texture units
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, texture1);
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, texture2);
//
//
//        glm::mat4 transform;
//        // first container
//        // ---------------
//        transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
//        transform = glm::rotate(transform, (float) glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
//        // get their uniform location and set matrix (using glm::value_ptr)
//        auto transformLoc = static_cast<unsigned int>(glGetUniformLocation(ourShader.ID, "transform"));
//        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
//
//        // with the uniform matrix set, draw the first container
//        glBindVertexArray(VAO);
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//        // second transformation
//        // ---------------------
//        transform = glm::mat4(); // reset it to an identity matrix
//        transform = glm::translate(transform, glm::vec3(-0.5f, 0.5f, 0.0f));
//        auto scaleAmount = static_cast<float>(sin(glfwGetTime()));
//        transform = glm::scale(transform, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
//        glUniformMatrix4fv(transformLoc, 1, GL_FALSE,
//                           &transform[0][0]); // this time take the matrix value array's first element as its memory pointer value
//
//        // now with the uniform matrix being replaced with new transformations, draw it again.
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
//    glDeleteBuffers(1, &EBO);
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