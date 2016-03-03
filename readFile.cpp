#include <iostream>
#include <map>
#include <list>
#include <string>
#include <vector>
#include <sstream>
#include <string>
#include "netclass.h"
#include <cstdlib>
#include <fstream>
#include <sstream>

using namespace std;

vector<int>top,bot;
void readinput(char* argv[])
{
    ifstream file;
    string data;
    file.open(argv[1]);
    if(!file)
    {
        cout << "Error: File cannot be Opened " << endl;
    }
    else
    {
        getline(file,data);
        string a;
        stringstream sp(data);
        int i = -1;
        while(getline(sp,a,','))
        {
            i = atoi(a.c_str());
            cout << " " << i;
            top.push_back(i);
        }
        cout << endl;
        getline(file,data);
        string a1;
        stringstream sp1(data);
        int j = -1;
        while(getline(sp1,a1,','))
        {
            j = atoi(a1.c_str());
            cout << " " << j;
            bot.push_back(j);
        }
        cout << endl;        
    }
}