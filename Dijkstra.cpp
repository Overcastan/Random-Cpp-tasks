#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

const int INF = 2009000999;

void Dijkstra(vector<vector<pair<int,int>>>& graph, vector<int>& distances, int s) {
	distances[s] = 0;

	set<pair<int, int>> vertexes;
	vertexes.insert(make_pair(distances[s], s));

	while (!vertexes.empty()) {
		int v = vertexes.begin()->second;
		vertexes.erase(vertexes.begin());

		for (int i = 0; i < graph[v].size(); ++i) {
			int u = graph[v][i].first;
			int weight = graph[v][i].second;

			if (distances[v] + weight < distances[u]) {
				vertexes.erase(make_pair(distances[u], u));
				distances[u] = distances[v] + weight;
				vertexes.insert(make_pair(distances[u], u));
			}
		}
	}
}

int main() {
	int num;
	cin >> num;

	for (int i = 0; i < num; ++i) {
		int vertex, edge;
		cin >> vertex >> edge;
		vector<vector<pair<int, int>>> graph(vertex);
		
		for (int j = 0; j < edge; ++j) {
			int start, end, weight;
			cin >> start >> end >> weight;
			graph[start].push_back(make_pair(end, weight));
			graph[end].push_back(make_pair(start, weight));
		}

		int source;
		cin >> source;
		vector<int> distances(vertex, INF);
		Dijkstra(graph, distances, source);

		for (int j = 0; j < vertex; ++j) {
			cout << distances[j] << " ";
		}
		cout << "\n";
	}
}