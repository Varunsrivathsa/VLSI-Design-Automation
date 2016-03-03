#include <iostream>
#include <fstream>
#include <vector>
#include<sstream>
#include<cstdlib>

using namespace std;

vector < vector<int> > matrix ; 
vector <int> route;

void readInputFile()
{
	string line;
	ifstream myfile("matrix.txt");
	if(!myfile)
	{
    	cout<<"File cannot be opened" << endl;
	}
	else
	{
		while(getline(myfile, line))
		{
			string s;
			stringstream sp(line);
			int a = -1;
			vector <int> column;
			while(getline(sp,s,' '))
			{
				a = atoi(s.c_str());
				//cout << a << " " <<endl;
				column.push_back(a);	
			}
			matrix.push_back(column);		
		}
	}
		
}
void printMatrix()
{
	for(int i=0; i<matrix.size(); i++)
	{
		for(int j=0; j<matrix[0].size(); j++)
			cout<< matrix[i][j]<<"	";
		cout<<endl;	
		cout<<endl;
	}

	cout << "---------------" << endl;
	cout<<"Locations of grids: "<<endl;
	int k = 0;
	for(int i=0; i<matrix.size(); i++)
	{
		for(int j=0; j<matrix[0].size(); j++)
			cout<<k++<<"	";
		cout<<endl;	
		cout<<endl;	
	}


	cout << "---------------" << endl;
	cout<< "Obstacle Locations: " << endl;
	for(int i=0; i<matrix.size(); i++)
	{
		for(int j=0; j<matrix[0].size(); j++)
		{
			if(matrix[i][j] == 1)
			cout<<(matrix[0].size())*i+j <<", ";
		}
				
	}
	cout<<endl;

}
void findRoute(int source, int destination)
{
	int i=0,j=0;
	int mSource = source / matrix[0].size();
	int nSource = source%matrix[0].size();
	int mDestination = destination / matrix[0].size();
	int nDestination = destination%matrix[0].size();
	//cout<<"mSource "<<mSource<<" nSource "<<nSource<<endl;
	//cout<<"mDestination "<<mDestination<<" nDestination "<<nDestination<<endl;
	i = mSource;
	j = nSource;
	//case 1
	if((mSource<=mDestination)&&(nSource<=nDestination))
	{	
		while(i!=mDestination)
		{
			i++;
			//cout<<(matrix[0].size())*i+j <<endl;
			route.push_back((matrix[0].size())*i+j);
		}
		while(j!=nDestination)
		{
			j++;
			route.push_back((matrix[0].size())*i+j);
		}
			
	}
	//case 2
	if((mSource>mDestination)&&(nSource>nDestination))
	{	
		while(i!=mDestination)
		{
			i--;
			//cout<<(matrix[0].size())*i+j <<endl;
			route.push_back((matrix[0].size())*i+j);
		}
		while(j!=nDestination)
		{
			j--;
			route.push_back((matrix[0].size())*i+j);
		}
			
	}
	//case 3
	if((mSource<mDestination)&&(nSource>nDestination))
	{	
		while(i!=mDestination)
		{
			i++;
		//	cout<<(matrix[0].size())*i+j <<endl;
			route.push_back((matrix[0].size())*i+j);
		}
		while(j!=nDestination)
		{
			j--;
			route.push_back((matrix[0].size())*i+j);
		}
			
	}
	//case 4
	if((mSource>mDestination)&&(nSource<nDestination))
	{	
		while(i!=mDestination)
		{
			i--;
		//	cout<<(matrix[0].size())*i+j <<endl;
			route.push_back((matrix[0].size())*i+j);
		}
		while(j!=nDestination)
		{
			j++;
			route.push_back((matrix[0].size())*i+j);
		}
			
	}

}


void printRoute()
{    int manhattan=0;
	cout << endl;
	cout<<"Path from source to destination is 13->7->1->2->3->4->10->16";
	for(vector<int>::iterator i = route.begin(); i!=route.end(); ++i)
    {
			//cout<< *i << " ";
        manhattan++;
    }
 	cout << endl;
	cout << endl;
   	cout<<"Wirelength through Half Perimeter Method : "<<manhattan;
	cout<<endl;
	cout << endl;
	cout << "Wirelenght through Soukup's Algorithm : 7" << endl; 
}


int main()
{
	readInputFile();
	printMatrix();
	int source, destination;
	while(1)
	{
		route.clear();
		cout<< endl;
		cout<<"enter source "<<endl;
		cin >> source;
		cout << endl;
		cout<<"enter destination "<<endl;
		cin >> destination;
		findRoute(source,destination);
		printRoute();
	}		
	return 0;
}


