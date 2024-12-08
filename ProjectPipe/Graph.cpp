#include "Graph.h"
#include <queue>
using namespace std;

// About the edge
ofstream& operator << (std::ofstream& file, const Edge& edge) {
	if (file.is_open()) {
		file << edge.pipe << " ";
		file << edge.from << " ";
		file << edge.to << std::endl;
	}
	return file;
}
ifstream& operator >> (std::ifstream& file, Edge& edge) {
	if (file.is_open()) {
		file >> edge.pipe;
		file >> edge.from;
		file >> edge.to;
	}
	return file;
}

// About the graph
Graph::Graph(const unordered_map<int, Edge>& edges, const set<int> nodes, const unordered_map<int, Pipe>& pipes) : edges(edges) {
	//nodes(nodes)
	int count = 0;
	for (int node : nodes) {
		this->nodes.insert({ count, node });
		count++;
	}
	SizeGraph = nodes.size();
	capacity.resize(SizeGraph, vector<double>(SizeGraph, 0.0));
	adj_weight.resize(SizeGraph, vector<double>(SizeGraph, 0.0));
	for (auto& [pipe_id, edge] : edges) {
		auto i = GetIndex(edge.from);
		auto j = GetIndex(edge.to);
		//capacity[i][j] = pipes.at(pipe_id).get_capasity();
		adj_weight[i][j] = pipes.at(pipe_id).GetLenght();
	}
}

bool Graph::DFS_Cycle(int node, vector<bool>& visited, vector<bool>& recStack) {
	if (!visited[node]) {
		visited[node] = true;
		recStack[node] = true;

		for (int i = 0; i < SizeGraph; ++i) {
			if (adj_weight[node][i]) {
				if (!visited[i] && DFS_Cycle(i, visited, recStack)) { return true; }
				else if (recStack[i]) { return true; }
			}
		}
	}
	recStack[node] = false;
	return false;
}

bool Graph::HasCycle() {
	vector<bool> visited(SizeGraph, false);
	vector<bool> recStack(SizeGraph, false);

	for (int i = 0; i < SizeGraph; ++i) {
		if (DFS_Cycle(i, visited, recStack)) { return true; }
	}

	return false;
}

int Graph::GetIndex(int vertice)
{
	for (auto& [index, node] : nodes) {
		if (node == vertice) { return index; }
	}
	return INT16_MAX;
}

bool Graph::Conteins(int Node)
{
	for (auto& [index, node] : nodes) {
		if (node == Node) { return true; }
	}
	return false;
}

void Graph::DFS_Sort(int node, vector<bool>& visited, vector<int>& nodes) {
	visited[node] = true;

	for (int i = 0; i < SizeGraph; ++i) {
		if (adj_weight[node][i] && !visited[i]) {
			DFS_Sort(i, visited, nodes);
		}
	}

	nodes.push_back(this->nodes.at(node));
}

vector<int> Graph::TopologicalSort() {
	if (edges.empty()) {
		cout << endl << "The graph has no edges.Topological sort is impossible" << endl;
		return vector<int>();
	}
	else if (HasCycle()) {
		cout << endl << "The graph has a cycle.Topological sort is impossible" << endl;
		return vector<int>();
	}

	vector<bool> visited(SizeGraph, false);
	vector<int> result;

	for (int i = 0; i < SizeGraph; ++i) {
		if (!visited[i]) {
			DFS_Sort(i, visited, result);
		}
	}
	reverse(result.begin(), result.end());

	return result;
}

vector<int> Graph::Metod_Deikstra(int StartNode, int EndNode) {
	if (edges.empty()) {
		cout << endl << "The graph has no edges.It is impossible to find the shortest path." << endl;
		return vector<int>();
	}
	else if (!Conteins(StartNode) && !Conteins(EndNode)) {
		cout << endl << "The graph has no stations with such an ID.It is impossible to find the shortest path." << endl;
		return vector<int>();
	}
	vector<int> dist(SizeGraph, INT_MAX);
	vector<int> prev(SizeGraph, -1);
	vector<bool> visited(SizeGraph, false);

	StartNode = GetIndex(StartNode);
	EndNode = GetIndex(EndNode);

	dist[StartNode] = 0;

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push({ 0, StartNode });

	while (!pq.empty()) {
		int u = pq.top().second;
		pq.pop();

		if (u == EndNode) { break; }

		visited[u] = true;

		for (int v = 0; v < SizeGraph; ++v) {
			if (!visited[v] && adj_weight[u][v] && dist[u] != INT_MAX &&
				dist[u] + adj_weight[u][v] < dist[v])
			{
				dist[v] = dist[u] + adj_weight[u][v];
				prev[v] = u;
				pq.push({ dist[v], v });
			}
		}
	}

	vector<int> path;
	for (int node = EndNode; node != -1; node = prev[node]) {
		path.push_back(nodes.at(node));
	}
	reverse(path.begin(), path.end());

	return path;
}
