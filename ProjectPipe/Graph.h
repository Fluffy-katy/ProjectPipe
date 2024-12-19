#pragma once
#include "Utilites.h"
#include "Pipe.h"
#include <map>
#include <unordered_map>
#include <set>

class Graph;
class GTS;
class Connections;

class Edge
{
	friend Graph;
	friend GTS;
	friend Connections;
	friend std::ofstream& operator << (std::ofstream& file, const Edge& edge);
	friend std::ifstream& operator >> (std::ifstream& file, Edge& edge);
public:
	Edge() {};

private:
	int from, to, pipe;
	Edge(int from, int to, int pipe) : from(from), to(to), pipe(pipe) {};
};

class Graph
{
	friend GTS;
public:
	Graph(const std::unordered_map<int, Edge>& edges, const std::set<int>& nodes, const std::unordered_map<int, Pipe>& pipes);
	std::vector<int> TopologicalSort();
	std::vector<int> Metod_Deikstra(int StartNode, int EndNode) const;
	double Ford_Fulkerson(int StartNode, int  EndNode) const;



private:
	bool DFS_Cycle(int, std::vector<bool>&, std::vector<bool>&);
	void DFS_Sort(int v, std::vector<bool>& visited, std::vector<int>& nodes);
	double Lenght_ShortestPath(std::vector<int>&);
	bool BFS_MaxFlow(std::vector<std::vector<double>>& capacity,
		int StartNode, int EndNode, std::vector<int>& parent) const;

	bool HasCycle();
	int GetIndex(int node) const;
	bool Conteins(int Node) const;
	std::map<int, int> nodes;
	std::unordered_map<int, Edge> edges;
	std::vector<std::vector<double>> capacity;
	std::vector<std::vector<double>> adj_weight;
	int SizeGraph;
};