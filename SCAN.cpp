#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

class Graph{
		int numNodes, numEdges;
		vector<int> offset, edgelist;
		vector<int> *adjlist;
	public:
		void createGraph(bool isUndirected);
		float struct_sim(int v, int w);	
};

void Graph::createGraph(bool isUndirected){
	
	int count=0;
	int buffer_start, buffer_end; 
	string line;

	ifstream inputG("input.txt");
	if (inputG.is_open()){
	while(getline (inputG,line)){
		++count;
		if(count==1) continue;
		else if(count==2) {numNodes = stoi(line); continue;}
		else if(count==3) {numEdges = stoi(line); continue;}
		else {
			if(count >= 4 && count <= (numNodes+3)){offset.push_back(stoi(line));}
			else if(count > (numNodes+3) && count <= (numEdges+numNodes+3)){edgelist.push_back(stoi(line));}		
		};
	}
	cout << "No. of Nodes = " << numNodes << endl;
	cout << "No. of Edges = " << numEdges << endl;
	inputG.close();
	}
	else cout << "Bad input file";
	adjlist = new vector<int>[numNodes];
	for(int vid=0; vid<numNodes;vid++){
		buffer_start = offset.at(vid);
		if(vid==(numNodes-1)) buffer_end = numEdges;
		else buffer_end = offset.at(vid+1);
		if(buffer_start == buffer_end) continue;             //node with no edges
		else{
			for(int eid=buffer_start;eid<buffer_end;eid++){
			adjlist[vid].push_back(edgelist.at(eid));
			if(isUndirected) adjlist[edgelist.at(eid)].push_back(vid);
			}
		}
	}
	for (int i = 0; i<numNodes;i++){
		cout << "Edgelist of node" << i << ": ";
		for(int neighbor: adjlist[i])
			cout << neighbor << ' ';
		cout << endl;
	}
}

float Graph::struct_sim(int v, int w){
	
	float sim_score;
	sort(adjlist[v].begin(),adjlist[v].end());
	sort(adjlist[w].begin(),adjlist[w].end());
	vector<int> matched_ngh(adjlist[v].size()+adjlist[w].size());
	vector<int>::iterator it;
	it=set_intersection(adjlist[v].begin(),adjlist[v].end(),adjlist[w].begin(),adjlist[w].end(),matched_ngh.begin());
	matched_ngh.resize(it-matched_ngh.begin());
	sim_score = (matched_ngh.size())/pow((adjlist[v].size() * adjlist[w].size()),0.5);
	return sim_score;
}


int main(){
		
	Graph G;
	G.createGraph(true);
	float similarity_score = G.struct_sim(10,11);
	cout << similarity_score << endl; 
	return 0;
}
