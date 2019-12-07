#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


const uint8_t PARAM1_MODE_BIT = 1 << 0;
const uint8_t PARAM2_MODE_BIT = 1 << 1;
const uint8_t PARAM3_MODE_BIT = 1 << 2;
struct Instruction
{
	uint8_t op = 0;
	uint8_t modes = 0;
};

Instruction parseInstruction(int inst)
{
	Instruction result;

	result.op = inst % 100;

	int t = 100;
	for (int i = 2; i < log10(inst) && i < 8; i++)
	{
		int d = (inst / t) % 10;
		if (d == 1)
		{
			result.modes |= 1 << (i - 2);
		}
		t *= 10;
	}
	return result;
}

struct Program
{
	std::vector<int> arr = { 3,8,1001,8,10,8,105,1,0,0,21,34,59,68,85,102,183,264,345,426,99999,3,9,101,3,9,9,102,3,9,9,4,9,99,3,9,1002,9,4,9,1001,9,2,9,1002,9,2,9,101,5,9,9,102,5,9,9,4,9,99,3,9,1001,9,4,9,4,9,99,3,9,101,3,9,9,1002,9,2,9,1001,9,5,9,4,9,99,3,9,1002,9,3,9,1001,9,5,9,102,3,9,9,4,9,99,3,9,1001,9,1,9,4,9,3,9,1001,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,101,1,9,9,4,9,99,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,101,2,9,9,4,9,99,3,9,1001,9,1,9,4,9,3,9,101,1,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,1001,9,1,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,1,9,4,9,99,3,9,1002,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,101,2,9,9,4,9,99,3,9,1001,9,1,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,2,9,9,4,9,99 };
	size_t counter = 0;
	bool started = false;
};

struct AmpResult
{
	int output;
	bool done;
};

AmpResult runAmp(std::vector<int> inputs, Program& program)
{
	int input_index = 0;

	std::vector<int>& arr = program.arr;
	size_t& counter = program.counter;
	bool running = true;

	int result = 0;

	while (running)
	{
		auto inst = parseInstruction(arr[counter]);

		switch (inst.op)
		{
		case 1:
		{
			int a = arr[counter + 1];
			if ((inst.modes & PARAM1_MODE_BIT) == 0)
				a = arr[a];
			int b = arr[counter + 2];
			if ((inst.modes & PARAM2_MODE_BIT) == 0)
				b = arr[b];
			arr[arr[counter + 3]] = a + b;
			counter += 4;
			break;
		}
		case 2:
		{
			int a = arr[counter + 1];
			if ((inst.modes & PARAM1_MODE_BIT) == 0)
				a = arr[a];
			int b = arr[counter + 2];
			if ((inst.modes & PARAM2_MODE_BIT) == 0)
				b = arr[b];
			arr[arr[counter + 3]] = a * b;
			counter += 4;
			break;
		}
		case 3:
		{
			arr[arr[counter + 1]] = inputs[input_index];
			input_index++;
			counter += 2;
			break;
		}
		case 4:
		{
			int a = arr[counter + 1];
			if ((inst.modes & PARAM1_MODE_BIT) == 0)
				a = arr[a];
			counter += 2;
			return { a, false };
			break;
		}
		case 5:
		{
			int a = arr[counter + 1];
			if ((inst.modes & PARAM1_MODE_BIT) == 0)
				a = arr[a];
			int b = arr[counter + 2];
			if ((inst.modes & PARAM2_MODE_BIT) == 0)
				b = arr[b];

			if (a != 0)
			{
				counter = b;
			}
			else
			{
				counter += 3;
			}
			break;
		}
		case 6:
		{
			int a = arr[counter + 1];
			if ((inst.modes & PARAM1_MODE_BIT) == 0)
				a = arr[a];
			int b = arr[counter + 2];
			if ((inst.modes & PARAM2_MODE_BIT) == 0)
				b = arr[b];

			if (a == 0)
			{
				counter = b;
			}
			else
			{
				counter += 3;
			}
			break;
		}
		case 7:
		{
			int a = arr[counter + 1];
			if ((inst.modes & PARAM1_MODE_BIT) == 0)
				a = arr[a];
			int b = arr[counter + 2];
			if ((inst.modes & PARAM2_MODE_BIT) == 0)
				b = arr[b];

			arr[arr[counter + 3]] = a < b ? 1 : 0;
			counter += 4;
			break;
		}
		case 8:
		{
			int a = arr[counter + 1];
			if ((inst.modes & PARAM1_MODE_BIT) == 0)
				a = arr[a];
			int b = arr[counter + 2];
			if ((inst.modes & PARAM2_MODE_BIT) == 0)
				b = arr[b];

			arr[arr[counter + 3]] = a == b ? 1 : 0;
			counter += 4;
			break;
		}
		case 99:
		{
			running = false;
			break;
		}
		default:
			running = false;
			std::cout << "UNKNOWN OPCODE\n";
			break;
		}
	}
	return { 0, true };
}

int main()
{
	int max = 0;

	int params[] = { 0,0,0,0,0 };
	for (int i = 0; i < 5 * 5 * 5 * 5 * 5; i++)
	{
		params[0]++;
		int used[] = { 0,0,0,0,0 };
		bool cont = false;
		for (int j = 0; j < 5; j++)
		{
			if (j < 4)
				params[j + 1] += params[j] / 5;
			params[j] = params[j] % 5;

			used[params[j]]++;
			if (used[params[j]] > 1)
			{
				cont = true;
			}
		}
		if (cont)
		{
			continue;
		}

		Program programs[5];

		int input = 0;
		int amp = 0;
		bool running = true;
		while (running)
		{
			std::vector<int> inputs;
			if (!programs[amp].started)
			{
				inputs.push_back(params[amp] + 5);
				programs[amp].started = true;
			}
			inputs.push_back(input);

			auto result = runAmp(inputs, programs[amp]);
			if (!result.done)
			{
				input = result.output;
			}
			else
			{
				running = false;
			}
			if (amp == 4 && running)
			{
				if (result.output > max)
				{
					max = result.output;
					for (int i = 0; i < 5; i++)
					{
						std::cout << params[i]+5 << ", ";
					}
					std::cout << ": " << input << "\n";
				}
			}
			amp = (amp+1) % 5;
		}

	}

	return 0;
}