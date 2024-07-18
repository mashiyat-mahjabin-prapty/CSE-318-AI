#include<bits/stdc++.h>
using namespace std;
//#define N 3

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3


class State{
public:
	int N;
	vector<int> state;
	State *parent;
	string direction;
	int depth;
	vector<State*> nextStates;
	vector<int> goalState;
	bool actions[4] = {true,true,true,true};
	
	State(int _N)
	{
		N=_N;
		state.resize(N*N);
	}
	
	State(int _N, vector<int> _state, State* _parent, string _direction)
	{
		N = _N;
		for(int i = 0; i < (int)_state.size(); i++) state.push_back(_state[i]);
		parent = _parent;
	
		direction = _direction;
		if( parent!=NULL )
			depth = parent->depth+1;
		else
			depth = 0;
	
		for(int i = 0; i < N*N-1; i++)
		{
			goalState.push_back(i+1);
		}
		goalState.push_back(0);
	}
	
	void calcLegal(){
		legalMoves(findZero()/N, findZero()%N);
		next();
	}
	
	bool test()
	{
		for(int i = 0; i < N*N; i++)
		{
			if(state[i] != goalState[i])
			return false;
		} 
		return true;
	}
	void legalMoves(int row, int col)
	{
		if(row == 0)
		{
			actions[UP]=false;
		}
		if(row == N-1)
		{
			actions[DOWN]=false;
		}
		if(col == 0)
		{
			actions[LEFT]=false;
		}
		if(col == N-1)
		{
			actions[RIGHT]=false;
		}
	}
	int findZero()
	{
		int t;
		for(int i = 0; i < (int)this->state.size(); i++)
		{
			if(this->state[i] == 0)
			t = i;
		}
		return t;
	}
	void next()
	{
		int t = this->findZero();
		if(actions[UP])
		{
		//	cout<<"up";
			State* temp = new State(this->N, this->state, this, "");
			swap(temp->state[t-N], temp->state[t]);
			nextStates.push_back(temp);
		}
		if(actions[DOWN])
		{
	//	cout<<"down";
			State* temp = new State(this->N, this->state, this, "");
			swap(temp->state[t+N], temp->state[t]);
			nextStates.push_back(temp);
		}
		if(actions[LEFT])
		{	
	//	cout<<"left";
			State* temp = new State(this->N, this->state, this, "");
			swap(temp->state[t-1], temp->state[t]);
			nextStates.push_back(temp);
		}
		if(actions[RIGHT])
		{
	//	cout<<"right";
			State* temp = new State(this->N, this->state, this, "");
			swap(temp->state[t+1], temp->state[t]);
			nextStates.push_back(temp);
		}
	}
	int manhattanDist()
	{
		int manhattan = 0;
		
		for(int i = 0; i < N*N; i++)
		{
			if(state[i] != 0)
			{
				int drow = abs(int(i/N)-int((state[i]-1)/N));
				int dcol = abs(int(i%N)-int((state[i]-1)%N));
				manhattan += drow+dcol;
			}
		}
		return manhattan;
	}
	int hammingDist()
	{
		int count = 0;
		for(int i = 0; i < N*N; i++)
		{
			if(state[i] != goalState[i])
			count++;
		}
		return count;
	}
	int getInversion()
	{
		int inversion = 0;
		
		for(int i = 0; i< N*N - 1; i++)
		{
			for(int j = i+1; j < N*N; j++)
			{
				if(state[i] != 0 && state[j] != 0 && (state[i] > state[j]))
				{
					inversion++;
				}
			}
		}
		return inversion;
	}
	
	
	bool isSolvable()
	{
		int inversion = getInversion();
		
		if(N & 1)
		{
			return !(inversion & 1);
		}
		else
		{
			int blank = findZero()/N;
			if(blank & 1)
			{
				return !(inversion & 1);
			}
			else
			{
				return (inversion & 1);
			}
		}
	}
};

set< vector<int> > closed_list;
class cmpManhattan
{
    public: 
    bool operator()(State* e1, State* e2)
    {
        return e1->depth+e1->manhattanDist() > e2->depth+e2->manhattanDist();
    }
};

class cmpHamming
{
    public: 
    bool operator()(State* e1, State* e2)
    {
        return e1->depth+e1->hammingDist() > e2->depth+e2->hammingDist();
    }
};

void printPath(int N, State* curr){
	if(curr->parent != NULL)
	{
		printPath(N, curr->parent);
	}
	for(int i=0;i<N*N;i++){
		if(curr->state[i] != 0)
		cout<<curr->state[i]<<" ";
		else 
		cout<<"*"<<" ";
		if( (i+1)%N == 0 ) cout<<endl;
	} cout<<endl;		
}

int optimalCost(int N, State* curr, int heuristic)
{
	if(curr->parent == NULL)
	{
		if(heuristic == 1)
		return curr->depth+curr->manhattanDist();
		else
		return curr->depth+curr->hammingDist();
	}
	if(heuristic==1)
	return curr->depth+curr->manhattanDist()+optimalCost(N, curr->parent, 1);
	else
	return curr->depth+curr->hammingDist()+optimalCost(N, curr->parent, 2);
}

void AStar_Search(int N, State current)
	{
		set< vector<int> > closed_list_man;
		priority_queue<State*, vector<State*>, cmpManhattan> frontierMan;
		State root(N, current.state, NULL, "");
		int cntMan=0, cntHam=0;
		frontierMan.push(&root);
		cntMan++;
		while(!frontierMan.empty())
        {
            State* temp = frontierMan.top();
        
            temp->calcLegal();
           
            bool p = temp->test();
            if(p) {
			
            	printPath(N, temp);
            	cout << "Optimal Cost: " << temp->depth << endl;
            	cout << "Explored Nodes: " << cntMan << endl;
            	cout << "Expanded Nodes: " << closed_list_man.size() << endl << endl;
            	break; 
			}
            closed_list_man.insert(temp->state);
            frontierMan.pop();
            for (int i = 0; i < (int)temp->nextStates.size(); i++)
            {
		        if(closed_list_man.count(temp->nextStates[i]->state) == 0)
		        {
		            frontierMan.push(temp->nextStates[i]);
		            cntMan++;
		        }
            }
        }
        //cout << "here\n";
        set< vector<int> > closed_list_ham;
        priority_queue<State*, vector<State*>, cmpHamming> frontierHam;
	
		frontierHam.push(&root);
		cntHam++;
		while(!frontierHam.empty())
        {
            State* temp = frontierHam.top();
        
            temp->calcLegal();
            bool p = temp->test();
            if(p) {
            	printPath(N, temp);
            	cout << "Optimal Cost: " << temp->depth << endl;
            	cout << "Explored Nodes: " << cntHam << endl;
            	cout << "Expanded Nodes: " << closed_list_ham.size() << endl << endl;
            	break; 
			}
            closed_list_ham.insert(temp->state);
            frontierHam.pop();
            for (int i = 0; i < (int)temp->nextStates.size(); i++)
            {
		        if(closed_list_ham.count(temp->nextStates[i]->state) == 0)
		        {
		            frontierHam.push(temp->nextStates[i]);
					cntHam++;
		        }
            }
        }
	}	



int main()
{
	int N;
	cin >> N;	
	State puzzle(N);
	string in;
	for(int i = 0; i < N*N; i++)
	{
		cin >> in;
		if(in != "*")puzzle.state[i] = stoi(in);
		else puzzle.state[i] = 0;
	}

	puzzle.isSolvable() ? cout << "\nSolvable\n" << endl : cout << "\nNot Solvable\n" << endl;
	if(puzzle.isSolvable())AStar_Search(N, puzzle);
	return 0;
	
}

// 8 1 3 4 * 2 7 6 5

//* 1 3 4 2 5 7 8 6

//8 5 7 12 9 15 6 3 1 * 4 2 13 14 10 11

//1  2  3 4  6  5 7  8  *

