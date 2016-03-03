#include<iostream>                                                              
#include<vector>
#include<fstream>                                                                
#include<boost/algorithm/string/split.hpp>                                      
#include<boost/algorithm/string.hpp>
#include<string>
#include <iostream> 
#include <map>
using namespace std; 
 
class row;
map<int, row> rowId;
int RowWidth;
int xLimit;
 class row
{

public:
int Id;
int coOrdinate;
int height;
int siteWidth;
int siteSpacing;
string siteOrient;
string siteSymmetry;
int siteRowOrigin;
int numSites;
int overlap;
vector <string> cellList;

void setId(int Id)
{
	this->Id=Id;
}


void setParameterRows(int coOrdinate,int height,int siteWidth,int siteSpacing,string siteOrient,string siteSymmetry,int siteRowOrigin,int numSites)
   {
 	this->coOrdinate = coOrdinate;
 	this->height = height;
	this->siteWidth = siteWidth;
	this->siteSpacing = siteSpacing;
 	this->siteOrient = siteOrient;
	this->siteSymmetry = siteSymmetry;
	this->siteRowOrigin = siteRowOrigin;
	this->numSites = numSites;
   }

void setCellList(string cellId)
 {
	cellList.push_back(cellId);	
 }

vector<string> sortByX()
{
int i=0,x=0;
map<int,string> sortx;
map<int,string>::iterator it;
vector<string>::iterator itl;
vector<string>list;
for(i=0;i<this->cellList.size();i++)
{
	x=nodeId.find(cellList[i])->second.xCoordinate;
	sortx.insert(pair<int,string> (x,cellList[i]));
}
for(it=sortx.begin();it!=sortx.end();++it)
{
	list.push_back(it->second);
}
this->cellList=list;
return this->cellList;
}

void calcRowOverlap()
{
	vector <string> :: iterator it1;
	int xLast=0, widthLast = 0;

	xLast = nodeId[cellList[cellList.size()-1]].xCoordinate;
	widthLast = nodeId[cellList[cellList.size()-1]].width;
	overlap = xLast + widthLast - (RowWidth+xLimit);
	
	this ->overlap = overlap;	
}

void printParameter()
   {
	cout <<"rowId          " << this->Id <<" "<< endl;
 	cout <<"Row-Co-ordinate " << this->coOrdinate << endl;
 	cout <<"height          " << this->height << endl;
 	cout <<"siteWidth       " << this->siteWidth << endl;
	cout <<"siteSpacing     " << this->siteSpacing << endl;
	cout <<"siteOrientation " << this->siteOrient << endl;
	cout <<"siteSymmetry    " << this->siteSymmetry << endl;
	cout <<"siteRowOrigin   " << this->siteRowOrigin << endl;
	cout <<"numSites        " << this->numSites << endl;
	cout <<"Overlap of this row   " << overlap<<endl;
	cout <<"cellsInRow      " << " ";
	vector <string> :: iterator it1;
	for(it1 = cellList.begin(); it1 != cellList.end(); ++it1)
	{
		cout<< *it1 << " ";
	} 
	cout << "\n" << endl;
   }
};

void readSclFile()
   {
    	fstream file;
    	string buf;
	int i=0,j=0,Id=1;
    	vector<string> strVec;                                                      
    	using boost::is_any_of;
                                                     
	int coOrdinate;
	int height;
	int siteWidth;
	int siteSpacing;
	string siteOrient;
	string siteSymmetry;
	int siteRowOrigin;
	int numSites;

    	file.open("ibm01.scl", ios :: in);

	while (getline(file, buf))
	{       
		i++;
		if(i>8)
		{	
			boost::algorithm::split(strVec,buf,is_any_of(" "),boost::token_compress_on);
			j = i%9;
			if(j == 1)
			{
				coOrdinate = atoi(strVec[3].c_str());			
			}
			else if(j == 2)
			{
				height = atoi(strVec[3].c_str());
			}
			else if(j == 3)
			{
				siteWidth = atoi(strVec[3].c_str());			
			}
			else if(j == 4)
			{
				siteSpacing = atoi(strVec[3].c_str());			
			}
			else if(j == 5)
			{
				siteOrient = strVec[3];
			}
			else if(j == 6)
			{
				siteSymmetry = strVec[3];
			}
			else if(j == 7)
			{
				siteRowOrigin = atoi(strVec[3].c_str());
				numSites = atoi(strVec[6].c_str());
			}
			else if(j == 8)
			{
				row r;				
				r.setId(Id);
				rowId.insert(pair<int,row>(Id,r));
				rowId[Id].setParameterRows(coOrdinate,height,siteWidth,siteSpacing,siteOrient,siteSymmetry,siteRowOrigin,numSites);
				Id++;
			}
			
		}
	}
	file.close();
   }

