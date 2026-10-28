#include "pch.h"
#include "Nes.h"
#include <iostream>

Nes::Nes()
{
	m_is_exit = false;
}

bool Nes::load(const char* path)
{
	std::cout << "加载Nes" << std::endl;
	return false;
}

void Nes::Test()
{
	uint8_t code[] = {
		0x69,0xA
	};

	InitNes();

	memcpy_s(m_memory, 65536, code, sizeof(code));

	m_cpu.SetAccRegister(0x2);
	m_cpu.Clock();				//执行单条指令
	m_cpu.PrintfRegister();		//打印寄存器
}

void Nes::InitNes()
{
	//分配64kb内存
	m_memory = new uint8_t[64 * 1024];
	memset(m_memory, 0, 64 * 1024);

	m_cpu.Init(m_memory);
}

void Nes::excute()
{
	while (m_is_exit)
	{
		int cycle = m_cpu.Clock();

	}
}
