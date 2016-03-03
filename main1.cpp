



#include <iostream>
#include<fstream>
#include<vector>
#include<map>
#include<list>
#include<sstream>
#include<cstdlib>
#include<string>
#include<queue>
#include<algorithm>
#include "cell.h"





using namespace std;

//int cell[]={1,2,3,4,5,6,7,8};

//int part[]={0,1,0,0,1,1,0,1};


int numOfCells = 8;
int numOfNets;
int cutSetSize = 0;
float ratioCut = 0.6;
int areaOfPartitionA = 0;
int areaOfPartitionB = 0;
int totalArea = 0;
int maxAreaCell = 0;
map<int,Cell> cellIdToCellMap;
map<int, list<int> > netToCellListMap;
map<int, list<int> > gainToCellIdListMap;
vector<int> gainVector;

void readAreaFile();
void readNetListFile();
std::list<Cell> split(std::string str,char delimiter);
void printCellIdToCellMap (/*map<int,Cell> cellIdToCellMap*/);
void printNetToCellListMap (/*map<int, list<int> > netToCellListMap*/);
void printGainToCellIdListMap();
void assignPartition();
int calculate_FofS(int A);
int calculate_TofS(int A);
int calculateGain(int A);
int calculateCutsetSize();
int makeGainBucket();
int computeAreaofPartition(int partition);
int computeAreaTotal();
int computeCellMaxArea();
bool checkAreaConstraint();
void updateGainBucket(int cellId);
void initiateCellMove();









int main ()
{

readAreaFile();
assignPartition();
readNetListFile();

printCellIdToCellMap ();
printNetToCellListMap();
int g = calculateGain(3);
cout<<"Gain of  is   "<<g<<endl;
cutSetSize = calculateCutsetSize();
cout<<"Cutset size "<<cutSetSize<<endl;
makeGainBucket();
int a = computeAreaofPartition(0);
cout<<"area of partition 0 is "<<a<<endl;
int b = computeAreaofPartition(1);
cout<<"area of partition 1 is "<<b<<endl;
totalArea = computeAreaTotal();
cout<<"Total area is "<<totalArea<<endl;
maxAreaCell = computeCellMaxArea();
cout<<"Max area among Cells "<<maxAreaCell<<endl;
bool isAreaConstraint = checkAreaConstraint();
cout<< " area constraint is "<<isAreaConstraint<<endl;
initiateCellMove();
printCellIdToCellMap();


return 0;
}


std::list<int>& split(std::string str,char delimiter,int i,std::list<int>& cellList)
{
    std::stringstream sp(str);
   // std::list <Cell> data;
    std::string t;
    int t1;
    while(getline(sp,t,delimiter))
    {
		
        t1=atoi(t.c_str());
        //Cell temp = cellIdToCellMap[t1];
		//temp.netList.push_back(i);
		cellIdToCellMap[t1].netList.push_back(i);
		//cout<<"t1  "<<t1<<endl;
		//cout<<"temp.CellID "<<temp.cellID<<endl;
        cellList.push_back(t1);
    }
    return cellList;
}



void readNetListFile()
{
	int count =0;
	string line;
	ifstream myfile("ibm01.hgr");
	if(!myfile)
	{
    		cout<<"File cannot be opened" << endl;
	}
	else
	{
   		int a=0;
    		while(getline(myfile, line)&&(count<numOfCells))
    		{  
			list<int> cellList; 
        		if(a >= 1)
        		{
				
				cellList = split(line,' ',a,cellList);
				netToCellListMap.insert(pair<int,list<int> >(a,cellList));
			}
			else
			{
	   			std::stringstream sp(line);
           			std::string t;
		   		int b[3];
		 		int i=0;
           			while(getline(sp,t,' '))
				{
		   			b[i] = atoi(t.c_str());
					i++;
				}
	   			numOfNets = b[0];
				count++;
	   			//numOfCells = b[1];
			}
 
			list<int>::iterator i;
	    		for( i =cellList.begin(); i != cellList.end(); ++i)
			cout << (*i)<< " ";
	    		cout << endl;
        		a++;
      		}
	}
   	cout<<"numOfNets  "<<numOfNets<<endl;
    	cout<<"numOfCells "<<numOfCells <<endl;
}

void readAreaFile()
{
	string line;
	int cellCount = 1;
	
	ifstream myfile("ibm01.are");
	if(!myfile)
	{
    	cout<<"File cannot be opened" << endl;
	}
	else
	{
   		while(getline(myfile,line)/*&& (cellCount<=numOfCells)*/ )
    		{
        		std::stringstream sp(line);
           		std::string t;
			Cell temp;
			int b[2];
	 		int i=0;
           		while(getline(sp,t,' '))
			{
 				b[i] = atoi(t.c_str());
				i++;
			}
			//cout<<b[0]<<" "<<endl;
			cout<<b[1]<<" "<<endl;
			temp.cellID = cellCount;
			if(b[1]==0)
			break;
			temp.area = b[1];
			temp.isLocked == false;
			cellIdToCellMap.insert(pair<int,Cell>(cellCount,temp));
			cellCount ++;
        	}
        	cout<<"Cell Count is "<<cellCount-1<<endl;
		numOfCells = cellCount-1;
    	}
   
}

void printCellIdToCellMap ()
{

  cout<<"CellID	Cell    area	partition	netlist   	"<<endl;
  for(map<int,Cell>::const_iterator it1 = cellIdToCellMap.begin();
    it1!= cellIdToCellMap.end(); ++it1)
    {
		cout<<it1->first<<"	"<<(it1->second).cellID<<"	 "<<(it1->second).area<<"	"<<(it1->second).partition<<"  		   ";
		for(list<int>::const_iterator it2 = (it1->second).netList.begin(); it2!=(it1->second).netList.end();++it2)
		cout<<(*it2)<<" ";
		cout<<endl; 	
    }


} 





void printNetToCellListMap ()
{
 
    cout<<endl<<"net	Cell List "<<endl;
	for(map<int, list<int> >::const_iterator it1 = netToCellListMap.begin();
    it1!= netToCellListMap.end(); ++it1)
    {
       cout<<it1->first<<"	";
       for(list<int>::const_iterator it2 =  it1->second.begin(); it2 != it1->second.end(); ++it2)
       {
	       cout<<(*it2)<<" "; 
	   }
       cout<<endl;
    }
}   


void printGainToCellIdListMap()
{
   if(gainToCellIdListMap.empty())
   {	
	cout<<"gain bucket empty !!!"<<endl;
	return;		
   }
   cout<<"gain 	Cell list"<<endl;
  for(map<int,list<int> >::const_reverse_iterator it1 = gainToCellIdListMap.rbegin(); it1 != gainToCellIdListMap.rend(); ++it1)
  {
	cout<<it1->first<<"	";
	for(list<int>::const_iterator it2 = (it1->second).begin(); it2!= (it1->second).end(); ++it2)
	{
		cout<<*it2<<" ";
	}
	cout<<endl;
   }
 	


}

void assignPartition()
{
	/*cellIdToCellMap[1].partition = 0;
	cellIdToCellMap[2].partition = 1;
	cellIdToCellMap[3].partition = 0;
	cellIdToCellMap[4].partition = 0;
	cellIdToCellMap[5].partition = 1;
	cellIdToCellMap[6].partition = 1;
	cellIdToCellMap[7].partition = 0;
	cellIdToCellMap[8].partition = 1;*/
        for(int i = 0; i <= numOfCells ; i++)
	{
		if(i<4500)
		cellIdToCellMap[i].partition = 0;
		else
		cellIdToCellMap[i].partition = 1;

	}

}


int calculate_FofS(int A)
{
   int FofS = 0;
   
   int temp =	A;
   //cout<<"temp.partition = "<< temp.partition<<endl;
   for(list<int> ::const_iterator it1 = cellIdToCellMap[A].netList.begin(); it1!=cellIdToCellMap[A].netList.end();++it1)
 	{
		int FofS_net =0;
    		for(list<int>::const_iterator it2 = netToCellListMap[*it1].begin(); it2!= netToCellListMap[*it1].end();++it2)
			{
				if(cellIdToCellMap[temp].partition == cellIdToCellMap[*it2].partition)
				{
					FofS_net++;
				}
			 	//cout<<"current Cell ID "<<*it2<<" "<< "partition " << cellIdToCellMap[*it2].partition <<endl;						
			    
			}
	   			if(FofS_net<=1)
			      FofS++;
	}
   return FofS;
	
}





int calculate_TofS(int A)
{
	int TofS = 0;
  	int temp = A;
   	for(list<int> ::const_iterator it1 = cellIdToCellMap[A].netList.begin(); it1!=cellIdToCellMap[A].netList.end();++it1)
 		{
	
    		int TofS_net =0;
    		for(list<int>::const_iterator it2 = netToCellListMap[*it1].begin(); it2!= netToCellListMap[*it1].end();++it2)
			{
			   	if(cellIdToCellMap[temp].partition != cellIdToCellMap[*it2].partition)
				{
					TofS_net++;
				}
			//	cout<<"current Cell ID "<<it2->cellID<<" ";//<< "partition " << it2->partition <<endl;						
			    	
			}
		    if(TofS_net==0)
		      TofS++;
		 }
  				
		 
		
   return TofS;
}

int calculateGain(int A)
{ 
    int FofS=calculate_FofS(A);
    int TofS=calculate_TofS(A) ;
	return (FofS-TofS); 	
}


int calculateCutsetSize()
{ 
	int cutsize = 0;
    for(map<int, list<int> >::const_iterator it1 = netToCellListMap.begin();
    it1!= netToCellListMap.end(); ++it1)
    {
	   int temp = it1->second.front();
	   	 
       for(list<int>::const_iterator it2 =  it1->second.begin(); it2 != it1->second.end(); ++it2)
       {
		  
		   if(cellIdToCellMap[temp].partition != cellIdToCellMap[*it2].partition)
		   {
				cutsize++;
				break;
		   }
	}
    }
 	return cutsize;
}   


int makeGainBucket()
{
	int gain =0;
	gainToCellIdListMap.clear();
		
	for(map<int,Cell>::iterator it1 = cellIdToCellMap.begin();it1!= cellIdToCellMap.end(); ++it1)
	{
		if((it1->second).getIsLocked() == false)
		{
		gain = calculateGain(it1->first);
		(it1->second).gain = gain;
	 	map<int, std::list<int> >::iterator finder;
		finder = gainToCellIdListMap.find(gain);
		if(finder==gainToCellIdListMap.end())
		{
			list<int> celllist;
			//cout<<"inserting cell "<<it1->first<<" into gain bucket "<<gain<<endl;
			celllist.push_back(it1->first);
			gainToCellIdListMap.insert(pair<int,list<int> >(gain,celllist));
			
		}
		else
		finder->second.push_back(it1->first);
		}
	}
	printGainToCellIdListMap();

}
   
	

int computeAreaofPartition(int partition)
{
	int sumArea = 0;
	for(map<int,Cell>::const_iterator it1 = cellIdToCellMap.begin();it1!= cellIdToCellMap.end(); ++it1)
    	{
		if(it1->second.partition == partition)
		{
			sumArea+=it1->second.area;
		}
	}
	return sumArea;
	
}

int computeAreaTotal()
{
	return (computeAreaofPartition(0) + computeAreaofPartition(1));
}

int computeCellMaxArea()
{
	int maxArea = cellIdToCellMap[1].area ;
	for(map<int,Cell>::const_iterator it1 = cellIdToCellMap.begin();
    it1!= cellIdToCellMap.end(); ++it1)
    {
		if(maxArea < (it1->second).area)
		{
			maxArea=it1->second.area;
		}
	}
 	return maxArea;
}



bool checkAreaConstraint()
{
    int areaPartitionA = computeAreaofPartition(0);
	int areaPartitionB = computeAreaofPartition(1);
	if (((ratioCut*totalArea - maxAreaCell)<= areaPartitionA)&&(areaPartitionA<=(ratioCut*totalArea + maxAreaCell)))
		return true;
	else 
		return false;
}

void initiateCellMove()
{
    	int initialCutset = calculateCutsetSize();
	int cutSet = 0;
	int counter=0;
	cout<<"initial Cutset = "<<initialCutset<<endl;
	int cellId =0;
	int temp =0;
	map<int,list<int> >::reverse_iterator it1 = gainToCellIdListMap.rbegin();

    	 
		while( it1 != gainToCellIdListMap.rend())
		{
			cout<<"for cell of gain "<<it1->first<<endl;
			bool setbreak = false;
			list<int>::iterator it2 = (it1->second).begin();
		    	while( it2!= (it1->second).end())
		 		{
					if(cellIdToCellMap[*it2].getIsLocked()== false)
						{
							cout<<"toggling bit of cell "<<cellIdToCellMap[*it2].cellID<<" "<<cellIdToCellMap[*it2].partition<<endl;
							cellIdToCellMap[*it2].changePartition();
							cout<<"new partition "<<cellIdToCellMap[*it2].partition<<endl;
							if(checkAreaConstraint() == false)
							{
								cellIdToCellMap[*it2].changePartition();
								cout<<"reverting partition -> area constraint not met" <<endl;
								++it2;
								continue;
							}
							else
							{
								cellIdToCellMap[*it2].setIsLocked();
								cout<<"Cell "<<*it2 <<" isLocked" << cellIdToCellMap[*it2].getIsLocked()<<endl;
								counter++;	
               							cutSet =  calculateCutsetSize();
								cout<<"cutset size after "<< counter <<" move =  "<<cutSet<<endl;
								setbreak = true;
								break;
							}
                       				}
					
				//	cout<<"isLocked "<<cellIdToCellMap[*it2].getIsLocked()<<endl;
		  	 	}
			if(setbreak==true)
			{
				makeGainBucket();
				it1=gainToCellIdListMap.rbegin();
				//it2 = (it1->second).begin();
				continue;
			}	
			it1++;		
		}
		
	
}

void updateGainBucket(int cellId)
{
	int gain =0;
	for(list<int> ::iterator it1 = cellIdToCellMap[cellId].netList.begin(); it1!=cellIdToCellMap[cellId].netList.end();++it1)
 	{
		 
    		for(list<int>::iterator it2 = netToCellListMap[*it1].begin(); it2!= netToCellListMap[*it1].end();++it2)
		{	
			
			for(map<int,list<int> >::reverse_iterator it3 = gainToCellIdListMap.rbegin(); it3 != gainToCellIdListMap.rend(); ++it3)
		    	{	
				list<int>::iterator it4 = (it3->second).begin();
				while(it4 != (it3->second).end())
		 		{
					if(*it4 == *it2)
					{
						it4 = (it3->second).erase(it4);
						cout<<"removing cell from gain list "<< *it2<<endl;
						continue;
					} 
					++it4;
				}
				
			}

			gain = 	calculateGain(*it2);
			map<int, std::list<int> >::iterator finder;
			finder = gainToCellIdListMap.find(gain);
			if(finder==gainToCellIdListMap.end())
			{
				list<int> celllist;
				celllist.push_back(*it2);
				gainToCellIdListMap.insert(pair<int,list<int> >(gain,celllist));
			
			}
			else
			finder->second.push_back(*it2);
			
				
		}
	}
	cout<<"updated gain bucket is"<<endl;	
	cout<<"gain 	Cell list"<<endl;
    	for(map<int,list<int> >::const_reverse_iterator it1 = gainToCellIdListMap.rbegin(); it1 != gainToCellIdListMap.rend(); ++it1)
		{
			cout<<it1->first<<"	";
			for(list<int>::const_iterator it2 = (it1->second).begin(); it2!= (it1->second).end(); ++it2)
			{
				cout<<*it2<<" ";
			}
			cout<<endl;
		}


}


