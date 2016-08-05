#pragma once
#include <iostream>
#include <string>
using namespace std;

// 添加宏定义错误文件和位置 
void error_out(string file, unsigned int linenum);
#define ErrorOut() error_out(__FILE__, __LINE__)
 

bool ReadShaderFile(const char* fileName, string& outFile);

