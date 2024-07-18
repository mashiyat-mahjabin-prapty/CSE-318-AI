#include<bits/stdc++.h>
using namespace std;

class LatinSquare
{
	int N;
	vector< vector<int> > board;
	vector< vector< set<int> > > domain;
	set< pair<int, int> > zeroes;
	long long int nodes=0;
	long long int bt = 0;
public:
	LatinSquare(int N)
	{
		this->N = N;
		board.resize(N);
		for(int i = 0; i < N; i++)
		board[i].resize(N);
		
		domain.resize(N);
		for(int i = 0; i < N; i++)
		domain[i].resize(N);
		
		int t;
		for(int i = 0; i < N; i++)
		{
			for(int j = 0; j < N; j++)
			{
				cin >> t;
				board[i][j]=t;
				if(t == 0)
				{
					zeroes.insert(make_pair(i, j));	
				}	
			}	
		}				
	}
	
	void preprocess()
	{
		for(int i = 0; i < N; i++)
		{
			for(int j = 0; j < N; j++)
			{
				if(board[i][j] == 0)
				{
					for(int k = 1; k <= N; k++)
					{
						domain[i][j].insert(k);
					}
				}
				else
				{
					domain[i][j].insert(board[i][j]);
				}
			}
		}
		
		for(int i = 0; i < N; i++)
		{
			for(int j = 0; j < N; j++)
			{
				if(board[i][j] != 0)
				{
					for(int c = 0; c < N; c++)
					{
						if(board[i][c] == 0)
						{
							if(domain[i][c].find(board[i][j]) != domain[i][c].end())
							{
								domain[i][c].erase(board[i][j]);
							}
						}
					}
					for(int r = 0; r < N; r++)
					{
						if(board[r][j] == 0)
						{
							if(domain[r][j].find(board[i][j]) != domain[r][j].end())
							{
								domain[r][j].erase(board[i][j]);
							}
						}
					}
				}
			}
		}
		
//		for(int i = 0; i < N; i++)
//		{
//			for(int j = 0; j < N; j++)
//			{
//				set<int, greater<int> >::iterator itr;
//				cout << "\nThe set (" << i << " " << j << ") is :";
//				for (itr = domain[i][j].begin(); itr != domain[i][j].end(); itr++) {
//    				cout << *itr << " ";
//				}
//			//cout << endl;
//			}
//		}
		cout << endl << endl;
	}
	
	int h1(int r, int c)
	{
		
		return domain[r][c].size();
	}
	
	int h2(int r, int c)
	{
		int cnt=0;
		set<pair<int, int> >::iterator itr;
		
		for(int i = 0; i < N; i++)
		{
			if(i != r && board[i][c] == 0)
			{
				cnt++;
			}
		}
		for(int j = 0; j < N; j++)
		{
			if(j != c && board[r][j] == 0)
			{
				cnt++;
			}
		}
		return cnt;
	}
	
	pair<int, int> rowcolh1()
	{
		int minimum = N+1; 
		pair<int, int> rc;
		for(int i = 0; i < N; i++)
		{
			for(int j = 0; j < N; j++)
			{
				if(board[i][j] == 0)
				{
					int h = h1(i, j);
					if(h < minimum)
					{
						minimum = h;
						rc.first = i;
						rc.second = j;
					}
				}
			}
		}
		return rc;
	}
	
	pair<int, int> rowcolh2()
	{
		int maximum = -1;
		pair<int, int> rc;
		for(int i = 0; i < N; i++)
		{
			for(int j = 0; j < N; j++)
			{
				if(board[i][j] == 0)
				{
					int h = h2(i, j);
					if(h > maximum)
					{
						maximum = h;
						rc.first = i;
						rc.second = j;
					}
				}
			}
		}
		return rc;
	}
	
	pair<int, int> rowcolh3()
	{
		int minimum = N+1;
		pair<int, int> rc;
		for(int i = 0; i < N; i++)
		{
			for(int j = 0; j < N; j++)
			{
				if(board[i][j] == 0)
				{
					int h = h1(i, j);
					if(h < minimum)
					{
						minimum = h;
						rc.first = i;
						rc.second = j;
					}
					else if(h == minimum)
					{
						int p = h2(i, j);
						int q = h2(rc.first, rc.second);
						
						if(p > q)
						{
							minimum = h;
							rc.first = i;
							rc.second = j;
						}
					}
				}
			}
		}
		return rc;
	}
	
	pair<int, int> rowcolh4()
	{
		int minimum = 1000000;
		pair<int, int> rc;
		for(int i = 0; i < N; i++)
		{
			for(int j = 0; j < N; j++)
			{
				if(board[i][j] == 0)
				{
					int h = h1(i, j);
					if(h2(i, j) != 0)
					{
						h = h/h2(i, j);
					}
					else
					{
						h = h/0.00001;
					}
					if(h < minimum)
					{
						minimum = h;
						rc.first = i;
						rc.second = j;
					}
				}
			}
		}
		return rc;
	}
	
	pair<int, int> rowcolh5()
	{
		pair<int, int> rc;
		srand(time(0));
		int i = -1;
		
		i = rand() % zeroes.size();
		set<pair<int, int> >::iterator itr;
		pair<int, int> p;
		int j;
		for(itr = zeroes.begin(), j = 0; itr != zeroes.end(); itr++, j++)
		{
			if(j == i)
			{
				p = *itr;
			}
		}
		rc.first = p.first;
		rc.second = p.second;
		
		return rc;
	}
	
	bool solve()
	{
		nodes++;
		int r=-1;
		int c=-1;
		
		if(zeroes.size() == 0)
		{
			return true;
		}
		
		pair<int, int> rc = rowcolh1();
		r = rc.first;
		c = rc.second;
		
		zeroes.erase(make_pair(r, c));
		set<int>::iterator itr;
		
		vector<int> temp;
		
		for(itr = domain[r][c].begin(); itr != domain[r][c].end(); itr++)
		{
			temp.push_back(*itr);
		}
		if(temp.size() == 0)
		{
			bt++;
			return false;
		}
		
		std::random_shuffle(temp.begin(), temp.end());
		
		for (int kk = 0; kk < temp.size(); kk++)
		{
			//cout << "Here\n";
			int a1 = temp[kk];
			board[r][c] = a1;
			
			vector<pair<int, int> > indices;
			for(int p = 0; p < N; p++)
				{
					if(board[r][p] == 0)
					{
						if(domain[r][p].find(a1) != domain[r][p].end())
						{
							domain[r][p].erase(a1);
							indices.push_back(make_pair(r, p));
						}
					}
				}
				for(int q = 0; q < N; q++)
				{
					if(board[q][c] == 0)
					{
						if(domain[q][c].find(a1) != domain[q][c].end())
						{
							domain[q][c].erase(a1);
							indices.push_back(make_pair(q, c));
						}
					}
				}
				
			bool s = solve();
			if(s)
			{
				return true;
			}
			
			for(int abc = 0; abc < indices.size(); abc++)
			{
				pair<int, int> pq = indices[abc];
				domain[pq.first][pq.second].insert(a1);
			}
		}
		
		board[r][c] = 0;
		zeroes.insert(make_pair(r, c));
		//bt++;
		return false;
	}
	
	void display()
	{
		cout << "\nNode Count: " << nodes << "\nBacktrack Count: " << bt << endl << endl;
		for(int i = 0; i < N; i++)
		{
			for(int j = 0; j < N; j++)
			{
				cout << board[i][j] << " "; 
			}
			cout << endl;
		}
	}
};

int main()
{
	int N;
	cin >> N;
	LatinSquare ls(N);
	ls.preprocess();
	time_t start, end;
	
	start = clock();
	ls.solve();
	end = clock();
	
	time_t time_taken = end-start;
	
	cout << "Time taken: " << time_taken/CLK_TCK << " milliseconds" << endl;
	ls.display();
}


