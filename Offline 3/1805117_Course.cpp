#include<bits/stdc++.h>
using namespace std;

class Course{
	int id;
	set<int> myNeighbours;
	int numStu;
	int color;
	int saturation;
	
public:
	Course(int id)
	{
		this->id = id;
		this->color = -1;
		this->saturation = 0;
	}
	Course(int id, int numStu)
	{
		this->id = id;
		this->numStu = numStu;
		this->color = -1;
		this->saturation = 0;
	}
	int getNumStu()
	{
		return this->numStu;
	}
	void setNumStu(int numStu)
	{
		this->numStu = numStu;
	}
	int getID()
	{
		return this->id;
	}
	void setID(int id)
	{
		this->id = id;
	}
	int getColor()
	{
		return this->color;
	}
	void setColor(int color)
	{
		this->color = color;
	}
	set<int> getMyNeighbours()
	{
		return this->myNeighbours;
	}
	void addNeighbour(int c)
	{
		this->myNeighbours.insert(c);
	}
	int getSaturation(){
		return saturation;
	}
	void incrementSaturation(){
		saturation++;
	}
};
