#pragma once
#include "program.h"
#include "direction.h"
#include "debug.h"
#include <stack>
#include "validate.h"
typedef pair<int, int> pii;

struct StackFrame
{
	int instruction_ptr;
	vector<int> loop_counters;
};

class Executor
{
public:
	pair<int, int> pos;
	pii goal;
	Direction curr_dir;
	int instruction_ptr;
	Program program;
	bool done;
	vector<string> maze;
	int r, c;
	stack<StackFrame> callstack;
	vector<vector<int>> vis;
	vector<int> loop_indices;

	Executor(pair<int, int> pos, pii goal, Direction curr_dir, vector<string>& maze, Program& program) : pos(pos), curr_dir(curr_dir),
		program(program), done(false), loop_counters(program.instructions.size(), -1), maze(maze),
		r(maze.size()), c(maze[0].size()), goal(goal)
	{
		vis.resize(maze.size(), vector<int>(maze[0].size()));
		instruction_ptr = -1;

		for (size_t i = 0; i < program.instructions.size(); i++)
		{
			auto instruction = program.instructions[i];
			if (instruction.type==label && instruction.name == "main")
			{
				instruction_ptr = i;
				break;
			}
		}
		for (size_t i = 0; i < program.instructions.size(); i++)
		{
			auto instruction = program.instructions[i];
			if (instruction.type==loop)
			{
				loop_indices.push_back(i);
			}
		}

		assert(instruction_ptr != -1);
	}

	void advance()
	{
		Instruction& curr_instruction = program.instructions[instruction_ptr];
		if (curr_instruction.type == eof) return;

		vis[pos.first][pos.second] = 1;

		switch (curr_instruction.type)
		{
		case gotoblocked:
			if (!can_go_here(make_movement(pos, curr_dir)))
			{
				for (auto p : loop_indices) loop_counters[p] = -1;
				instruction_ptr = curr_instruction.target;
			}
			break;
		case InstructionType::forward:
			if (can_go_here(make_movement(pos, curr_dir)))
			{
				pos = make_movement(pos, curr_dir);
			}
			break;
		case InstructionType::rotate_right:
			curr_dir = (Direction)((curr_dir + 1) % 4);
			break;
		case InstructionType::rotate_left:
			curr_dir = (Direction)(curr_dir - 1 + 4 * (curr_dir==0));
			break;
		case InstructionType::loop:
			if (loop_counters[instruction_ptr]==-1)
			{
				loop_counters[instruction_ptr] = curr_instruction.num_iterations-1;
			}
			break;
		case InstructionType::endloop:
			loop_counters[curr_instruction.target]--;
			if (loop_counters[curr_instruction.target]!=-1)
			{
				instruction_ptr = curr_instruction.target;
			}
			break;
		case call:;
			callstack.push(create_stack_snapshot());
			instruction_ptr = curr_instruction.target-1;
			break;
		case ret:;
			if (callstack.empty())
			{
				author_message("Called ret with empty callstack");
				wrong_answer("Called ret with empty callstack");
			}
			instruction_ptr = callstack.top().instruction_ptr;
			for (int i = 0; i < loop_indices.size(); i++) loop_counters[loop_indices[i]] = callstack.top().loop_counters[i];
			callstack.pop();
		case label:
			break;
		default:
			assert(0);
			break;
		}

		instruction_ptr++;

		if (pos==goal)
		{
			done = true;
		}
	}
private:
	StackFrame create_stack_snapshot()
	{
		vector<int> snapshot;
		for (auto p : loop_indices) snapshot.push_back(loop_counters[p]);
		return { instruction_ptr, snapshot };
	}

	vector<int> loop_counters;

	inline bool is_inside(pii pos)
	{
		return pos.first >= 0 && pos.first < r && pos.second >= 0 && pos.second < c;
	}

	inline bool can_go_here(pii pos)
	{
		if (!is_inside(pos)) return false;
		return maze[pos.first][pos.second] != '#';
	}

	inline pii make_movement(pii pos, Direction dir)
	{
		switch (dir)
		{
		case up:
			return make_pair(pos.first - 1, pos.second);
		case down:
			return make_pair(pos.first + 1, pos.second);
		case Direction::left:
			return make_pair(pos.first, pos.second - 1);
		case Direction::right:
			return make_pair(pos.first, pos.second + 1);
		default:
			break;
		}
	}
};
