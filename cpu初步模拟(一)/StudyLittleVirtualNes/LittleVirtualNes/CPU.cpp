#include "pch.h"
#include "CPU.h"
#include <sstream>
#include <windows.h>

CPU::CPU()
{
	ZeroMemory(&m_register, sizeof(Register));
}

uint8_t CPU::ReadByte(uint16_t addr)
{
	return m_memroy[addr];	//简单读取
}

uint8_t CPU::Immediate()
{
	uint8_t data = ReadByte(m_register.PC++);
	return data;	//这个是数据
}

//m_register.pc 指向当前数据，用于来运算
//数字只有一个字节
uint8_t CPU::ZeroPage()
{
	//读取 zero page 对应的index ，作为地址
	uint8_t index = ReadByte(m_register.PC++);
	return ReadByte(index);
}

uint8_t CPU::Absolute()
{
	uint8_t low = ReadByte(m_register.PC++);
	uint8_t high = ReadByte(m_register.PC++);
	uint16_t addr = low | high << 8;
	return ReadByte(addr);
}

//数据操作只是读取立即数，用来进行偏移
uint8_t CPU::Relative()
{
	return Immediate();	//这个地址要切换-128~127，所以要切换成char
}

char CPU::Indirect()
{
	uint8_t addr = Absolute();
	uint8_t low = ReadByte(m_register.PC++);
	uint8_t high = ReadByte(m_register.PC++);
	return low | high << 8;
}

void CPU::SetFlagCarry(const uint16_t& result)
{
	//设置carry
	if (result > 0xFF) {
		m_register.P |= 0x1;
	}
	else {
		m_register.P &= ~0x1;
	}
}

void CPU::SetFlagZero(const uint16_t& result)
{
	if (result == 0) {
		m_register.P |= 0x2;// 一定设置
	}
	else {
		m_register.P &= ~0x2;
	}
}

//(result ^ A) & (result ^ memory) & $80
//公式的原理：我暂时不知道，后面要考虑思考
void CPU::SetFlagOverflow(const uint16_t& result, const uint8_t& data)
{
	bool r = ((result ^ m_register.ACC)& (result ^ data) & 0x80);
	if (r) {
		m_register.P |= 0x40;
	}
	else {
		m_register.P &= ~0x40;
	}
}

void CPU::SetNegative(const uint16_t& result)
{
	bool r = result & 0x80;
	if (r) {
		m_register.P |= 0x80;
	}
	else {
		m_register.P &= ~0x80;
	}
}

uint8_t CPU::GetFlagCarry()
{
	return m_register.P & 0x1;
}

//A = A + memory + C
void CPU::ADC(uint8_t data)
{
	uint8_t c = GetFlagCarry();
	uint16_t result = m_register.ACC + data + c;

	//设置carry
	SetFlagCarry(result);

	//设置0位
	SetFlagZero(result);

	//设置溢出
	SetFlagOverflow(result, data);

	m_register.ACC = (uint8_t)result;
}

uint16_t CPU::Clock()
{
	uint16_t cycle = 0;
	uint8_t OPCODE = ReadByte(m_register.PC++);
	uint8_t data = 0;
	switch (OPCODE)
	{
	case 0x69:
		data = Immediate();
		ADC(data);
		cycle = 2;
		break;
	default:
		break;
	}

	return cycle;
}

void CPU::PrintfRegister()
{
	std::stringstream log;
	log << std::hex << " acc: 0x" << static_cast<unsigned int>(m_register.ACC) << " p: 0x" << static_cast<unsigned int>(m_register.P);
	OutputDebugStringA(log.str().c_str());
	::MessageBoxA(0, log.str().c_str(), 0, 0);
}

void CPU::Init(uint8_t* addr)
{
	m_memroy = addr;
}

void CPU::SetAccRegister(uint8_t data)
{
	m_register.ACC = data;
}
