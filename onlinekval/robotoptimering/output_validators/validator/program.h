#pragma once
#include "instruction.h"
#include "debug.h"
#include <bits/stdc++.h>
using namespace std;


class Program
{
public:
	vector<Instruction> instructions;
	bool succeeded_parsing = true;
	string fail_reason = "";

	Program(istream& input)
	{
		read_program(input);
		if (!succeeded_parsing) return;
		compile_program();
	}

	void compile_program()
	{
		link_goto();
		if (!succeeded_parsing) return;
		link_loops();
		if (!succeeded_parsing) return;
		validate_main();
	}

	int get_move_count()
	{
		int count = 0;
		vector<InstructionType> counted_instructions = { InstructionType::forward,
			rotate_left,
			rotate_right,
			loop,
			call,
			ret,
			gotoblocked };
		for (auto inst : instructions)
		{
			count += find(counted_instructions.begin(), counted_instructions.end(), inst.type) != counted_instructions.end();
		}

		return count;
	}

private:
	void fail(string reason, string line = "")
	{
		succeeded_parsing = false;
		if (line.size()) fail_reason = reason + ". Line: \"" + line + "\"";
		else fail_reason = reason;
	}

	void validate_main()
	{
		bool found_main = false;
		for (int i = 0; i < instructions.size(); i++)
		{
			Instruction& inst = instructions[i];
			if (inst.type == label && inst.name == "main")
			{
				found_main = true;
				break;
			}
		}
		if (!found_main) fail("There is no label main");
	}

	// forward
	// left
	// right
	// }
	// return

	// gotoblocked x
	// goto x
	// for x {
	// call x

	// label
	void read_program(istream& input)
	{
		map<string, Instruction> instruction_names;
		instruction_names["for"] = InstructionType::loop;
		instruction_names["}"] = InstructionType::endloop;
		instruction_names["right"] = InstructionType::rotate_right;
		instruction_names["left"] = InstructionType::rotate_left;
		instruction_names["forward"] = InstructionType::forward;
		instruction_names["call"] = InstructionType::call;
		instruction_names["return"] = InstructionType::ret;
		instruction_names["gotoblocked"] = InstructionType::gotoblocked;
		string line;
		while (getline(input, line))
		{
			string original_line = line;
			trim(line);
			if (line.empty()) continue;
			// Label
			if (line.find(":") != string::npos)
			{
				if (line.back() != ':')
				{
					fail("Label has more instructions after the colon", original_line);
					return;
				}
				line.pop_back();
				if (is_space(line.back()))
				{
					fail("Label has whitespace between name and colon", original_line);
					return;
				}
				if (any_whitespace(line))
				{
					fail("Label name has whitespace in it", original_line);
					return;
				}

				instructions.push_back(Instruction(label, line));
				continue;
			}

			// forward
			// left
			// right
			// }
			// return
			if (!any_whitespace(line))
			{
				InstructionType t = noop;
				if (line == "forward") t = InstructionType::forward;
				if (line == "left") t = InstructionType::rotate_left;
				if (line == "right") t = InstructionType::rotate_right;
				if (line == "}") t = InstructionType::endloop;
				if (line == "return") t = InstructionType::ret;

				if (t == noop)
				{
					fail("Did not recognize token", original_line);
					return;
				}
				instructions.push_back(Instruction(t));
				continue;
			}

			// gotoblocked x
			// goto x
			// for x {
			// call x
			int first_whitespace = -1;
			for (int i = 0; i < line.size(); i++) if (is_space(line[i]))
			{
				first_whitespace = i;
				break;
			}
			assert(first_whitespace != -1);
			string first_token = line.substr(0, first_whitespace);
			for (int i = 0; i < first_whitespace; i++) line.erase(line.begin());
			trim(line);
			InstructionType t = noop;
			if (first_token == "gotoblocked") t = InstructionType::gotoblocked;
			if (first_token == "for") t = InstructionType::loop;
			if (first_token == "call") t = InstructionType::call;

			if (t == noop)
			{
				fail("Did not recognize token", original_line);
				return;
			}

			if (t == loop)
			{
				if (line.find("{") == string::npos)
				{
					fail("Malformed loop: no {", original_line);
					return;
				}
				string iterations = line.substr(0, line.find("{"));
				trim(iterations);
				if (!is_int(iterations))
				{
					fail("Number of loop iterations is not an integer", original_line);
					return;
				}
				try
				{
					int num_its = stoi(iterations);
					if (num_its <= 0)
					{
						fail("Number of loop iterations is not positive", original_line);
						return;
					}
					if (num_its > int(1e8))
					{
						fail("Number of loop iterations is more than 10^8", original_line);
						return;
					}
					instructions.push_back(Instruction(loop, num_its));
				}
				catch (const std::out_of_range)
				{
					fail("Number of loop iterations is more than 10^8", original_line);
					return;
				}

			}
			else if (t == gotoblocked || t == call)
			{
				if (any_whitespace(line))
				{
					fail("goto cannot have target with spaces", original_line);
					return;
				}
				instructions.push_back(Instruction(t, line));
			}
			else
			{
				fail("Failed to parse line", original_line);
			}
		}
		instructions.push_back(Instruction(eof));
	}

	void link_goto()
	{
		map<string, int> labels;
		int label_count = 0;
		for (int i = 0; i < instructions.size(); i++)
		{
			Instruction& inst = instructions[i];
			if (inst.type == label)
			{
				label_count++;
				labels[inst.name] = i;
			}
		}
		if (label_count != labels.size())
		{
			fail("Multiple labels with the same name are present in the program");
			return;
		}
		for (int i = 0; i < instructions.size(); i++)
		{
			Instruction& inst = instructions[i];
			if (inst.type == gotoblocked || inst.type == call)
			{
				if (labels.count(inst.name) == 0)
				{
					fail("Label not found for", inst.name);
					return;
				}
				inst.target = labels[inst.name];
			}
		}
	}

	void link_loops()
	{
		stack<int> loops;

		for (int i = 0; i < instructions.size(); i++)
		{
			Instruction& inst = instructions[i];
			if (inst.type == loop)
			{
				loops.push(i);
			}
			if (inst.type == endloop)
			{
				if (loops.empty())
				{
					fail("Tried ending a loop that doesn't exist");
					return;
				}
				inst.target = loops.top();
				loops.pop();
			}
			if (loops.size() && inst.type == label)
			{
				fail("label inside loop");
				return;
			}
		}
		if (loops.size())
		{
			fail("There were loops with no closing parenthesis");
		}
	}

	void trim(string& s)
	{
		while (s.size() && is_space(s.back())) s.pop_back();
		reverse(s.begin(), s.end());
		while (s.size() && is_space(s.back())) s.pop_back();
		reverse(s.begin(), s.end());
	}
	bool any_whitespace(string& s)
	{
		for (auto c : s) if (is_space(c)) return true;
		return false;
	}
	bool is_int(string& s)
	{
		for (auto c : s) if (c < '0' || c > '9') return false;
		return true;
	}
	bool is_space(char c)
	{
		return c == ' ' || c == '\t' || c == '\n' || c == '\r';
	}
};