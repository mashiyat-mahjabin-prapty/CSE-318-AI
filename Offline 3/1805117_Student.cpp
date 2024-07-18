#include<bits/stdc++.h>
using namespace std;

class Student{
	int id;
	vector<int> myCourses;
	
public:
	Student(int id)
	{
		this->id = id;		
	}		
	int getID()
	{
		return this->id;
	}
	void setID(int id)
	{
		this->id = id;
	}
	vector<int> getMyCourses()
	{
		return this->myCourses;
	}
	void setMyCourses(vector<int> mycourses)
	{
		this->myCourses = mycourses;
	}
	void addCourse(int c)
	{
		this->myCourses.push_back(c);
	}
};
