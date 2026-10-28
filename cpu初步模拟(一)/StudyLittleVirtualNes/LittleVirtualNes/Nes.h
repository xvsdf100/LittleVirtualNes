#pragma once
#include "CPU.h"

/// <summary>
/// 定义Nes，代表整个Nes
/// 属性：cpu ppu apu 重要3个组件
/// </summary>
class Nes
{
public:
	Nes();
	//加载nes
	bool load(const char* path);

	void Test();	//测试所有的命令

	void InitNes();	//测试nes

private:
	void excute();

private:
	int i = 0;
	bool	m_is_exit;
	CPU		m_cpu;
	uint8_t* m_memory;
};

