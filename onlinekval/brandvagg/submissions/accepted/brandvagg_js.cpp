#include<bits/stdc++.h>
#include<memory>

using namespace std;

queue<string> history;
map<string, int> counts;

class Packet {
public:
	int id;
	string ip;
	string port;

	Packet(int id, string host) : id(id) {
		bool f = true;
		for(char c : host){
			if(c == ':') f = false;
			else if(f) ip.push_back(c);
			else port.push_back(c);
		}
	}
};

void push_packet(const Packet& p){
	counts[p.ip]++;
	history.push(p.ip);
}

void pop_packet(){
	string ip = history.front();
	history.pop();
	counts[ip]--;
}

class Condition {
public:
	virtual bool matches(const Packet& p) const = 0;
};

class IP : public Condition {
public:
	string ip;
	IP(string condition) : ip(condition.substr(3)) { }
	bool matches(const Packet& p) const { return p.ip == ip; }
};

class Port : public Condition {
public:
	string port;
	Port(string condition) : port(condition.substr(5)) { }
	bool matches(const Packet& p) const { return p.port == port; }
};

class Limit : public Condition {
public:
	string lim;
	Limit(string condition) : lim(condition.substr(6)) { }
	bool matches(const Packet& p) const { return counts[p.ip] >= atoi(lim.c_str()); }
};

class Action {
public:
	virtual bool execute(const Packet& p) const = 0;
};

class Accept : public Action {
public:
	bool execute(const Packet& p) const { cout << "accept " << p.id << endl; return false; }
};

class Drop : public Action {
public:
	bool execute(const Packet& p) const { cout << "drop " << p.id << endl; return false; }
};

class Log : public Action {
public:
	bool execute(const Packet& p) const { cout << "log " << p.id << endl; return true; }
};

class Abort : public Action {
public:
	bool execute(const Packet& p) const { abort(); }
};

class Rule {
public:
	Action* action;
	vector<Condition*> conditions;

	Rule(string s){
		stringstream ss;
		ss << s;

		string tok;
		ss >> tok;
		setAction(tok);
		while(ss >> tok) addCondition(tok);
	}

	Rule() {
		action = new Abort;
	}

	void setAction(const string& tok){
		if(tok == "accept") action = new Accept;
		else if(tok == "drop") action = new Drop;
		else if(tok == "log") action = new Log;
	}

	void addCondition(const string& tok){
		if(tok[0] == 'i') conditions.push_back(new IP(tok));
		else if(tok[0] == 'p') conditions.push_back(new Port(tok));
		else if(tok[0] == 'l') conditions.push_back(new Limit(tok));
	}

	bool execute(const Packet& p) const {
		for(const auto& a : conditions) if (!a->matches(p)) return true;
		return action->execute(p);
	}
};

int main(){
	int N, P;
	cin >> N;
	vector<Rule> firewall;
	cin.ignore();
	for(int i = 0; i < N; ++i){
		string s;
		getline(cin, s);
		firewall.push_back(Rule(s));
	}
	firewall.push_back(Rule());
	cin >> P;
	cin.ignore();
	for(int i = 1; i <= P; ++i){
		string s;
		getline(cin, s);
		Packet p(i, s);
		push_packet(p);
		if (history.size() > 100) pop_packet();
		for(const auto& rule : firewall){
			if(!rule.execute(p)) break;
		}
	}
}
