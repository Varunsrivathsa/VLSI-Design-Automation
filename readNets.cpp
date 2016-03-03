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

map<int, vector<string> > netToCell;

void readNetsFile()
{
    	fstream file;
    	string buf;
	int i=0,a=0,j=0,NetId=1;
    	vector<string> strVec;                                                      
    	using boost::is_any_of;

	regex find ("\\b(NetDegree : )");
	smatch match;
	string Out;                                                    

    	file.open("ibm01.nets", ios :: in);

	while (getline(file, buf))
	{       
		i++;
		if(i>7)
		{
			regex_search(buf, match, find);
			Out = match.suffix();
			a = atoi(Out.c_str());
			vector<string> strTemp;
			for (j=0; j<a; j++)
			{
				
				getline(file,buf);
				boost::algorithm::split(strVec,buf,is_any_of(" "),boost::token_compress_on);
				strTemp.push_back(strVec[1]);
				nodeId[strVec[1]].setNetList(NetId);
			}
			netToCell.insert(pair<int, vector <string> >(NetId,strTemp));
			NetId++;
		}
		
   	}
}

void printMap()
{
	map<int, vector<string> > :: iterator itr;
	vector<string> :: iterator itr1;
	
	cout << "netToCellMap" << endl;
	for(itr= netToCell.begin(); itr != netToCell.end(); ++itr)
	{
		cout << itr->first <<"	";

		for(itr1 = itr->second.begin(); itr1 != itr->second.end(); ++itr1 )
		{
			cout << *itr1 <<"	";
		}
		
		cout << endl;
	}
	cout << "\n" << endl;
}

