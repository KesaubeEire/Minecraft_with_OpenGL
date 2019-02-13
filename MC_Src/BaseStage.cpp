// Self Made
#define STB_IMAGE_IMPLEMENTATION
#include "../dependencies/selfmade/shader.h"
#include "../dependencies/selfmade/stb_image.h"
#include "../dependencies/selfmade/Camera.h"
#include "../dependencies/selfmade/filesystem.h"
#include "map_generate/map_generate.h"

// Standard Headers
#include <map>
#include <string>
#include <iostream>
#include <sstream>

// GL Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#pragma region 字体渲染
// #include <ft2build.h>
// #include FT_FREETYPE_H
// #include <freetype/ftglyph.h>
// #include <freetype/freetype.h>
#include "../dependencies/freetype/freetype.h"
#pragma endregion

// 回调操作:窗口 | 鼠标 | 滚轮 | 键盘
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
// 加载材质
unsigned int loadTexture(char const *path);

// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

// camera
Camera camera(glm::vec3(15, 30, 15), glm::vec3(0.0f, 1.0f, 0.0f), -90, -80); //这里改成80度防止万向节死锁
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float ShownTime = 0.0f;
string fpsNum;

// cursor
bool isCursorHidden;
// log
bool isLogShown = true;
/////////////////////////////// --1--Log String Worker
struct LogString
{
    // 内容核心
    string content;
    // 临时变量
    string tmp;
    // stringstream
    std::stringstream tmpStream;

    // 求内容时用
    string Str()
    {
        return content;
    }

    // // 加入
    template <typename T>
    void append(T word)
    {
        tmpStream << word;
        tmpStream >> tmp;

        content += tmp;

        tmpStream.clear();
        tmp.clear();
    }
    void addStr(string word = " ")
    {
        content += word;
    }

    void clear()
    {
        content.clear();
    }
};
/////////////////////////////// --1--Log String Worker

/////////////////////////////// --2--Texture Renderer

/// Holds all state information relevant to
/// a character as loaded using FreeType
struct Character
{
    GLuint TextureID;   // ID handle of the glyph texture
    glm::ivec2 Size;    // Size of glyph
    glm::ivec2 Bearing; // Offset from baseline to left/top of glyph
    GLuint Advance;     // Horizontal offset to advance to next glyph
};
std::map<GLchar, Character> Characters;

GLuint textVAO, textVBO;

void RenderText(Shader &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

/////////////////////////////// --2--Texture Renderer

/////////////////////////////// --3--Block Renderer
struct BlockRenderer
{
    unsigned int Texture_top;
    unsigned int Texture_side;
    unsigned int Texture_bot;

    BlockRenderer(string topStr, string sideStr, string botStr)
    {
        Texture_top = loadTexture(FileSystem::getPath(topStr).c_str());
        Texture_side = loadTexture(FileSystem::getPath(sideStr).c_str());
        Texture_bot = loadTexture(FileSystem::getPath(botStr).c_str());
    }

    void Render()
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Texture_top);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, Texture_side);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, Texture_bot);
    }
};
/////////////////////////////// --3--Block Renderer

int main()
{

    // Step1_初始化窗口
#pragma region
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
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "MineCraft_OpenGL", nullptr, nullptr);
    if (window == nullptr)
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
    isCursorHidden = true;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
#pragma endregion

    // Step1.5_全局配置
    // -----------------------------
    // 启用深度测试。根据坐标的远近自动隐藏被遮住的图形（材料）
    glEnable(GL_DEPTH_TEST);

    // 启用颜色混合。例如实现半透明效果
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 根据函数glCullFace要求启用隐藏图形材料的面。
    // 启用剔除 | 剔除向后的面 | 顺时针剔除(逆时针为正面)
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    // Step2_生成基础小块
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // 单位Block的内部Hierarchy生成
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // normals           // texture coords
        // 前
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,  //右下
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, //左下
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,   //右上
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,   //右上
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, //左下
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,  //左上

        // 后
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        // 左
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, //右下
        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,   //左上
        -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  //右上
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, //右下
        -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  //左下
        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,   //左上

        // 右
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   //右上
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, //左下
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  //左上
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   //右上
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  //右下
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, //左下

        // 下
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

        // 上
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f};

    //Texure的流程:
    // first, configure the cube's VAO (and VBO)
    unsigned int cubeVBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindVertexArray(cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Step3_生成基本Shader
    // build and compile our shader zprogram
    // ------------------------------------
    Shader Shader_Block_Grass("MC_Shaders/vs_block001.glsl", "MC_Shaders/fs_block001.glsl");

    // ----------- diffuseMap ----------- //

    // unsigned int diffuseMap_top = loadTexture(FileSystem::getPath("MC_Resources/Textures/grass_block_top.png").c_str());
    // unsigned int diffuseMap_side = loadTexture(FileSystem::getPath("MC_Resources/Textures/grass_block_side.png").c_str());
    // unsigned int diffuseMap_bottom = loadTexture(FileSystem::getPath("MC_Resources/Textures/coarse_dirt.png").c_str());

    BlockRenderer block_GrassSoil(
        "MC_Resources/Textures/grass_block_top.png",
        "MC_Resources/Textures/grass_block_side.png",
        "MC_Resources/Textures/coarse_dirt.png");
    BlockRenderer block_Soli(
        "MC_Resources/Textures/coarse_dirt.png",
        "MC_Resources/Textures/coarse_dirt.png",
        "MC_Resources/Textures/coarse_dirt.png");
    BlockRenderer block_Stone(
        "MC_Resources/Textures/stone.png",
        "MC_Resources/Textures/stone.png",
        "MC_Resources/Textures/stone.png");
    // ----------- diffuseMap ----------- //

    // shader configuration
    // --------------------
    Shader_Block_Grass.use();
    Shader_Block_Grass.setInt("material.diffuse_t", 0);
    Shader_Block_Grass.setInt("material.diffuse_s", 1);
    Shader_Block_Grass.setInt("material.diffuse_b", 2);

//TODO:暂时放弃MC_debug_line
#pragma region
// // Step3.5_生成debug方向
// float debug_line_vertices[] = {
//     // pos   // color
//     0.8, 0, 0, 1, 0, 0,
//     1.0, 0, 0, 1, 0, 0,
//     0, 0, 0, 1, 0, 0,
//     0, 0.8, 0, 0, 1, 0,
//     0, 1.0, 0, 0, 1, 0,
//     0, 0, 0, 0, 1, 0,
//     0, 0, 0.8, 0, 0, 1,
//     0, 0, 1, 0, 0, 1,
//     0, 0, 0, 0, 0, 1};

// unsigned int debug_line_VBO, dubug_line_VAO;
// glGenVertexArrays(1, &dubug_line_VAO);
// glGenBuffers(1, &debug_line_VBO);

// glBindBuffer(GL_ARRAY_BUFFER, debug_line_VBO);
// glBufferData(GL_ARRAY_BUFFER, sizeof(debug_line_vertices), debug_line_vertices, GL_STATIC_DRAW);
// glBindVertexArray(dubug_line_VAO);

// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
// glEnableVertexAttribArray(0);
// glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
// glEnableVertexAttribArray(1);

// Shader Shader_debug_line("MC_Shaders/vs_debugline.glsl", "MC_Shaders/fs_debugline.glsl");
#pragma endregion

    // Step4_生成文本
#pragma region 生成文本
    // Compile and setup the shader
    Shader Shader_Font("MC_Shaders/fontsShaders/text_vs.glsl", "MC_Shaders/fontsShaders/text_fs.glsl");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(SCR_WIDTH), 0.0f, static_cast<GLfloat>(SCR_HEIGHT));
    Shader_Font.use();
    glUniformMatrix4fv(glGetUniformLocation(Shader_Font.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    // FreeType
    FT_Library ft;
    // All functions return a value different than 0 whenever an error occurred
    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

    // Load font as face
    FT_Face face;
    if (FT_New_Face(ft, "MC_Resources/fonts/Monaco_Linux.ttf", 0, &face))
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

    // Set size to load glyphs as
    FT_Set_Pixel_Sizes(face, 0, 48);

    // Disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Load first 128 characters of ASCII set
    // 加载ASCII码 - 没有汉字呢还
    for (GLubyte c = 0; c < 128; c++)
    {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // Generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer);
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Now store character for later use
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            (unsigned)face->glyph->advance.x};
        Characters.insert(std::pair<GLchar, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    // Destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    // Configure VAO/VBO for texture quads
    glGenVertexArrays(1, &textVAO);
    glGenBuffers(1, &textVBO);
    glBindVertexArray(textVAO);
    glBindBuffer(GL_ARRAY_BUFFER, textVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
#pragma endregion

    // Step5_排列方块位置
    // 管理Block位置数组

    // 读取地图信息
    map_generate mapGenerate;
    auto map = mapGenerate.GenerateMap();

    // log信息
    LogString log_position;
    LogString log_camfront;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
#pragma region Log - 信息
        // region
        // 显示帧数
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // std::cout << "FPS: " << (int)(1 / deltaTime) << "\t\t"
        //           << "Position: "
        //           << (int)camera.Position.x << " "
        //           << (int)camera.Position.y << " "
        //           << (int)camera.Position.z << "\t"
        //           << "Camera.Front: "
        //           << camera.Front.x << " "
        //           << camera.Front.y << " "
        //           << camera.Front.z << " "
        //           << std::endl;

        log_position.clear();
        log_position.addStr("Camera.Position: x:");
        log_position.append((int)camera.Position.x);
        log_position.addStr(" y:");
        log_position.append((int)camera.Position.y);
        log_position.addStr(" z:");
        log_position.append((int)camera.Position.z);
        // std::cout << log_position.content << std::endl;

        log_camfront.clear();
        log_camfront.addStr("Camera.Front: x:");
        log_camfront.append(camera.Front.x);
        log_camfront.addStr(" y:");
        log_camfront.append(camera.Front.y);
        log_camfront.addStr(" z:");
        log_camfront.append(camera.Front.z);
        // std::cout << log_camfront.content << std::endl;
// endregion
#pragma endregion

        // 得到
        string fpsINFO = "FPS:\t";
        ShownTime += deltaTime;
        if ((ShownTime - 0.3f) >= 0)
        {
            std::stringstream ss;
            ss << (int)(1 / deltaTime);
            ss >> fpsNum;
            ss.clear();
            ShownTime = 0;
        }

        fpsINFO += fpsNum;

        // input
        // -----
        // 键盘输入
        processInput(window);

        // render
        // ------
        // 底色
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // TODO: GL基础配置 : 搞懂意义
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Shader赋值:草地
        // be sure to activate shader when setting uniforms/drawing objects
        Shader_Block_Grass.use();
        Shader_Block_Grass.setVec3("viewPos", camera.Position);
        Shader_Block_Grass.setFloat("material.shininess", 32.0f);

        /*
           Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
           the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
           by defining light types as classes and set their values in there, or by using a more efficient uniform approach
           by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
        */

        // view/projection transformations
        glm::mat4 projection =
            glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        Shader_Block_Grass.setMat4("projection", projection);
        Shader_Block_Grass.setMat4("view", view);

        // world transformation
        glm::mat4 model;
        Shader_Block_Grass.setMat4("model", model);

        // 渲染贴图:草皮贴图
        // bind diffuse map
        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, diffuseMap_top);
        // glActiveTexture(GL_TEXTURE1);
        // glBindTexture(GL_TEXTURE_2D, diffuseMap_side);
        // glActiveTexture(GL_TEXTURE2);
        // glBindTexture(GL_TEXTURE_2D, diffuseMap_bottom);

        // todo:这里省略了逐帧调用 但是总有一天要搞回来的
        // render containers
        glBindVertexArray(cubeVAO);
        // 读取地图 - 绘制地形
        int Row = 0;
        for (auto row : map)
        {
            int Col = 0;
            for (auto point : row)
            {
                for (int i = 0; i <= point; i++)
                {
                    if (i == point)
                    {
                        // 渲染贴图:草皮贴图
                        block_GrassSoil.Render();
                    }
                    else if (i < point - 4)
                    {
                        block_Stone.Render();
                    }
                    else
                    {
                        // 渲染贴图:土块贴图
                        block_Soli.Render();
                    }

                    glm::vec3 cubePositions = glm::vec3(Row, i, Col);
                    // calculate the model matrix for each object
                    // and pass it to shader before drawing
                    glm::mat4 model;
                    model = glm::translate(model, cubePositions);
                    Shader_Block_Grass.setMat4("model", model);

                    glDrawArrays(GL_TRIANGLES, 0, 36);
                }
                Col++;
            }
            Row++;
        }

        // glfw: swap buffers and poll IO events
        // --------------------------------------
        // (keys pressed/released, mouse moved etc.)
        // -----------------------------------------
        glfwPollEvents();

        float text_interval = 12.5f;

        // Render Text
        if (isLogShown)
        {
            // RenderText(Shader_Font, "MineCraft_OpenGL", 0, SCR_HEIGHT - 15, 0.3f, glm::vec3(0.3, 0.7f, 0.9f));
            // RenderText(Shader_Font, fpsINFO, 0, SCR_HEIGHT - 30, 0.3f, glm::vec3(0.5, 0.8f, 0.2f));
            // RenderText(Shader_Font, log_position.content, 0, SCR_HEIGHT - 45, 0.3f, glm::vec3(0, 0.8f, 0.8f));
            // RenderText(Shader_Font, log_camfront.content, 0, SCR_HEIGHT - 60, 0.3f, glm::vec3(0, 0.8f, 0.8f));

            RenderText(Shader_Font, "MineCraft_OpenGL", 0, SCR_HEIGHT - text_interval, text_interval / 50, glm::vec3(0.3, 0.7f, 0.9f));
            RenderText(Shader_Font, fpsINFO, 0, SCR_HEIGHT - text_interval * 2, text_interval / 50, glm::vec3(0.5, 0.8f, 0.2f));
            RenderText(Shader_Font, log_position.content, 0, SCR_HEIGHT - text_interval * 3, text_interval / 50, glm::vec3(0, 0.8f, 0.8f));
            RenderText(Shader_Font, log_camfront.content, 0, SCR_HEIGHT - text_interval * 4, text_interval / 50, glm::vec3(0, 0.8f, 0.8f));
        }

        glfwSwapBuffers(window);
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------

    glDeleteVertexArrays(1, &textVAO);
    glDeleteBuffers(1, &textVBO);
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &cubeVBO);

    // glDeleteVertexArrays(1, &dubug_line_VAO);
    // glDeleteBuffers(1, &debug_line_VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();

    return 0;
}
#pragma region 回调函数

// process all input: query GLFW whether
// -------------------------------------
// relevant keys are pressed/released this frame and react accordingly
// --------------------------------------------------------------------
// 按键控制:wasd前后左右 qe上下 left_shift加速(only 4 wasd) v玄学显示鼠标 back显示Log
bool isVpressed = false;
bool isBSpressed = false;
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard_Move(FORWARD, deltaTime, FPS_ALL);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard_Move(BACKWARD, deltaTime, FPS_ALL);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard_Move(LEFT, deltaTime, FPS_ALL);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard_Move(RIGHT, deltaTime, FPS_ALL);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.Position.y -= 0.1f;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.Position.y += 0.1f;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        camera.ChangeSpeed(10);
    }
    else
    {
        camera.ChangeSpeed();
    }

    if (glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_PRESS && isBSpressed == false)
    {
        isLogShown = !isLogShown;
        isBSpressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_RELEASE && isBSpressed == true)
    {
        isBSpressed = false;
    }

    // 玄学控制 => 没办法实现单词点击实现

    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS && isVpressed == false)
    {
        if (isCursorHidden)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            isCursorHidden = false;
        }
        else
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            isCursorHidden = true;
        }
        isVpressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_RELEASE && isVpressed == true)
    {
        isVpressed = false;
    }
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
// 鼠标移动视角
void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = static_cast<float>(xpos);
        lastY = static_cast<float>(ypos);
        firstMouse = false;
    }

    auto xoffset = static_cast<float>(xpos - lastX);
    auto yoffset = static_cast<float>(lastY - ypos); // reversed since y-coordinates go from bottom to top

    lastX = static_cast<float>(xpos);
    lastY = static_cast<float>(ypos);

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll((float)yoffset);
}
#pragma endregion

// utility function for loading a 2D texture from file
// ---------------------------------------------------
// 导入材质
unsigned int loadTexture(char const *path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;

    // tell stb_image.h to flip loaded texture's on the y-axis.
    stbi_set_flip_vertically_on_load(true);

    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        // 先行判断图形格式:有没有透明通道
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

        // 风格1:远处使用线性采样 - 减少摩尔纹
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // 风格2:真实mc:全邻近
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
        throw glGetError();
    }

    return textureID;
}

// 渲染文字
void RenderText(Shader &shader, const std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
    // Activate corresponding render state
    shader.use();
    glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(textVAO);

    // Iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        GLfloat xpos = x + ch.Bearing.x * scale;
        GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        GLfloat w = ch.Size.x * scale;
        GLfloat h = ch.Size.y * scale;
        // Update VBO for each character
        GLfloat vertices[6][4] = {
            {xpos, ypos + h, 0.0, 0.0},
            {xpos, ypos, 0.0, 1.0},
            {xpos + w, ypos, 1.0, 1.0},

            {xpos, ypos + h, 0.0, 0.0},
            {xpos + w, ypos, 1.0, 1.0},
            {xpos + w, ypos + h, 1.0, 0.0}};
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, textVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices),
                        vertices); // Be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) *
             scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}