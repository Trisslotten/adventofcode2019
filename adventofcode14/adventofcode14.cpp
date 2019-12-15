#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <algorithm>

struct Requirement
{
	std::string element;
	long num_required = 1;
};

struct ReactionNode
{
	long num_from_reaction = 1;
	std::vector<Requirement> requirements;
};

std::unordered_map<std::string, ReactionNode> reactions;
std::unordered_map<std::string, long> produced;
std::unordered_map<std::string, long> extra;
std::unordered_map<std::string, std::unordered_map<std::string, long>> total_produced;


void setTotalRequirements(const std::string& element, long num_wanted, long depth = 0)
{
	auto& reaction = reactions[element];

	long num_to_produce = 0; // = num_wanted - extra[element];
	long extra_left = 0;
	if (num_wanted < extra[element])
	{
		num_to_produce = 0;
		extra_left = extra[element] - num_wanted;
	}
	else
	{
		num_to_produce = num_wanted - extra[element];
	}

	if (extra[element] > 0)
	{
		for (int i = 0; i < depth; i++)
			std::cout << "  ";
		std::cout << "Using " << extra[element] << " spare " << element << "\n";
	}
	for (int i = 0; i < depth; i++)
		std::cout << "  ";
	std::cout << "Producing " << num_to_produce << " " << element << "\n";

	long mult = num_to_produce / reaction.num_from_reaction;
	mult += (num_to_produce % reaction.num_from_reaction) > 0 ? 1 : 0;
	if ((num_to_produce % reaction.num_from_reaction) > 0)
		extra[element] = reaction.num_from_reaction - (num_to_produce % reaction.num_from_reaction);
	else
		extra[element] = extra_left;

	if (extra[element] > 0)
	{
		for (int i = 0; i < depth; i++)
			std::cout << "  ";
		std::cout << "Produced " << extra[element] << " spare " << element << "\n";
	}

	for (auto& requirement : reaction.requirements)
	{
		produced[requirement.element] += mult * requirement.num_required;
		setTotalRequirements(requirement.element, mult * requirement.num_required, depth + 1);
	}
}

void main()
{
	std::string line;
	std::ifstream data("data.txt");
	if (data.is_open())
	{
		while (getline(data, line))
		{
			std::vector<Requirement> requirements;
			std::string result;

			auto i = line.find_first_of("=>");
			std::string req_str = line.substr(0, i - 1);
			std::string result_str = line.substr(i + 3);

			while (req_str.size() > 0)
			{
				size_t next;
				long num_required = std::stol(req_str, &next);

				std::string rest = req_str.substr(next + 1);
				next = rest.find_first_of(',');
				next = std::min(next, rest.size());
				requirements.push_back({ rest.substr(0, next), num_required });
				if (next + 1 > rest.size())
				{
					break;
				}
				req_str = rest.substr(next + 1);
			}

			size_t next;
			long num_from_reaction = std::stol(result_str, &next);
			result = result_str.substr(next + 1);

			reactions[result] = { num_from_reaction,requirements };

			//std::cout << result << ": " << num_from_reaction << "\n";
		}
		data.close();
	}
	setTotalRequirements("FUEL", 1);

	for (auto& reaction : reactions)
	{
		std::string element = reaction.first;

		long mult = produced[element] / reaction.second.num_from_reaction;
		mult += (produced[element] % reaction.second.num_from_reaction) > 0 ? 1 : 0;

		for (auto req : reaction.second.requirements)
		{
			total_produced[req.element][element] = mult * req.num_required;
		}
	}

	long sum = 0;
	for(auto p : total_produced["ORE"])
		sum += p.second;

	std::cout << sum << "\n";
}