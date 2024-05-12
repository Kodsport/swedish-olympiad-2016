#include "validator.h"

void run() {
	string input = Line();
	assert(input.size()>0 && input.size()<=int(Arg("maxn")));
	vector<int> allowed(256);
	allowed['U']=1;
	allowed['N']=1;
	allowed['V']=1;
	allowed['H']=1;
	allowed['B']=1;
	allowed['A']=1;
	for (int i = 0; i < input.size(); i++)
	{
		assert(allowed[input[i]]);
	}
	Eof();
}
