#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "adventofcode14.h"

struct Requirement
{
	std::string element;
	int64_t num_required = 1;
};

struct ReactionNode
{
	int64_t num_from_reaction = 1;
	std::vector<Requirement> requirements;
};

std::unordered_map<std::string, ReactionNode> reactions;

std::unordered_map<std::string, int64_t> produced;
std::unordered_map<std::string, int64_t> extra;
std::unordered_map<std::string, std::unordered_map<std::string, int64_t>> total_produced;


void setTotalRequirements(const std::string& element, int64_t num_wanted, int64_t depth = 0)
{
	auto& reaction = reactions[element];

	int64_t num_to_produce = 0; // = num_wanted - extra[element];
	int64_t extra_left = 0;
	if (num_wanted < extra[element])
	{
		num_to_produce = 0;
		extra_left = extra[element] - num_wanted;
	}
	else
	{
		num_to_produce = num_wanted - extra[element];
	}
	
	/*
	if (extra[element] > 0)
	{
		for (int i = 0; i < depth; i++)
			std::cout << "  ";
		std::cout << "Using " << extra[element] << " spare " << element << "\n";
	}
	for (int i = 0; i < depth; i++)
		std::cout << "  ";
	std::cout << "Producing " << num_to_produce << " " << element << "\n";
	*/
	
	int64_t mult = num_to_produce / reaction.num_from_reaction;
	mult += (num_to_produce % reaction.num_from_reaction) > 0 ? 1 : 0;
	if ((num_to_produce % reaction.num_from_reaction) > 0)
		extra[element] = reaction.num_from_reaction - (num_to_produce % reaction.num_from_reaction);
	else
		extra[element] = extra_left;

	/*
	if (extra[element] > 0)
	{
		for (int i = 0; i < depth; i++)
			std::cout << "  ";
		std::cout << "Produced " << extra[element] << " spare " << element << "\n";
	}
	*/
	
	

	for (auto& requirement : reaction.requirements)
	{
		produced[requirement.element] += mult * requirement.num_required;
		setTotalRequirements(requirement.element, mult * requirement.num_required, depth + 1);
	}
}

void part1()
{
	setTotalRequirements("FUEL", 1);

	for (auto& reaction : reactions)
	{
		std::string element = reaction.first;

		int64_t mult = produced[element] / reaction.second.num_from_reaction;
		mult += (produced[element] % reaction.second.num_from_reaction) > 0 ? 1 : 0;

		for (auto req : reaction.second.requirements)
		{
			total_produced[req.element][element] = mult * req.num_required;
		}
	}

	int64_t sum = 0;
	for (auto p : total_produced["ORE"])
		sum += p.second;

	std::cout << sum << "\n";
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
				int64_t num_required = std::stol(req_str, &next);

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
			int64_t num_from_reaction = std::stol(result_str, &next);
			result = result_str.substr(next + 1);

			reactions[result] = { num_from_reaction, requirements };

			//std::cout << result << ": " << num_from_reaction << "\n";
		}
		data.close();
	}

	//part1();
	int64_t start = 0;
	int64_t i = 1;
	bool running = true;
	while (running)
	{
		int64_t n = start + i*i*i;

		setTotalRequirements("FUEL", n);

		for (auto& reaction : reactions)
		{
			std::string element = reaction.first;

			int64_t mult = produced[element] / reaction.second.num_from_reaction;
			mult += (produced[element] % reaction.second.num_from_reaction) > 0 ? 1 : 0;

			for (auto req : reaction.second.requirements)
			{
				total_produced[req.element][element] = mult * req.num_required;
			}
		}
		int64_t sum = 0;
		for (auto p : total_produced["ORE"])
			sum += p.second;
		std::cout << n << ": " << sum << "\n";

		if (sum > 1000000000000L)
		{
			int64_t old_start = start;
			start = i-1;
			start *= start * start;
			start += old_start;
			i = -1;
		}

		produced.clear();
		extra.clear();
		total_produced.clear();
		i++;
	}
}