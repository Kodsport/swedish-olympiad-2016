//#include "validate.h"

#include "validate.h"
#include <bits/stdc++.h>
#include "direction.h"
#include "program.h"
#include "Executor.h"
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define debug(...) //ignore
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long double ld;

#define repe(i, container) for (auto& i : container)

int r, c;
vector<string> maze;
string map_name;
pair<int, int> goal;
pair<int,int> startpos;
Direction startdirection;


void parse_map(ifstream& in)
{
	in >> map_name;
	in >> r >> c;
	maze.resize(r);
	rep(i, 0, r) in >> maze[i];

	rep(i, 0, r)
	{
		rep(j, 0, c)
		{
			if (maze[i][j]=='M')
			{
				maze[i][j] = '.';
				goal = make_pair(i, j);
			}
			if (maze[i][j]=='<')
			{
				maze[i][j] = '.';
				startpos = make_pair(i, j);
				startdirection = Direction::left;
			}
			if (maze[i][j]=='v')
			{
				maze[i][j] = '.';
				startpos = make_pair(i, j);
				startdirection = Direction::down;
			}
			if (maze[i][j]=='>')
			{
				maze[i][j] = '.';
				startpos = make_pair(i, j);
				startdirection = Direction::right;
			}
			if (maze[i][j]=='^')
			{
				maze[i][j] = '.';
				startpos = make_pair(i, j);
				startdirection = Direction::up;
			}
		}
	}
}



const int MAX_MOVES = int(1e8);

int num_moves = -1;
bool reaches_goal(Program program)
{
	Executor exec(startpos, goal, startdirection, maze, program);

	for (int i = 0; i < MAX_MOVES; i++)
	{
		num_moves = i;
		exec.advance();
		if (exec.done) return true;
	}
	/*rep(i, 0, r) {
		rep(j, 0, c)
		{
			cout << exec.vis[i][j];
		}
		cout << "\n";
	}*/
	return false;
}

int main(int argc, char** argv)
{
#if 0
	ifstream in_file("e:\\maze.txt");
	parse_map(in_file);
	ifstream user_solution("e:\\submission.txt");
	Program program(user_solution);

	cout << reaches_goal(program);
#else

	init_io(argc, argv);
	//parse_map(judge_in);
	//ifstream in("e:\\maze.txt");
	parse_map(judge_in);

	//ifstream auth("c:\\users\\matis\\source\\repos\\robotoptimering\\x64\\debug\\author.txt");
	Program program(author_out);
	if (!program.succeeded_parsing)
	{
		author_message(program.fail_reason.c_str());
		wrong_answer(program.fail_reason.c_str());
	}
	if (!reaches_goal(program))
	{
		author_message("Does not reach goal in 10^8 steps");
		wrong_answer("Does not reach goal");
	}
	
	string judge_s;
	judge_ans >> judge_s;
	double judge_moves = stoi(judge_s);
	double author_moves = program.get_move_count();

	if (false)
	{
		author_message(("AC with " + to_string(num_moves)).c_str());
		accept_with_score(author_moves);
		return 0;
	}

	if (author_moves<=judge_moves)
	{
		accept_with_score(10);
	}
	else
	{
		double score = 10 * (1 - pow((author_moves - judge_moves) / author_moves, 2));
		accept_with_score(score);
	}
	
	//ofstream(map_name) << score << " " << author_moves;
#endif
	
}
