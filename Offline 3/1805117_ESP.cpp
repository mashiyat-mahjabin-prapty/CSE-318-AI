#include<bits/stdc++.h>
#include "1805117_Student.cpp"
#include "1805117_Course.cpp"
using namespace std;

vector<Student> studentList;
vector<Course> courseList;
vector<Course> orderList;
vector<bool> visited;
vector<int> visitedCrs;
bool LargestDegreeComparator(Course &a, Course &b)
{
	if (a.getMyNeighbours().size() > b.getMyNeighbours().size())
	return true;
	else
	return false;
}

int getSaturationDegree(Course &course)
{
	return course.getSaturation();
	set<int> colors;
	for(int c: course.getMyNeighbours())
	{
		if(courseList[c].getColor() != -1)
		colors.insert(courseList[c].getColor());
	}
	return colors.size();
}

bool BrelazComparator(Course &a, Course &b)
{
	if (getSaturationDegree(a) < getSaturationDegree(b))
	return true;
	else if(getSaturationDegree(a) > getSaturationDegree(b))
	return false;
	else if(a.getMyNeighbours().size() > b.getMyNeighbours().size())
	return true;
	else 
	return false;
}

bool LargestEnrollmentComparator(Course &a, Course &b)
{
	if (a.getNumStu() > b.getNumStu())
	return true;
	else
	return false;
}	

bool checkValidityofColoring(Course course, int color)
{
	 set<int> neighbours = course.getMyNeighbours();
   	for(int c: neighbours)
	{
		if(courseList[c].getColor() == color) return false;
	}
    return true;
}
int getColoring()
{
	int colors = 0;
	
	courseList[orderList[0].getID()].setColor(colors);
	
	for(int i = 1; i < orderList.size(); i++)
	{
		if(orderList[i].getColor() == -1)
		{
			bool Valid = false;
			int color;
			for(color = 0; color <= colors; color++)
			{
				Valid = checkValidityofColoring(orderList[i], color);
				if(Valid) break;
			}
			if(Valid)
			{
				courseList[ orderList[i].getID() ].setColor(color);
			}
			else
			{
				colors++;
				courseList[ orderList[i].getID() ].setColor(colors);
			}
			for(auto &c: courseList[ orderList[i].getID() ].getMyNeighbours() ){
					courseList[c].incrementSaturation();
			}
		}
	}
	return colors+1;
}
int getDSaturColoring()
{
	int colors = 0;
	
	courseList[orderList[0].getID()].setColor(colors);
	
	for(int i = 1; i < orderList.size(); i++)
	{
		sort(orderList.begin()+i, orderList.end(), BrelazComparator);
		
		if(orderList[i].getColor() == -1)
		{
			bool Valid = false;
			int color;
			for(color = 0; color <= colors; color++)
			{
				Valid = checkValidityofColoring(orderList[i], color);
				if(Valid) break;
			}
			if(Valid)
			{
				courseList[ orderList[i].getID() ].setColor(color);
			}
			else
			{
				colors++;
				courseList[ orderList[i].getID() ].setColor(colors);
			}
			for(auto &c: courseList[ orderList[i].getID() ].getMyNeighbours() ){
					courseList[c].incrementSaturation();
			}
		}
	}
	return colors+1;
}
void createGraph()
{
	for(Student s : studentList)
	{
		vector<int> myCourses = s.getMyCourses();
		for(int i = 0; i < myCourses.size(); i++)
		{
			for(int j = i+1; j < myCourses.size(); j++)
			{
				courseList[myCourses[i]].addNeighbour(myCourses[j]);
				courseList[myCourses[j]].addNeighbour(myCourses[i]);
			}
		}
		
	}
	return;
}
float penalty()
{
	float totalPenalty = 0.0;
	int penalties[] = {16, 8, 4, 2, 1};
	for(Student s : studentList)
	{
		vector<int> myCourses = s.getMyCourses();
		
		if(myCourses.empty()) continue;
		
		vector<int> myExamDays;
		myExamDays.resize(myCourses.size());
		int i = 0;
		for(int c : myCourses)
		{
			myExamDays[i++] = courseList[c].getColor();
		}
		
		int myPenalty = 0;
		
		if(myExamDays.size()==1) continue;
		
		for(int m = 0; m < myExamDays.size(); m++)
		{
			for(int n = m+1; n < myExamDays.size(); n++)
			{
				int diff = abs(myExamDays[m]-myExamDays[n]);
				
				if(diff >= 1 && diff <= 5)
				myPenalty += penalties[diff-1];
			}
		}
		totalPenalty += myPenalty*1.0;
	}
	return totalPenalty/(studentList.size()*1.0);
}
float penaltyLinear()
{
	float totalPenalty = 0.0;
	for(Student s : studentList)
	{
		vector<int> myCourses = s.getMyCourses();
		
		if(myCourses.empty()) continue;
		
		vector<int> myExamDays;
		myExamDays.resize(myCourses.size());
		int i = 0;
		for(int c : myCourses)
		{
			myExamDays[i++] = courseList[c].getColor();
		}
		
		int myPenalty = 0;
		
		if(myExamDays.size()==1) continue;
		
		for(int m = 0; m < myExamDays.size(); m++)
		{
			for(int n = m+1; n < myExamDays.size(); n++)
			{
				int diff = abs(myExamDays[m]-myExamDays[n]);
				
				if(diff >= 1 && diff <= 5)
				myPenalty += (2*(5-diff));
			}
		}
		totalPenalty += myPenalty*1.0;
	}
	return totalPenalty/(studentList.size()*1.0);
}
int chooseCourse(int maxSize)
{
	int random = rand()%maxSize;
	
	return random;
}
bool checkValidityofSwap(int c1, int c2, int color)
{
	set<int> neighbours = courseList[c1].getMyNeighbours();
	
	for(int n : neighbours)
	{
		if(courseList[n].getColor() == color && n != c2) return false;
	}
	return true;
}
float applyPairSwapExp(float prevPenalty)
{
	float myPenalty = prevPenalty;
	for(int i = 0; i < 1000; i++)
	{
		int c1 = chooseCourse(courseList.size());
		int c2 = chooseCourse(courseList.size());
	
		int color1 = courseList[c1].getColor();
		int color2 = courseList[c2].getColor();
		
		if(color1 != color2)
		{
			bool v1 = checkValidityofSwap(c1, c2, color2);
			bool v2 = checkValidityofSwap(c2, c1, color1);
			
			if(v1 && v2)
			{
				courseList[c1].setColor(color2);
				courseList[c2].setColor(color1);
				
				float newPen = penalty();
				
				if(newPen > myPenalty)
				{
					courseList[c1].setColor(color1);
					courseList[c2].setColor(color2);
				}
				else
				{
					myPenalty = newPen;
				}
			} 
		}
	}
	return myPenalty;
}
float applyPairSwapLin(float prevPenalty)
{
	float myPenalty = prevPenalty;
	for(int i = 0; i < 1000; i++)
	{
		int c1 = chooseCourse(courseList.size());
		int c2 = chooseCourse(courseList.size());

		int color1 = courseList[c1].getColor();
		int color2 = courseList[c2].getColor();
		
		if(color1 != color2)
		{
			bool v1 = checkValidityofSwap(c1, c2, color2);
			bool v2 = checkValidityofSwap(c2, c1, color1);
			
			if(v1 && v2)
			{
				courseList[c1].setColor(color2);
				courseList[c2].setColor(color1);
				
				float newPen = penaltyLinear();
				
				if(newPen > myPenalty)
				{
					courseList[c1].setColor(color1);
					courseList[c2].setColor(color2);
				}
				else
				{
					myPenalty = newPen;
				}
			} 
		}
	}
	return myPenalty;
}
void swapColor(int color1, int color2)
{
	for(auto u : visitedCrs)
	{
		if(courseList[u].getColor() == color1)
		{
			courseList[u].setColor(color2);
		}
		else
		{
			courseList[u].setColor(color1);
		}
	}
}
void dfs(int u, int color1, int color2)
{
	visited[u] = true;
	visitedCrs.push_back(u);
	for(auto v : courseList[u].getMyNeighbours())
	{
		if(!visited[v] and (courseList[v].getColor() == color1 or courseList[v].getColor() == color2))
		{
			dfs(v, color1, color2);
		}
	}
}
float kempe_chain_exp(float prevPenalty)
{
	float myPenalty = prevPenalty;
	for(int i = 0; i < 1000; i++)
	{
		int c1, c2;
		while(true)
		{
			c1 = chooseCourse(courseList.size());
			int t = courseList[c1].getMyNeighbours().size();
			if(t == 0) continue;
			else
			{
				c2 = chooseCourse(t);
				break;
			}
			
		}
		int color1 = courseList[c1].getColor();
		int color2 = courseList[c2].getColor();

		visitedCrs.clear();
		for(int j = 0; j < courseList.size(); j++)
		{
			visited[j] = false;
		}
		
		dfs(c1, color1, color2);
		
		swapColor(color1, color2);
		float newPenalty = penalty();
		
		if(newPenalty > myPenalty)
		{
			swapColor(color1, color2);
		}
		else
		{
			myPenalty = newPenalty;
		}
	}
	return myPenalty;
}
float kempe_chain_lin(float prevPenalty)
{
	float myPenalty = prevPenalty;
	for(int i = 0; i < 1000; i++)
	{
		int c1, c2;
		while(true)
		{
			c1 = chooseCourse(courseList.size());
			int t = courseList[c1].getMyNeighbours().size();
			if(t == 0) continue;
			else
			{
				c2 = chooseCourse(t);
				break;
			}
			
		}
		int color1 = courseList[c1].getColor();
		int color2 = courseList[c2].getColor();

		visitedCrs.clear();
		for(int j = 0; j < courseList.size(); j++)
		{
			visited[j] = false;
		}
		
		dfs(c1, color1, color2);
		
		swapColor(color1, color2);
		float newPenalty = penaltyLinear();
		
		if(newPenalty > myPenalty)
		{
			swapColor(color1, color2);
		}
		else
		{
			myPenalty = newPenalty;
		}
	}
	return myPenalty;
}

void colorGraphLargestDegree()
{
	orderList = courseList;
	sort(orderList.begin(), orderList.end(), LargestDegreeComparator);
	
	cout << "After applying Largest Degree Heuristic" << endl;
	int ret = getColoring();
	cout << "Timeslots: " << ret << endl;
	float epen = penalty();
	cout << "Exponential Penalty:" << epen << endl;
	float lpen = penaltyLinear();
	cout << "Linear Penalty:" << lpen << endl;
	cout << endl;
	
	cout << "After applying Kempe Chain" << endl;
	float kcpen = kempe_chain_exp(epen);
	cout << "Exponential Penalty: " << kcpen << endl;
	float kcpenl =  kempe_chain_lin(lpen);
	cout << "Linear Penalty: " << kcpenl << endl;
	cout << endl;
	
	cout << "After applying Pair Swap:" << endl;
	float pspen = applyPairSwapExp(kcpen);
	cout << "Exponential Penalty: " << pspen << endl;
	float pspenl =  applyPairSwapLin(kcpenl);
	cout << "Linear Penalty: " << pspenl << endl;
	cout << endl;
}
void colorGraphDSatur()
{
	orderList = courseList;
	sort(orderList.begin(), orderList.end(), BrelazComparator);
	cout << "After applying Smallest Saturation Heuristic" << endl;
	int ret = getDSaturColoring();
	cout << "Timeslots: " << ret << endl;
	float epen = penalty();
	cout << "Exponential Penalty:" << epen << endl;
	float lpen = penaltyLinear();
	cout << "Linear Penalty:" << lpen << endl;
	cout << endl;
	
	cout << "After applying Kempe Chain" << endl;
	float kcpen = kempe_chain_exp(epen);
	cout << "Exponential Penalty: " << kcpen << endl;
	float kcpenl =  kempe_chain_lin(lpen);
	cout << "Linear Penalty: " << kcpenl << endl;
	cout << endl;
	
	cout << "After applying Pair Swap:" << endl;
	float pspen = applyPairSwapExp(kcpen);
	cout << "Exponential Penalty: " << pspen << endl;
	float pspenl =  applyPairSwapLin(kcpenl);
	cout << "Linear Penalty: " << pspenl << endl;
	cout << endl;	
}
void colorGraphLargestEnrollment()
{
	orderList = courseList;
	sort(orderList.begin(), orderList.end(), LargestEnrollmentComparator);
	cout << "After applying Largest Enrollment Heuristic" << endl;
	int ret = getColoring();
	cout << "Timeslots: " << ret << endl;
	float epen = penalty();
	cout << "Exponential Penalty:" << epen << endl;
	float lpen = penaltyLinear();
	cout << "Linear Penalty:" << lpen << endl;
	cout << endl;
	
	cout << "After applying Kempe Chain" << endl;
	float kcpen = kempe_chain_exp(epen);
	cout << "Exponential Penalty: " << kcpen << endl;
	float kcpenl =  kempe_chain_lin(lpen);
	cout << "Linear Penalty: " << kcpenl << endl;
	cout << endl;
	
	cout << "After applying Pair Swap:" << endl;
	float pspen = applyPairSwapExp(kcpen);
	cout << "Exponential Penalty: " << pspen << endl;
	float pspenl =  applyPairSwapLin(kcpenl);
	cout << "Linear Penalty: " << pspenl << endl;
	cout << endl;
}
void colorRandomOrder()
{
	orderList = courseList;
	random_shuffle(orderList.begin(), orderList.end());
	
	cout << "After applying Largest Enrollment Heuristic" << endl;
	int ret = getColoring();
	cout << "Timeslots: " << ret << endl;
	float epen = penalty();
	cout << "Exponential Penalty:" << epen << endl;
	float lpen = penaltyLinear();
	cout << "Linear Penalty:" << lpen << endl;
	cout << endl;
	
	cout << "After applying Kempe Chain" << endl;
	float kcpen = kempe_chain_exp(epen);
	cout << "Exponential Penalty: " << kcpen << endl;
	float kcpenl =  kempe_chain_lin(lpen);
	cout << "Linear Penalty: " << kcpenl << endl;
	cout << endl;
	
	cout << "After applying Pair Swap:" << endl;
	float pspen = applyPairSwapExp(kcpen);
	cout << "Exponential Penalty: " << pspen << endl;
	float pspenl =  applyPairSwapLin(kcpenl);
	cout << "Linear Penalty: " << pspenl << endl;
	cout << endl;
}
void getCourseList(string crsFileNames)
{
	ifstream infile(crsFileNames);
	
	int crsNum, stuNum;
	
	while(!infile.eof())
	{
		infile >> crsNum >> stuNum;
		Course c(crsNum-1, stuNum);
		courseList.push_back(c);	
	}
	infile.close();
}

void getStudentList(string stuFileNames)
{
	ifstream infile(stuFileNames);
	string line;
	int i = 1;
	while( getline(infile,line) ){
		Student s(i);
		stringstream str(line);
		int course;
		while(str>>course){
			s.addCourse(course-1);
		}
		studentList.push_back(s);
		i++;
	}
	infile.close();
}

void initialize(string crsFileName, string stuFileName)
{
	studentList.clear();
	courseList.clear();
	getStudentList(stuFileName);
	getCourseList(crsFileName);
	
	createGraph();
	visited.resize(courseList.size());
}

int main()
{
	srand(time(0));
	string stuFileNames[] = {"car-s-91.stu", "car-f-92.stu", "kfu-s-93.stu", "tre-s-92.stu", "yor-f-83.stu"};
	string crsFileNames[] = {"car-s-91.crs", "car-f-92.crs", "kfu-s-93.crs", "tre-s-92.crs", "yor-f-83.crs"};
	string datasets[] = {"CAR91", "CAR92", "KFU93", "TRE92", "YOR83"};
	
	for(int i = 0; i < 5; i++)
	{
		initialize(crsFileNames[i], stuFileNames[i]);
		cout << datasets[i] << ":" << endl; 
		colorRandomOrder();	
		cout << "=====================================================" << endl;
	}	
}


