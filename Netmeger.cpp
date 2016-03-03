#include <iostream>
#include <map>
#include <fstream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;


void readNets();
void mapOfNets();
void printMapOfNets();
void findMinMax();
void printMapMinMax();
void findNetsInCoulum();
void printMapOfColNets();
void createVCG();
void printVCG();
void zone();
void prinZoneTable();
void createNetToZone();
void printNetToZone();
void createNetFromTo();
int maxTracks();
vector<int> findZone(int Net);
void getTracks(int maxNumTracks);

struct border;

vector<int> topRow;
vector<int> bottomRow;

map<int, list<int>> netMap;
map<int, border> borderMap;
map<int, vector<int>> columnToNets;
map<int, vector<int>> zoneTable;
map<int, vector<int>> VCG;
map<int, vector<int>> netToZone;
map<int, vector<int>> tracksToNet;

int main()
{
    int Net;
    readNets();
    mapOfNets();
    printMapOfNets();
    findMinMax();
    //printMapMinMax();
    findNetsInCoulum();
    printMapOfColNets();
    createVCG();
    printVCG();
    zone();
    prinZoneTable();
    createNetToZone();
    printNetToZone();
    createNetFromTo();
    int maxNumTracks = maxTracks();
    vector<int> Id;
    Id = findZone(Net);
    getTracks(maxNumTracks);
    return 0;
}

struct border
{
    int min;
    int max;
    int netNum;
    int netBegin;
    int netEnd;
    int track = -1;
};


void mapOfNets()
{
    
    for(int itr1 = 0; itr1 < topRow.size(); ++itr1)
    {
        netMap[topRow[itr1]].push_back(itr1);
        netMap[bottomRow[itr1]].push_back(itr1);
    }

}


void printMapOfNets()
{
    cout<<endl;
    cout << "Nets and Its Indices" << endl;
    map<int, list<int>>::iterator itrM;
    list<int>::iterator itrV;
    
    for (itrM = netMap.begin(); itrM != netMap.end(); ++itrM)
    {
        cout << itrM->first << ": ";
        for (itrV = itrM->second.begin(); itrV != itrM->second.end(); ++itrV)
        {
            cout << *itrV << " ";
        }
        cout << endl;
    }
    
}

void findMinMax()
{
    map<int, list<int>>::iterator itrM;
    int val = 0;
    
    for(itrM = netMap.begin(); itrM != netMap.end(); ++itrM)
    {
        border b;
        itrM->second.sort();
        b.netNum = val;
        b.min = itrM->second.front();
        b.max = itrM->second.back();
        borderMap.insert(pair<int, border>(val,b));
        val++;
    }
}

void printMapMinMax()
{
    map<int, border>::iterator itrB;
    
    for (itrB = borderMap.begin(); itrB != borderMap.end(); ++itrB)
    {
        cout << itrB->first << ": " << itrB ->second.max << endl;

    }
    
}

void findNetsInCoulum()
{
    map<int, border>::iterator itrB;

    for (int itrV = 0; itrV < topRow.size(); ++itrV)
    {
        for (itrB = borderMap.begin(); itrB != borderMap.end(); ++itrB)
        {
            if (itrB->first != 0)
            {
                if (itrB->second.min <= itrV && itrV <= itrB->second.max)
                {
                    columnToNets[itrV].push_back(itrB->first);
                }
            }
        }
    }

}

void printMapOfColNets()
{
    cout<<endl;
    cout << "Columns to Nets" << endl;
    map<int, vector<int>>::iterator itrC;
    vector<int>::iterator itrV;
    
    for (itrC = columnToNets.begin(); itrC != columnToNets.end(); ++itrC)
    {
        cout << itrC->first << ": ";
        for (itrV = itrC->second.begin(); itrV != itrC->second.end(); ++itrV)
        {
            cout << *itrV << " ";
        }
        cout << endl;
    }
    
}

void createVCG()
{
    for (int itrV = 0; itrV != topRow.size(); ++itrV)
    {
        if(topRow[itrV] != 0)
        {
            VCG[topRow[itrV]].push_back(bottomRow[itrV]);
        }
    }
}

void printVCG()
{
    map<int, vector<int>>::iterator itrG;
    vector<int>::iterator itrV;
    
    cout<<endl;
    cout << "VCG graph" << endl;
    for (itrG = VCG.begin(); itrG != VCG.end(); ++itrG)
    {
        cout << itrG->first;
        for (itrV = itrG->second.begin(); itrV != itrG->second.end(); ++itrV)
        {
            cout << " <- " << *itrV ;
        }
        cout << endl;
        }
}

void zone()
{
    map<int, vector<int>>::iterator itrC;
    int zoneNum = 1;
    
    vector<int> temp;
    
    itrC = columnToNets.begin();
    
    temp = itrC->second;
    
    for (itrC = columnToNets.begin(); itrC != columnToNets.end(); ++itrC)
    {
        if (includes(itrC->second.begin(),itrC->second.end(),temp.begin(),temp.end()))
        {
            temp = itrC->second;
            zoneTable[zoneNum] = temp;
        }
        else if (includes(temp.begin(),temp.end(),itrC->second.begin(),itrC->second.end()))
        {
            zoneTable[zoneNum] = temp;
        }
        else
        {
            zoneNum++;
            temp = itrC->second;
            zoneTable[zoneNum] = temp;
        }
    }
}

void prinZoneTable()
{
    map<int, vector<int>>::iterator itrZ;
    vector<int>::iterator itrL;
    
    cout<<endl;
    cout << "Zone Table" << endl;
    for (itrZ = zoneTable.begin(); itrZ != zoneTable.end(); ++itrZ)
    {
        cout << "Zone "<< itrZ->first << " : ";
        for (itrL = itrZ->second.begin(); itrL != itrZ->second.end(); ++itrL)
        {
            cout << *itrL << " " ;
        }
        cout << endl;
    }
}

void createNetToZone()
{
    map<int, vector<int>>::iterator itrZ;
    vector<int> :: iterator itrV;
    
    for (itrZ = zoneTable.begin(); itrZ != zoneTable.end(); ++itrZ)
    {
        for(itrV = itrZ->second.begin(); itrV != itrZ->second.end(); ++itrV)
        {
            netToZone[*itrV].push_back(itrZ->first);
        }
    }
}

void printNetToZone()
{
    map<int, vector<int>>::iterator itrN;
    vector<int>::iterator itrV;
    
    cout<<endl;
    cout << "Net To Zone" << endl;
    for (itrN = netToZone.begin(); itrN != netToZone.end(); ++itrN)
    {
        cout << itrN->first << " : ";
        for (itrV = itrN->second.begin(); itrV != itrN->second.end(); ++itrV)
        {
            cout << *itrV << " " ;
        }
        cout << endl;
    }
}

void createNetFromTo()
{
    map<int, vector<int>>::iterator itrN;
    
    cout<<endl;
    cout << "Start Zone and End Zone of Nets" << endl;
    for (itrN = netToZone.begin(); itrN != netToZone.end(); ++itrN)
    {
        borderMap[itrN->first].netBegin = *min_element(itrN->second.begin(),itrN->second.end());
        borderMap[itrN->first].netEnd = *max_element(itrN->second.begin(),itrN->second.end());
        cout << "Net" << itrN->first << ": ";
        cout << borderMap[itrN->first].netBegin << " -- ";
        cout << borderMap[itrN->first].netEnd << endl;
    }
}

int maxTracks()
{
    map<int, vector<int>>:: iterator itrZ;
    int itrV;
    int numTracks, maxNumTracks=0;
    
    for (itrZ = zoneTable.begin(); itrZ != zoneTable.end(); ++itrZ)
    {
        for (itrV = 0; itrV != itrZ->second.size(); ++itrV)
        {
            numTracks = itrV;
        }
        if (numTracks > maxNumTracks)
        {
            maxNumTracks = numTracks + 1;
        }
    }
    return maxNumTracks;
}

vector<int> findZone(int Net)
{
    map<int,border> :: iterator itB = borderMap.find(Net);
    map<int, border> :: iterator itrB;
    vector<int> Id;

    for (itrB = borderMap.begin(); itrB != borderMap.end(); ++itrB)
    {
        if (borderMap[itrB->first].netEnd <= (borderMap[itB->first].netBegin-1))
        {
            Id.push_back(itrB->first);
        }
    }
    return Id;
}

void getTracks(int maxNumTracks)
{
    map<int, border> :: iterator itrB;
    vector<int> :: iterator itrV;
    vector<int> temp;
    int x;
    int trackNum = 1;

    for (itrB = borderMap.begin(); itrB != borderMap.end(); ++itrB)
    {
        x = itrB->first;
        temp = findZone(x);
        
        if (temp.empty() == true && borderMap[itrB->first].track == -1)
        {
            if (trackNum < maxNumTracks)
            {
                borderMap[itrB->first].track = trackNum;
                tracksToNet[trackNum];
                trackNum++;
                
                cout << "Net: " << borderMap[itrB->first].netNum;
                cout << "Track: " << borderMap[itrB->first].track;
                cout << endl;
            }
        }
    }
}


int Netmap :: root_elements(map<int,list<int>> vcg_new){
    
    list<int> keys,elements,roots;
    int length,max_length=0;
    map<int, list<int> > :: iterator it8;
    list<int> :: iterator it9,it1;
    
    for(it8=vcg_new.begin(); it8 !=vcg_new.end(); ++it8)
    {
        keys.push_back(it8->first);
        
        for(it9 = it8->second.begin(); it9 != it8->second.end(); ++it9 )
        {
            elements.push_back(*it9);
        }
        
    }
    
    
    for(it1=keys.begin();it1!=keys.end();it1++){
        bool found = (std::find(elements.begin(), elements.end(),*it1) != elements.end());
        if(found == false )
        {
            
            length =dfs(*it1,vcg_new);
            if(max_length<length){
                max_length = length;
                
            }
            cout<<"root:"<<*it1<<endl;
            cout<<"length:"<<length<<endl;
        }
        
    }
    cout<<"length:"<<max_length<<endl;
    return max_length;
}



map<int,list<int>> Netmap:: compute_vcg(int index1,int index2){
    
    
    vcg_temp = this->vcg;
    
    list <int>  :: iterator vcg;
    map<int,list <int>>  :: iterator it1,it2;
    it2=vcg_temp.find(index1);
    list<int> :: iterator it3,it4;
    
    for(it3=it2->second.begin();it3!=it2->second.end();it3++){
        vcg_temp[index2].push_back(*it3);
    }
    
    vcg_temp.erase (it2);
    for(it1= vcg_temp.begin(); it1 !=vcg_temp.end(); ++it1)
    {
	       
        replace (it1->second.begin(), it1->second.end(), index1,index2);
    }
    
    map<int, list<int> > :: iterator it8;
    list<int> :: iterator it9;
    cout<<"new vcg"<<endl;
    for(it8=vcg_temp.begin(); it8 !=vcg_temp.end(); ++it8)
    {
        cout << it8->first <<"	";
        
        for(it9 = it8->second.begin(); it9 != it8->second.end(); ++it9 )
        {
            cout << *it9 <<"	";
        }
        cout << endl;
    }
    
    
    return vcg_temp;
    
    
    
}

int :: Netmap :: try_vcg(list <int> temp,int index){
    
    map<int,list<int>> vcg_copy;
    vcg_copy=vcg;
    int track_rno;
    int list_size =temp.size();
    list<int>  :: iterator it2;
    int element,length,length1;
    length1 = root_elements(vcg);
    
    for(it2=temp.begin();it2!=temp.end();it2++)
    {
        
        vcg_temp=compute_vcg(index,*it2);
        length =root_elements(vcg_temp);
        if(length<=length1){
            vcg=vcg_temp;
            element = *it2;
        }
        
        
    }
    
    track_rno = netstructure[element].track;
    return track_rno;
    
    
}