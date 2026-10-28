#pragma once
class CPU
{
public:
	CPU();
private:
	struct Register {
		uint8_t ACC;
		uint8_t X;
		uint8_t Y;
		uint8_t SP;
		uint8_t P;
		uint16_t PC;
	};

	//其他的选址模式
	//读取一个字节
	uint8_t	ReadByte(uint16_t addr);

	//立即数
	inline uint8_t Immediate();

	//寻址模式
	inline uint8_t ZeroPage();

	//绝对寻址模式
	inline uint8_t Absolute();

	//相对寻址模式
	inline uint8_t Relative();
	
	//间接选址模式
	//类似C语言的指针
	inline char Indirect();

	//索引的寻址模式

	//标志操作
	void	SetFlagCarry(const uint16_t& result);

	void	SetFlagZero(const uint16_t& result);

	void	SetFlagOverflow(const uint16_t& result, const uint8_t& data);

	void	SetNegative(const uint16_t& result);

	uint8_t GetFlagCarry();

private:
	void ADC(uint8_t data);

public:
	uint16_t Clock();

	void PrintfRegister();

	//初始化
	void	Init(uint8_t* addr);

public:
	//测试数据
	void	SetAccRegister(uint8_t data);

private:

	Register	m_register;

	uint8_t* m_memroy;
};

