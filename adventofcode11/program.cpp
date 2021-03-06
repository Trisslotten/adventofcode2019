#include "program.hpp"

#include <iostream>

int64_t Program::getArg(int64_t arg)
{
	int64_t result = arr[counter + arg + 1];
	switch (inst.modes[arg])
	{
	case MODE_POSITION:
		result = arr[result];
		break;
	case MODE_RELATIVE:
		result = arr[relative_base + result];
		break;
	}
	return result;
}

void Program::write(int64_t arg, int64_t val)
{
	int64_t address;
	switch (inst.modes[arg])
	{
	case MODE_POSITION:
		address = arr[counter + arg + 1];
		break;
	case MODE_RELATIVE:
		address = arr[counter + arg + 1] + relative_base;
		break;
	}
	arr[address] = val;
}

int64_t Program::run()
{
	int64_t output = 99;
	bool running = true;
	while (running)
	{
		inst = parseInstruction(arr[counter]);

		switch (inst.op)
		{
		case 1:
		{
			write(2, getArg(0) + getArg(1));
			counter += 4;
		} break;

		case 2:
		{
			write(2, getArg(0) * getArg(1));
			counter += 4;
		} break;

		case 3:
		{
			write(0, input);
			counter += 2;
		} break;

		case 4:
		{
			//std::cout << getArg(0) << "\n";
			output = getArg(0);
			counter += 2;
			running = false;
		} break;

		case 5:
		{
			if (getArg(0) != 0)
				counter = getArg(1);
			else
				counter += 3;
		} break;

		case 6:
		{
			if (getArg(0) == 0)
				counter = getArg(1);
			else
				counter += 3;
		} break;

		case 7:
		{
			write(2, getArg(0) < getArg(1) ? 1 : 0);
			counter += 4;
		} break;

		case 8:
		{
			write(2, getArg(0) == getArg(1) ? 1 : 0);
			counter += 4;
		} break;

		case 9:
		{
			relative_base += getArg(0);
			counter += 2;
		} break;

		case 99:
		{
			running = false;
		} break;

		default:
			running = false;
			std::cout << "UNKNOWN OPCODE: " << (int)inst.op << "\n";
			break;
		}
	}
	return output;
}

void Program::setCode(const std::vector<int64_t>& code)
{
	for (int64_t i = 0; i < code.size(); i++)
	{
		arr[i] = code[i];
	}
}
