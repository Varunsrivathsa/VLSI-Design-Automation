#include<iostream>                                                              
#include<vector>
#include<fstream>                                                                
#include<boost/algorithm/string/split.hpp>                                      
#include<boost/algorithm/string.hpp>
#include<string>
#include <iostream>
#include <sstream> 
#include <regex>
#include <map>
#include <cmath>
#include "time.h"
#include "readFiles.cpp"
#include "readNets.cpp"
#include "readScl.cpp"


void printEverything();
void initialPlacement(int xLimit);
void printCellMap();
void printRowMap();
int rowOverlap();
void updateCenter();
long int wireLength();
void CalcBoundaries();
int macroPlacement();
long int cellOverlap();
void timberWolfAlgorithm();
void update_Temperature();
void initiateMove();
bool checkMove(long int prevCost);
void gnuPlot();

double Temperature;

int main()
{                                                                    
        readNodesFile();
	readWtsFile();
	readPlFile();
	readNetsFile();
	readSclFile();
	//printMap();
	CalcBoundaries();
	//int xLimit=macroPlacement();  
	//initialPlacement(xLimit);
	gnuPlot();
	//updateCenter();
	//rowOverlap();
	//wireLength();
	//cellOverlap();
	timberWolfAlgorithm();
        //printCellMap();
	//printRowMap();                             
	return 0;
}


struct boundaries
{
int minX, maxX, minY, maxY;
};

boundaries b;

void createRowToCellMap()
{
	map<int, row> ::iterator itRow;
	map<string, node> ::iterator itNode;

	for(itRow = rowId.begin(); itRow != rowId.end(); ++itRow)
	{
		for(itNode = nodeId.begin(); itNode != nodeId.end(); ++itNode)
		{
			if(itNode->second.height <= 16)
			{
			if((itRow->second.coOrdinate <= itNode->second.yCoordinate) && ((itRow->second.coOrdinate)+(itRow->second.height)) >= itNode->second.yCoordinate)
			{
				itNode->second.setRowId(itRow->first);
				itRow->second.setCellList(itNode->first);	
			}
			}
		}
	}
}

void CalcBoundaries()
{
int xval,yval;
b.minX = 32767, b.maxX = -32768,b.minY = 32767, b.maxY = -32768;
	map<string, node> ::iterator itNode;
	for(itNode = nodeId.begin(); itNode != nodeId.end(); ++itNode)
	{
		if(itNode->second.terminal == 1)
		{
			xval = itNode->second.xCoordinate;
			yval = itNode->second.yCoordinate;
			if(xval < b.minX)
			{
				b.minX = xval;
			}
			if(xval > b.maxX)
			{
				b.maxX = xval;
			}
			if(xval < b.minY)
			{
				b.minY = yval;
			}
			if(xval > b.maxY)
			{
				b.maxY = yval;
			}
			
		}
	}
	//cout << b.minX << endl;
	//cout << b.maxX << endl;
	//cout << b.minY << endl;
	//cout << b.maxY << endl;

}

int macroPlacement()
{
	int xValue=b.minX,yValue=0;
	xLimit=b.minX;
	map<int, row> ::iterator itRow;
	itRow = rowId.begin();
	int rowHeight = itRow->second.height;
	for(map<string,node>::iterator itNode = nodeId.begin();itNode != nodeId.end();++itNode)
	{
		if(itNode->second.terminal == false && itNode->second.height > rowHeight)
		{	
			if(xValue + itNode->second.width > xLimit)
				{
					xLimit = xValue + itNode->second.width+1;
				}
			if((yValue + itNode->second.height) < b.maxY)
			{
				itNode->second.yCoordinate = yValue;
				itNode->second.xCoordinate = xValue;				
			}
			else
			{	
				
				yValue = 0;
				xValue = xLimit;
				itNode->second.yCoordinate = yValue;
				itNode->second.xCoordinate = xValue;
				

			}
			yValue = yValue + itNode->second.height;
		}
	}
	return xLimit;
}

void initialPlacement(int xLimit)
{
	map<string, node> ::iterator itNode;
	map<int, row> ::iterator itRow=rowId.begin();
	int totalWidth = 0, rowWidth = 0, numNodes =0, cnt=0,count=0, xCord=xLimit,yCord=0;
	float numCellsPerRow = 0;
	for(itNode = nodeId.begin(); itNode != nodeId.end(); ++itNode)
		{
			if(itNode->second.terminal == 0 && itNode->second.height <= 16)
			{
				totalWidth += itNode->second.width;
				numNodes++;
			}
		}
		totalWidth = totalWidth + numNodes;
		//cout << "TotalWidth : " << totalWidth << endl;
		rowWidth = totalWidth/rowId.size();
		RowWidth = rowWidth;
		//cout << "RowWidth :  " << rowWidth << endl;
		numCellsPerRow = ceil(float (numNodes)/rowId.size());
		numCellsPerRow = numCellsPerRow-1;
		//cout << "Number of cells in a row :  " << numCellsPerRow << endl;


for(itNode = nodeId.begin(); itNode != nodeId.end(); ++itNode)
	{
		if(itRow != rowId.end())
		{
			if(itNode->second.terminal == 0)
			{
				if(itNode->second.height == itRow->second.height)
				{
					if(cnt < (numCellsPerRow))
			  		{
					itNode->second.yCoordinate = itRow->second.coOrdinate;
					itNode->second.xCoordinate = xCord;
					xCord += itNode->second.width+1;
					//itRow->second.setCellList(itNode->first);
					cnt++;
					//itNode->second.setRowId(itRow->first);
					
					if(cnt == numCellsPerRow)
					{						
						cnt = 0;
						xCord = xLimit;
						++itRow;	
					}
					}
				}
			}
		}
	}
updateCenter();
createRowToCellMap();
}

void gnuPlot()
{
ofstream myfile ("example.txt");
  	if (myfile.is_open())
  	{
		int x = 0,y = 0,w = 0,h = 0;
	
		for(map<string,node>::iterator it_node = nodeId.begin();it_node != nodeId.end();++it_node)
		{
	
	     		x = it_node->second.xCoordinate;
      			y = it_node->second.yCoordinate;
      			w = it_node->second.width;	
      			h = it_node->second.height;
		
			myfile << x << " " << y << " "<< (x+w)<< " "<<(y+h)<<" "<<endl;
		}


    		//myfile.close();
  	}
  	else cout << "Unable to open file";
}

int rowOverlap()
{
	map<int, row> ::iterator itRow;
	int cost3=0;

	for(itRow = rowId.begin(); itRow != rowId.end(); ++itRow)
	{	
		itRow->second.calcRowOverlap();
		if(itRow->second.overlap >= 0)
		{
			cost3 += itRow->second.overlap;
		}		
	}
		//cout << "row overlap: "<< cost3 << endl;
return cost3;	
}

void updateCenter()
  {
	map<string, node> ::iterator itNode;
	
	int xBy2 =0, yBy2 =0;
	for(itNode = nodeId.begin(); itNode != nodeId.end(); ++itNode)
	{	
		xBy2 = (itNode->second.xCoordinate)+((itNode->second.width)/2);
		yBy2 = (itNode->second.yCoordinate)+((itNode->second.height)/2);	
		itNode->second.setCenter(xBy2,yBy2);			
	}
  }


long int wireLength()
{
	map<int, vector<string>> :: iterator itNet;
	vector<string> :: iterator itCellList;
	int xVal, yVal, wireLength=0;
	cout<< "updating wire length "<< endl;
	for(itNet= netToCell.begin(); itNet != netToCell.end(); ++itNet)
	{
			int minXW = 32767, minYW = 32767, maxXW = -32768 , maxYW = -32768;
			for(itCellList = itNet->second.begin(); itCellList != itNet->second.end(); ++itCellList)
			{
				xVal = nodeId[*itCellList].xBy2;
				yVal = nodeId[*itCellList].yBy2;
				if(xVal < minXW)
				minXW = xVal;
				if(xVal > maxXW)
				maxXW = xVal;
				if(yVal < minYW)
				minYW = yVal;
				if(yVal > maxYW)
				maxYW = yVal;
			}
			wireLength += abs((maxXW-minXW)) + abs((maxYW-minYW));
	}
			cout << "New Wire length : " << wireLength << endl;
return wireLength;
}

long int cellOverlap()
{

map<string,node>::iterator nodeit=nodeId.begin();
map<int,row>::iterator rowit;
int x1=0,w1=0,x2=0,w2=0,h1=0,h2=0,overlap=0,i=0;
long int totaloverlap=0;

vector<string>list;
for(rowit=rowId.begin();rowit!=rowId.end();++rowit)
{
	overlap=0;
	list=rowit->second.sortByX();
	overlap=0;
	for(i=0;i<list.size();i++)
	{
		node nodeobj=nodeId.find(list[i])->second;
		x1=nodeobj.xCoordinate;
		w1=nodeobj.width;
		h1=nodeobj.height;
		i++;
		if(i==list.size())
		{
			break;		
		}
		x2=nodeId.find(list[i])->second.xCoordinate;
		w2=nodeId.find(list[i])->second.width;
		h2=nodeId.find(list[i])->second.height;
		if(x2<=(x1+w1)&&(x2+w2)>=(x1+w1))
		{
			overlap+=((x1+w1)-x2)*h1;
		}
		else if(x2>=x1 && x2<=(x1+w1) && (x2+w2)<=w1)
		{
			overlap+=w2*h2;
		}
		
	}
totaloverlap+=overlap;

}
//cout << "Total cell overlap :" << totaloverlap << endl;
return totaloverlap;
}

void initiateMove()
{
srand48(time(NULL));
int randomCellnum, randRow, randXcord,i;
stringstream randomCellTemperature;
string randomCellStr,randomCell;
node n;
row r;
map<string, node> ::iterator itNode;
map<int, row> ::iterator itRow;
bool accept;
long int cost2,cost1,prevCost;
int cost3;
	//cost3 = rowOverlap();
	cost1 = wireLength();
	cost2 = cellOverlap();
	prevCost = cost1 + cost2;


	for(int i=0; i<11; i++)
	{
		randomCellnum = rand() % 12506;
		//cout << randomCellnum << endl;
	}
	randomCellTemperature << randomCellnum;
	randomCellStr = randomCellTemperature.str();
	randomCell = "a" + randomCellStr;

	//cout<< randomCell << endl;
	randRow = rand() % 144;
	//cout<< randRow << endl;
	randXcord = rand() % 910+1426; 
	//cout<< 	randXcord <<  endl;

	itRow = rowId.find(randRow);
	itNode = nodeId.find(randomCell);
	n = itNode->second;
	r = itRow->second;
	//r.coOrdinate = itRow->second.coOrdinate;
	//n.yCoordinate = itNode->second.yCoordinate;
	//n.xCoordinate = itNode->second.xCoordinate;
	cout<<" moving cell "<<randomCell<<" to Row "<<randRow<< endl;
	itNode->second.yCoordinate = itRow->second.coOrdinate;
	itNode->second.xCoordinate = randXcord;
	
	
	
	rowId[itNode->second.cellRowId].cellList.erase(std::remove(rowId[itNode->second.cellRowId].cellList.begin(), rowId[itNode->second.cellRowId].cellList.end(),randomCell), rowId[itNode->second.cellRowId].cellList.end());
	itRow->second.cellList.push_back(randomCell);
	itNode->second.cellRowId = randRow;
	updateCenter();
	
	accept = checkMove(prevCost);
	if(!accept)
	{
		itNode->second = n;
		itRow->second.cellList.erase(std::remove(itRow->second.cellList.begin(),itRow->second.cellList.end(),randomCell), itRow->second.cellList.end());
		rowId[itNode->second.cellRowId].cellList.push_back(randomCell);
	}	
	//n.printParameter();
	//itNode->second.printParameter();
		
}

void update_Temperature()
{

if(Temperature>5000)
{
	Temperature=0.8*Temperature;
}
else if(Temperature<=5000 && Temperature >200)
{
	Temperature=0.94*Temperature;
}
else if(Temperature<200)
{
	Temperature=0.8*Temperature;
}
else if(Temperature<1.5)
{
	Temperature=0.1*Temperature;
}
 cout<<" new temperature is "<< Temperature <<endl;
}

bool checkMove(long int prevCost)
{
srand(time(NULL));
long int cost2=0,cost1=0,newCost=0;
int cost3=0;
int delCost=0;
double factor=0;
double prob = drand48(); 
		cout<<"Checking validity of the move"<<endl;
		cost1 = wireLength();
		cost2 = cellOverlap();
		//cost3 = rowOverlap();
		newCost = cost1 + cost2;
		delCost = newCost - prevCost;
		factor = exp(-delCost/Temperature);

		if(delCost < 0 ) //|| prob > (exp(-delCost/Temperature)) )
		{
			prevCost = newCost;
			cout << "Cell position is updated " << endl;
			return true; 
		}
		else
		{
			cout << "Move is NOT valid, reverting" << endl;
			return false;
		}	
}

void timberWolfAlgorithm()
{
	long int cost2,cost1;
	int cost3;
	int xLimit=macroPlacement();  
	initialPlacement(xLimit);
        //printCellMap();
	//printRowMap();
	//cost2 = cellOverlap();
	//cost3 = rowOverlap();
	Temperature = 400000;
	int i = 10;
	
	int delCost;


	while (Temperature > 0.1 )
	{
		i=100;
		while(i > 0)
		{

		initiateMove();
		i--;
		update_Temperature();	
		}
	}
	
}

void printCellMap()
{
	map<string, node> ::iterator itNode;

	for(itNode = nodeId.begin(); itNode != nodeId.end(); ++itNode)
		{
			
			itNode->second.printParameter();	
			
		}
}

void printRowMap()
{
	map<int, row> ::iterator itRow;

	for(itRow = rowId.begin(); itRow != rowId.end(); ++itRow)
		{
			
			itRow->second.printParameter();	
			
		} 
	
}
