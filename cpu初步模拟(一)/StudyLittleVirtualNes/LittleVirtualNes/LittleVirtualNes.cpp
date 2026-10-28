// LittleVirtualNes.cpp : 定义静态库的函数。
//

#include "pch.h"
#include "framework.h"
#include <iostream>

// TODO: 这是一个库函数示例
// 导出一定要加extern "C" 否则无法识别

#ifdef __cplusplus
extern "C" {
#endif


void hello()
{
	std::cout << "hello world4" << std::endl;
}

#ifdef __cplusplus
}
#endif