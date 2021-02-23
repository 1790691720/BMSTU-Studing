//“transact.h”
#ifndef TRANSACT_H
#define TRANSACT_H
class Transact {

private:
	static unsigned int CURRENT_ID;
	unsigned int _ID;
	float _timeNextEvent;
	unsigned int _currentState;
public:
	Transact() { _ID = CURRENT_ID++; _currentState = 0; }
	unsigned int GetID() const { return _ID; }
	unsigned int GetCurrentState() { return _currentState; }
	void SetCurrentState(unsigned int state) { _currentState = state; }
	float GetTime() { return _timeNextEvent; }
	void SetTime(float _time) { _timeNextEvent = _time; }
	friend bool operator == (Transact& one, Transact& another);

};
#endif
//“transact.cpp”

unsigned int Transact::CURRENT_ID = 0;
bool operator == (Transact& one, Transact& another) {
	return one._ID == another._ID;
}
//“state.h”
#ifndef STATE_H
#define STATE_H
#include <iostream>
#include <fstream>
#include <list>

using namespace std;
class Querry {
private:
	list <Transact*> _transacts;
	int _capacity;
public:
	Querry(int capacity = -1) : _capacity(capacity) { }
	int Size() { return _transacts.size(); }
	int Add(Transact* transact);
	Transact* Get() { Transact* ret = _transacts.front(); _transacts.pop_front(); return ret; }
	bool Has(Transact& transact);

};
class State {
protected:
	static unsigned int CURRENT_ID;
	unsigned int _ID;
	unsigned int _nextState;
public:
	State() { _ID = CURRENT_ID++; }
	unsigned int GetID() const { return _ID; }
	void SetNextState(unsigned int nextState, ofstream& file) { _nextState = nextState; }
	virtual int UseTransact(Transact& transact) = 0;

};
class Generate : public State {
private:
	float _time;
	int _MIN;
	int _MAX;
public:
	Generate() : State() { _time = 0.0; }
	float GetTime() { return _time += (_MIN + (rand() % _MAX) + (float)rand() / RAND_MAX); }
	int UseTransact(Transact& transact, ofstream& file);
	void SetMinMax(int min, int max) { _MIN = min; _MAX = max; }

};
class Operator : public State {
private:
	int _MIN;
	int _MAX;
	bool _isOccuped;
	Transact* _occuped;
	Querry _querry;
public:
	Operator(int querryCapacity = -1) : State(), _querry(querryCapacity) { _isOccuped = false; }
	void SetMinMax(int min, int max) { _MIN = min; _MAX = max; }
	int UseTransact(Transact& transact, ofstream& file);
	int GetQuerrySize() { return _querry.Size(); }
	bool IsOccuped() { return _isOccuped; }

};
class Terminator : public State {
public:
	Terminator() : State() { }
	int UseTransact(Transact& transact, ofstream& file);
};
#endif

//“state.cpp”
#include <iterator>
#include "state.h"
int Querry::Add(Transact* transact) {
	if ((_capacity == -1) || (_transacts.size() < _capacity)) {
		_transacts.push_back(transact);
	}
	else {
		return 1;
	}
}
bool Querry::Has(Transact& transact) {
	list <Transact*> ::iterator it;
	for (it = _transacts.begin(); it != _transacts.end(); ++it) {
		if ((**it) == transact) { return true; }
	}
	return false;
}
unsigned int State::CURRENT_ID = 0;
int Generate::UseTransact(Transact& transact, ofstream& file) {
	transact.SetCurrentState(_nextState);
	file << "At " << transact.GetTime() << "s transact " << transact.GetID() << " has appeared" << endl;
}
int Operator::UseTransact(Transact& transact, ofstream& file) {
	if (!_isOccuped) {
		file << "At " << transact.GetTime() << "s transact " << transact.GetID() << " has begun operating at " << _ID << " operator" << endl;
		transact.SetTime(transact.GetTime() + (_MIN + (rand() % _MAX) + (float)rand() / RAND_MAX));
		_occuped = &transact;
		_isOccuped = true;
	}
	else if (&transact == _occuped) {
		file << "At " << transact.GetTime() << "s transact " << transact.GetID() << " has ended operating at " << _ID << " operator" << endl;
		transact.SetCurrentState(_nextState);
		if (_querry.Size() > 0) {
			Transact* next = _querry.Get();
			file << "At " << next->GetTime() << "s transact " << next->GetID() << " has begun operating at " << _ID << " operator" << endl;
			next->SetTime(next->GetTime() + (_MIN + (rand() % _MAX) + (float)rand() / RAND_MAX));
			_occuped = next;
		}
		else {
			_isOccuped = false;
		}
	}
	else {
		if (!_querry.Has(transact)) {
			_querry.Add(&transact);
			file << "At " << transact.GetTime() << "s transact " << transact.GetID() << " has gone to querry at " << _ID << " operator on " << _querry.Size() << " place" << endl;
		}
		transact.SetTime(_occuped->GetTime());
	}
}
int Terminator::UseTransact(Transact& transact, ofstream& file) {
	file << "At " << transact.GetTime() << "s transact " << transact.GetID() << " has left" << endl;
	delete& transact;
}
//“main.cpp”
#include "transact.h"
#include "state.h"
int main(int argc, char** argv)
{
	if (argc < 6) { cout << "Not enough input data" << endl; return -1; }
	int r1 = atoi(argv[1]);
	int g1 = atoi(argv[2]);
	int b1 = atoi(argv[3]);
	int rnd = atoi(argv[4]);
	int endTime = atoi(argv[5]);
	ofstream file;
	file.open("debug.txt");
	if (!file.is_open()) { cout << "Cannot use file" << endl; return 2; }
	srand(rnd);
	Generate generate;
	generate.SetNextState(1);
	generate.SetMinMax(0, r1 + g1 + b1);
	Operator* operators[2];
	operators[0] = new Operator();
	operators[0]->SetNextState(4);
	operators[0]->SetMinMax(r1, r1 + g1 + b1);
	operators[1] = new Operator();
	operators[1]->SetNextState(4);
	operators[1]->SetMinMax(g1, r1 + g1 + b1);
	Terminator terminator;
	list <Transact*> transacts;
	Transact* end = new Transact();
	end->SetCurrentState(0);
	end->SetTime(endTime);
	transacts.push_front(end);
	Transact* start = new Transact();
	start->SetCurrentState(0);
	start->SetTime(generate.GetTime());
	transacts.push_front(start);
	list <Transact*> ::iterator it;
	bool endFlag = false;
	while (!endFlag) {
		float minTime = (*transacts.begin())->GetTime();
		for (it = transacts.begin(); it != transacts.end(); ++it) {
			minTime = minTime > (*it)->GetTime() ? (*it)->GetTime() : minTime;
		}
		for (it = transacts.begin(); it != transacts.end(); ++it) {
			if ((*it)->GetTime() == minTime) {
				switch ((*it)->GetCurrentState()) {
				case 0: {
					if (**it == *end) {
						endFlag = true;
					}
					else {
						generate.UseTransact(**it, file);
						Transact* newTrans = new Transact();
						newTrans->SetTime(generate.GetTime());
						transacts.push_back(newTrans);
					}
					break;
				}
				case 1: {
					bool flag = false;
					for (int i = 0; i < sizeof(operators) / sizeof(*operators); ++i) {
						if (!(operators[i]->IsOccuped())) {
							(*it)->SetCurrentState(i + 2);
							operators[i]->UseTransact(**it, file);
							flag = true;
							break;
						}
					}
					if (!flag) {
						int min = operators[0]->GetQuerrySize();
						int minIndex = 0;
						for (int i = 0; i < sizeof(operators) / sizeof(*operators); ++i) {
							if (operators[i]->GetQuerrySize() < min) {
								minIndex = i;
								min = operators[i]->GetQuerrySize();
							}
						}
						(*it)->SetCurrentState(minIndex + 2);
						operators[minIndex]->UseTransact(**it, file);
					}
					break;
				}
				case 2:
					operators[0]->UseTransact(**it, file);
					break;
				case 3:
					operators[1]->UseTransact(**it, file);
					break;
				case 4:
					terminator.UseTransact(**it, file);
					it = transacts.erase(it);
					break;
				}
			}
		}
	}
	file.close();
	return 0;
}