#pragma once

#include <iostream>
#include <unordered_map>

const uint8_t MODE_POSITION = 0;
const uint8_t MODE_IMMEDIATE = 1;
const uint8_t MODE_RELATIVE = 2;

struct Instruction
{
	uint8_t op = 0;
	uint8_t modes[3] = { 0,0,0 };
};

Instruction parseInstruction(int64_t inst)
{
	Instruction result;

	result.op = inst % 100;

	int t = 100;
	for (int i = 2; i < log10(inst) && i < 8; i++)
	{
		int d = (inst / t) % 10;
		result.modes[i - 2] = d;
		t *= 10;
	}
	return result;
}

class Program
{
public:
	void run();

	void setCode(const std::vector<int64_t>& code);
	void setInput(int64_t input)
	{
		this->input = input;
	}

private:
	int64_t getArg(int64_t arg);
	void write(int64_t arg, int64_t val);

	int64_t input = 0;

	Instruction inst;

	std::unordered_map<int64_t, int64_t> arr;
	int64_t counter = 0;
	int64_t relative_base = 0;
};
