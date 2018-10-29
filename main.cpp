// Input Output
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
// Datastructures
#include <cstring>
#include <bitset>
#include <queue>
#include <map>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <utility>
#include <queue>
// Others
#include <cmath>
#include <algorithm>
#include <time.h>

//Define for shorter typing
#define vi vector<int>
#define mp make_pair
#define ff first
#define ss second

using namespace std;

//Since from the country.txt the number of countries is <200, it is safe to put the upper limit as 500 I think, futher addition to countries is still possible in this case.
int country_id;
map<string,int> countrycode; // Changes country name to int automatically
map<int,string> reverse_countrycode;
vector<int> AdjList[500]; // Adjacency List is implemented using array of vectors
vector<int> path;
bool visited[500];

string srcCountry, desCountry;
int beginPos, desPos;

bool debug=0;

vector<int> bfs(int source_cc,int dest_cc)// cc means countrycode
{
	//Initialization
	queue<pair<int,vector<int> > > countriesQueue; // Careful with > >, if merged may be considered as >> operator
	while(!countriesQueue.empty())countriesQueue.pop(); // make sure queue is empty
	memset(visited,0,sizeof(visited)); // make sure visited is reset
	vector<int> temp_path,next_path;
	temp_path.clear();
	temp_path.push_back(source_cc);
	//Base case
	countriesQueue.push(make_pair(source_cc,temp_path));
	int curPos;
	while(!countriesQueue.empty())
	{
		curPos = countriesQueue.front().first;
		temp_path= countriesQueue.front().second;
		countriesQueue.pop();
		if(debug)
			cout<<"Currently at "<<curPos<<endl;
		if(curPos==dest_cc)
		{
			// BFS finished
			cout<<"Path found!!\n";
			return temp_path;
		}
		if(visited[curPos]==true)continue; // already visited, must still check even though it is checked before being pushed to the queue!
		visited[curPos]=true;
		for(int x=0;x<AdjList[curPos].size();x++) // traverse all vertices from adjlist
		{
			if(debug)
				printf("%d: %d\n",x,AdjList[curPos][x]);
			if(visited[AdjList[curPos][x]])continue; // no need to push if it is already visited
			next_path=temp_path;
			next_path.push_back(AdjList[curPos][x]); // add next vertices to the path
			if(debug)
			{
				for(int x=0;x<next_path.size();x++)
				{
					cout<<next_path[x]<<" ";
				}cout<<endl;
			}
			countriesQueue.push(make_pair(AdjList[curPos][x],next_path)); // add to queue
		}
	}
	cout<<"No path found!\n";
	temp_path.clear();
	return temp_path;
}

void add_vetices_manual()
{
	country_id=1;
	int num_v;
	string temp;
	cout<< "Input number of vertices: "<< endl;
    getline(cin,temp);
    num_v=stoi(temp);
	for(int x=1;x<=num_v;x++)
    {
    	
    	cout<<"Input country name:"<<endl;
		getline(cin,temp);
		transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
		countrycode[temp]=country_id;
	    reverse_countrycode[country_id] = temp;
	    country_id++;
	}
	
}

void load_vertices()
{
	country_id=1;
	ifstream myfile("Country.txt");
    if (myfile.is_open()) {
        string temp;
        while(getline(myfile, temp)) {
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            //cout<<temp<<'\n'; //for debug only
            countrycode[temp]=country_id;
            reverse_countrycode[country_id] = temp;
            country_id++;
        }
    }
    myfile.close();
}

void add_edges_manual()
{
	int num_edges;
	string temp;
	// Edges adding
	cout<< "Input number of edges: "<< endl;
    getline(cin,temp);
    num_edges=stoi(temp);
    for(int x=0;x<num_edges;x++)
    {
    	cout << "Input name of 2 cities to be added to the graph!" << endl;
    	cout << "Name of source country" << endl;
    	getline(cin,srcCountry);
    	cout << "Name of destination country" << endl;
    	getline(cin,desCountry);
		transform(srcCountry.begin(), srcCountry.end(), srcCountry.begin(), ::tolower);
		transform(desCountry.begin(), desCountry.end(), desCountry.begin(), ::tolower);
		beginPos=countrycode[srcCountry];
		desPos=countrycode[desCountry];
		if(beginPos==0||desPos==0)
		{
			cout<<"Invalid edges added!"<<endl;
		}
		if(debug)
			cout<<"Added edges from "<<reverse_countrycode[beginPos]<<" to "<<reverse_countrycode[desPos]<<endl;
		// Assuming the graph is undirected
		AdjList[beginPos].push_back(desPos); // adding the edges from beginPos to desPos
		AdjList[desPos].push_back(beginPos); // adding the edges from desPos to beginPos
	}   
}

void add_edges_random()
{
	srand(time(NULL));
	int num_edges;
	string temp;
	cout<< "Input number of edges: "<< endl;
    getline(cin,temp);
    num_edges=stoi(temp);
    cout<< "Generating edges...: "<< endl;
    map<pair<int,int>,bool> gen_edges_check;
	for(int x=0;x<num_edges;x++)
    {
    	while(1)
    	{
    		beginPos=rand()%country_id+1;
    		desPos=rand()%country_id+1;
    		if(gen_edges_check[make_pair(beginPos,desPos)]==0&&gen_edges_check[make_pair(desPos,beginPos)]==0)
    		{
    			gen_edges_check[make_pair(beginPos,desPos)]=1;
    			gen_edges_check[make_pair(desPos,beginPos)]=1;
    			cout<<"Added edges from "<<reverse_countrycode[beginPos]<<" to "<<reverse_countrycode[desPos]<<endl;
    			AdjList[beginPos].push_back(desPos); // adding the edges from beginPos to desPos
				AdjList[desPos].push_back(beginPos); // adding the edges from desPos to beginPos
    			//Unique edges added, otherwise rerandom
    			break;
			}
		}
    }
    
}

int main() {
	//debug=1;
	memset(AdjList,0,sizeof(AdjList));
	//add_vetices_manual();
    load_vertices();
    
    if(debug)
	for (auto it = countrycode.begin(); it != countrycode.end(); it++ )
	{
		cout<<it->first<<" : "<<it->second<<'\n';
	}
    
    //add_edges_manual();
    add_edges_random();
	// Query start
	cout << "Input name of source country" << endl;
	getline(cin,srcCountry);
	cout << "Input name of destination country" << endl;
    getline(cin,desCountry);
	transform(srcCountry.begin(), srcCountry.end(), srcCountry.begin(), ::tolower);
	transform(desCountry.begin(), desCountry.end(), desCountry.begin(), ::tolower);
	beginPos=countrycode[srcCountry];
	desPos=countrycode[desCountry];
	
	// Call BFS Algorithm
	path.clear();
	path=bfs(beginPos,desPos);
	
	// Output the result
	if(path.size()>0)
	{
		cout<<"The shortest path is:\n";
		for(int x=0;x<path.size();x++)
		{
			cout<<reverse_countrycode[path[x]]<<" ";
		}
		cout<<"\n";
	}
	
    return 0;
}
