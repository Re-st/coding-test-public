#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <string.h>
using namespace std;

bool visited[1002];
vector<int> result_dfs;
vector<int> result_bfs;
vector<int> edges[1002];

void bfs(int x) {
	queue<int> q;
	q.push(x);
	visited[x] = true;
	while (!q.empty())
	{
		x = q.front();
		q.pop();
		result_bfs.push_back(x);
		for (int i = 0; i < edges[x].size(); i++) {
			if (!visited[edges[x][i]]) {
				q.push(edges[x][i]);
				visited[edges[x][i]] = true;
			}
		}
	}
}

void dfs(int x) {
	visited[x] = true;
	result_dfs.push_back(x);
	for (int i = 0; i < edges[x].size(); i++) {
		if (!visited[edges[x][i]]) {
			dfs(edges[x][i]);
		}
	}
}


int main() {
	int n, m, v, a, b;
	cin >> n >> m >> v;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	for (int i = 1; i <= n; i++)
		sort(edges[i].begin(), edges[i].end());
	bfs(v); 
	memset(visited, false, sizeof(visited));
	dfs(v);
	for (int i = 0; i < result_dfs.size(); i++)
		cout << result_dfs[i] << " ";
	cout << "\n";
	for (int i = 0; i < result_bfs.size(); i++)
		cout << result_bfs[i] << " ";
	return 0;
}