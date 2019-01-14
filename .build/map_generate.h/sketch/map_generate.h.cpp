#include <Arduino.h>
#line 1 "/Users/w/CLionProjects/MineCraft_OpenGL_Version/MC_Src/map_generate/map_generate.h"
#line 1 "/Users/w/CLionProjects/MineCraft_OpenGL_Version/MC_Src/map_generate/map_generate.h"
//
// Created by W/Lee on 2019-01-08.
//

#ifndef MINECRAFT_OPENGL_MAP_GENERATE_H
#define MINECRAFT_OPENGL_MAP_GENERATE_H

#include <iostream>
#include <string>
//#include <vector>
#include <math.h>
#include <fstream>
#include <iomanip>
#include <random>

using namespace std;

class map_generate
{
    // 输出Config目录
    const string dir_config = "/Users/w/CLionProjects/MineCraft_OpenGL_Version/MC_Config/map.txt";
    //    const string dir_config = "MC_Config/map.txt";

    // 输出二维大小
    const int regionX = 40;
    const int regionY = 40;

    // 随机种子
    // 如果有指定种子就用指定种子
    // 没有指定种子就用系统时间 -> seed = 0
    // 我在这里暂且指定种子从 0 - 65535
    unsigned randNum = 0;

    // 持续度 -> 越大越乱
    float persistence = 0.20;

    // 倍频度 -> 越大好像也越乱
    int Number_Of_Octaves = 4;

    // 根据(x,y)获取一个初步噪声值
    double Noise(int x, int y)
    {
        int n = x + y * 57;
        n = (n << 13) ^ n;
        return (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
    }

    // 如果有指定种子就用指定种子
    // 没有指定种子就用系统时间 -> seed = 0
    // 我在这里暂且指定种子从 0 - 65535
    unsigned GenerateRandom(const unsigned &target_seed)
    {
        //初始化种子
        auto seed = static_cast<unsigned int>(time(nullptr));
        if (target_seed != 0)
        {
            seed = target_seed;
        }

        //随机数引擎对象
        default_random_engine e;

        e.seed(seed);

        //随机数分布对象，控制随机数范围5-15
        uniform_int_distribution<unsigned> u(0, 65535);
        //        std::cout << "地图生成seed:\t" << seed << std::endl;

        //展示一下,没必要放上去
        //        for (int i = 0; i < 10; i++)
        //        {
        //            cout << u(e) << endl;
        //        }

        return u(e);
    }

    //光滑噪声
    double SmoothedNoise(int x, int y)
    {
        double corners = (Noise(x - 1, y - 1) + Noise(x + 1, y - 1) + Noise(x - 1, y + 1) + Noise(x + 1, y + 1)) / 16;
        double sides = (Noise(x - 1, y) + Noise(x + 1, y) + Noise(x, y - 1) + Noise(x, y + 1)) / 8;
        double center = Noise(x, y) / 4;
        return corners + sides + center;
    }

    // 余弦插值
    double Cosine_Interpolate(double a, double b, double x)
    {
        double ft = x * 3.1415927;
        double f = (1 - cos(ft)) * 0.5;
        return a * (1 - f) + b * f;
    }

    // 获取插值噪声
    double InterpolatedNoise(float x, float y)
    {
        int integer_X = int(x);
        float fractional_X = x - integer_X;
        int integer_Y = int(y);
        float fractional_Y = y - integer_Y;
        double v1 = SmoothedNoise(integer_X, integer_Y);
        double v2 = SmoothedNoise(integer_X + 1, integer_Y);
        double v3 = SmoothedNoise(integer_X, integer_Y + 1);
        double v4 = SmoothedNoise(integer_X + 1, integer_Y + 1);
        double i1 = Cosine_Interpolate(v1, v2, fractional_X);
        double i2 = Cosine_Interpolate(v3, v4, fractional_X);
        return Cosine_Interpolate(i1, i2, fractional_Y);
    }

    // 最终调用：根据(x,y)获得其对应的PerlinNoise值
    double PerlinNoise(float x, float y)
    {
        double total = 0;
        double p = persistence;
        int n = Number_Of_Octaves;
        for (int i = 0; i < n; i++)
        {
            double frequency = pow(2, i);
            double amplitude = pow(p, i);
            total = total + InterpolatedNoise(x * frequency, y * frequency) * amplitude;
        }

        return total;
    }

  public:
    vector<vector<int>> GenerateMap()
    {
        // 读写文件流
        ofstream mapFile(dir_config);
        // if (!mapFile)
        // {
        //     // throw runtime_error("Map file Open Error!");
        // }

        // 读取随机种子
        unsigned seed = GenerateRandom(randNum);
        cout << "地图生成seed:\t" << seed << endl;

        // 记录生成量
        unsigned block_num = 0;

        // 搞出来vector存储地形数据
        vector<vector<int>> map;
        for (float i = 0; i < regionX; ++i)
        {
            vector<int> height_row;
            for (float j = 0; j < regionY; ++j)
            {
                // todo:很丑陋的做法,有机会改了
                int height = static_cast<int>(
                    PerlinNoise(static_cast<float>(i * 0.1 + seed), static_cast<float>(j * 0.1 + seed)) * 30 + 6);

                // 防止露馅儿
                if (height < 1)
                    height = 1;

                height_row.push_back(height);
                //                std::cout << height << "\t";

                //记录总数
                block_num += height;

                //写文件
                mapFile << height << "\t";
            }
            map.push_back(height_row);
            //            std::cout << std::endl;

            //写文件
            mapFile << "\n"
                    << endl;
        }
        cout << "地图生成block:\t" << block_num << endl;

        return map;
    }
};

#endif //MINECRAFT_OPENGL_MAP_GENERATE_H

