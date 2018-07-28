/* This is a graph theory problem that is very similar to Dijkstra's
but with various possible routes and no saving of the path in a parent var
CODE: crocdile
*/
#include <iostream>
#include <vector>
using namespace std;

struct Chamber
{
	bool visited;
	int dist, tempDist;
	Chamber()
	{
		dist = -1;
		tempDist = -1;
		visited = false;
	}
};

//Return -1 if all visited
int getMinChamber(const vector<Chamber> & chambers)
{
	int dist = -1, index = -1;
	for(size_t i = 0; i < chambers.size(); ++i)
	{
		if(!chambers[i].visited)
		{
			if(dist == -1 || chambers[i].tempDist < dist)
			{
				dist = chambers[i].tempDist;
				index = i;
			}
		}
	}
	return index;
}

void dijkstra(int start, vector<Chamber> & chambers, const vector<vector<pair<int,int> > > & corridors)
{
	while(start != -1)
	{
		chambers[start].visited = true;
		for(size_t i = 0; i < corridors[start].size(); ++i)
		{
			int tempL, tempC;
			tempC = corridors[start][i].first;
			tempL = corridors[start][i].second;
			if(chambers[tempC].tempDist == -1 || chambers[tempC].tempDist > tempL + chambers[start].tempDist)
			{
				chambers[tempC].tempDist = tempL + chambers[start].tempDist; 
				if(chambers[tempC].dist == -1 || chambers[tempC].tempDist < chambers[tempC].dist)
					chambers[tempC].dist = chambers[tempC].tempDist;
			}
		}
		start = getMinChamber(chambers);
	}
	//Reinitialize it
	for(size_t i = 0; i < chambers.size(); ++i)
	{
		chambers[i].visited = false;
		if(chambers[i].dist != 0)
			chambers[i].tempDist = -1;
	}
}

void printChambers(const vector<Chamber> & chambers)
{
	for(size_t i = 0; i < chambers.size(); ++i)
		cout << i << " length " << chambers[i].dist << endl;
}

int nextBestPath(vector<Chamber> & chambers, const vector<vector<pair<int,int> > > & corridors)
{
	int curNode = 0, dist = 0;
	while(chambers[curNode].dist != 0)
	{
		int minDist = -1, min2Dist = -1, tempDist, tempC, minIndex=-1, min2Index = -1;
		//Find the second best route to take
		//If only one route then set to visited and start
		//over at 0
		chambers[curNode].visited = true;
		for(size_t i = 0; i < corridors[curNode].size(); ++i)
		{
			tempC = corridors[curNode][i].first; 
			if(chambers[tempC].visited)
				continue;
			tempDist = chambers[tempC].dist + corridors[curNode][i].second;
			if(minDist == -1)
			{
				minDist = tempDist;
				minIndex = tempC;
			}
			else if(tempDist < minDist)
			{
				min2Dist = minDist;
				min2Index = minIndex;
				minDist = tempDist;
				minIndex = tempC;
			}
			else if(tempDist < min2Dist || min2Dist == -1)
			{
				min2Dist = tempDist;
				min2Index = tempC;
			}
		}
		if(min2Index == -1)
		{
			return -1;
		}
		else
		{
			curNode = min2Index;
			dist += min2Dist - chambers[curNode].dist;
		}
	}
	return dist;
}

int main()
{
	int numChambers, numCorridors, numExits;
	int tempC1, tempC2, l;
	//Each vector has a list of other chambers
	//its connected to and the length
	vector<vector<pair<int,int> > > corridors;
	vector<Chamber> chambers;
	vector<int> exits;

	cin >> numChambers >> numCorridors >> numExits;

	chambers = vector<Chamber>(numChambers, Chamber());
	corridors = vector<vector<pair<int,int> > >(numChambers, vector<pair<int,int> >());

	for(int i = 0 ; i < numCorridors; ++i)
	{
		cin >> tempC1 >> tempC2 >> l;
		corridors[tempC1].push_back(make_pair(tempC2,l));
		corridors[tempC2].push_back(make_pair(tempC1,l));
	}
	for(int i = 0; i < numExits; ++i)
	{
		cin >> tempC1;
		exits.push_back(tempC1);
		chambers[tempC1].dist = chambers[tempC1].tempDist = 0;
	}
	//Get distances to closest exit
	//I thought I need to run this for ea. exit, but it's
	//unnecessary
	//for(int i = 0; i < numExits; ++i)
	dijkstra(exits[0], chambers, corridors);
	cout << nextBestPath(chambers, corridors) << endl;
}
