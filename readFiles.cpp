#include<iostream>                                                              
#include<vector>
#include<fstream>                                                                
#include<boost/algorithm/string/split.hpp>                                      
#include<boost/algorithm/string.hpp>
#include<string>
#include <iostream> 
#include <regex>
#include <map>

using namespace std;

class node;
map<string, node> nodeId;
 
 class node
{

public:

string nodeName;
int width;
int height;
int weight;
int terminal;
int xCoordinate;
int yCoordinate;
int xBy2;
int yBy2;
string orientation;
int cellRowId;
vector <int> Netlist;

void setParameterNodes(string nodeName, int width, int height,int terminal)
   {
 	this->nodeName = nodeName;
 	this->width = width;
	this->height = height;
	this->terminal = terminal;
   }

void setParameterWts(int weight)
   {
 	this->weight = weight;
   }

void setParameterPl(int xCoordinate,int yCoordinate,string orientation)
{
	this->xCoordinate = xCoordinate;
	this->yCoordinate = yCoordinate;
	this->orientation = orientation;
}

void setRowId(int cellRowId)
{
	this->cellRowId = cellRowId;
}

void setNetList(int NetId)
{
	Netlist.push_back(NetId);
}

void setCenter(int xBy2, int yBy2)
{
	this->xBy2 = xBy2;
	this->yBy2 = yBy2;
}

void printParameter()
   {
 	cout <<"nodeName      " << this->nodeName << endl;
 	cout <<"Width         " << this->width << endl;
 	cout <<"Height        " << this->height << endl;
	cout <<"Weight        " << this->weight << endl;
	cout <<"X_Co-ordinate " << this->xCoordinate << endl;
	cout <<"Y_Co-ordinate " << this->yCoordinate << endl;
 	cout <<"X/2           " << xBy2 << endl;
	cout <<"Y/2           " << yBy2 << endl;	
	cout <<"Orientation   " << this->orientation << endl;
	cout <<"cellRowId     " << this->cellRowId << endl;
	cout <<"terminal      " << this->terminal << endl;
	cout <<"NetList       " ;
	vector <int> :: iterator it2;
	for(it2=Netlist.begin(); it2 != Netlist.end(); ++it2)
	{
		cout << *it2 << " ";
	} 
	cout << "\n" << endl;
   }
};

void readNodesFile()
   {
    	fstream file;
    	string buf;
	int i=0;
    	vector<string> strVec;                                                      
    	using boost::is_any_of;
	int Value=2;                                                     

    	file.open("ibm01.nodes", ios :: in);

	while (getline(file, buf))
	{       
		i++;
		if(i>7)
		{
			boost::algorithm::split(strVec,buf,is_any_of(" "),boost::token_compress_on);
			node n; 
			if (strVec[4] == "terminal")
			{
				Value = 1;
			}
			else
			{
				Value = 0;
			}
			n.setParameterNodes(strVec[1],atoi(strVec[2].c_str()),atoi(strVec[3].c_str()),Value);
			nodeId.insert(pair<string,node>(strVec[1],n));
		}
	}
	file.close();
   }

void readWtsFile()
   {
	fstream file;
	string buf;
	int i=0;
	vector<string> strVec;
	using boost::is_any_of;
	map<string, node>::iterator itr;

	file.open("ibm01.wts", ios :: in);

	while (getline(file, buf))
	{       
		i++;
		if(i>5)
		{
			boost::algorithm::split(strVec,buf,is_any_of(" "),boost::token_compress_on);
			nodeId[strVec[1]].setParameterWts(atoi(strVec[2].c_str()));

		}
	}
	file.close();
   }



void readPlFile()
   {
    	fstream file;
    	string buf;
	int i=0;
    	vector<string> strVec;                                                      
    	using boost::is_any_of;                                                     

    	file.open("ibm01.pl", ios :: in);

	while (getline(file, buf))
	{       
		i++;
		if(i>6)
		{
			boost::algorithm::split(strVec,buf,is_any_of(" "),boost::token_compress_on);
			nodeId[strVec[0]].setParameterPl(atoi(strVec[1].c_str()),atoi(strVec[2].c_str()),strVec[4]);

		}
	}
	file.close();
   }
