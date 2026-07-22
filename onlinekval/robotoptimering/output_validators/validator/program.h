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
	void fail(string reason, string token = "")
	{
		succeeded_parsing = false;
		if (token.size()) fail_reason = reason + ". Token: \"" + token + "\"";
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
		// The program is a free-form stream of whitespace-separated tokens;
		// line breaks are not significant. { and } are their own tokens.
		vector<string> tokens;
		{
			string tok;
			while (input >> tok) tokens.push_back(tok);
		}

		for (size_t i = 0; i < tokens.size(); )
		{
			const string& tok = tokens[i];

			// Label: any token ending in a colon.
			if (tok.back() == ':')
			{
				string name = tok.substr(0, tok.size() - 1);
				if (name.empty())
				{
					fail("Empty label name", tok);
					return;
				}
				if (name.find(':') != string::npos)
				{
					fail("Label name contains a colon", tok);
					return;
				}
				instructions.push_back(Instruction(label, name));
				i++;
				continue;
			}

			if (tok == "forward") { instructions.push_back(Instruction(InstructionType::forward)); i++; continue; }
			if (tok == "left")    { instructions.push_back(Instruction(rotate_left));   i++; continue; }
			if (tok == "right")   { instructions.push_back(Instruction(rotate_right));  i++; continue; }
			if (tok == "return")  { instructions.push_back(Instruction(ret));           i++; continue; }
			if (tok == "}")       { instructions.push_back(Instruction(endloop));       i++; continue; }

			if (tok == "call" || tok == "gotoblocked")
			{
				InstructionType t = (tok == "call") ? call : gotoblocked;
				if (i + 1 >= tokens.size())
				{
					fail("Missing label after", tok);
					return;
				}
				instructions.push_back(Instruction(t, tokens[i + 1]));
				i += 2;
				continue;
			}

			if (tok == "for")
			{
				if (i + 2 >= tokens.size())
				{
					fail("Malformed loop: expected \"for X {\"", tok);
					return;
				}
				const string& iterations = tokens[i + 1];
				if (tokens[i + 2] != "{")
				{
					fail("Malformed loop: expected { after the iteration count", tokens[i + 2]);
					return;
				}
				if (!is_int(iterations))
				{
					fail("Number of loop iterations is not an integer", iterations);
					return;
				}
				try
				{
					int num_its = stoi(iterations);
					if (num_its <= 0)
					{
						fail("Number of loop iterations is not positive", iterations);
						return;
					}
					if (num_its > int(1e8))
					{
						fail("Number of loop iterations is more than 10^8", iterations);
						return;
					}
					instructions.push_back(Instruction(loop, num_its));
				}
				catch (const std::out_of_range&)
				{
					fail("Number of loop iterations is more than 10^8", iterations);
					return;
				}
				catch (const std::invalid_argument&)
				{
					fail("Number of loop iterations is not an integer", iterations);
					return;
				}
				i += 3;
				continue;
			}

			fail("Did not recognize token", tok);
			return;
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

	bool is_int(const string& s)
	{
		if (s.empty()) return false;
		for (auto c : s) if (c < '0' || c > '9') return false;
		return true;
	}
	bool is_space(char c)
	{
		return c == ' ' || c == '\t' || c == '\n' || c == '\r';
	}
};