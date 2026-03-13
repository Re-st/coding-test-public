# 제목: 순방향 시간 전파를 이용한 풀이
- 적용 조건: 위상 정렬을 사용하는 모든 문제에서 일반적으로 더 직관적입니다.
- 핵심 아이디어: 현재 건물(u)의 완공 시간(`completion_time[u]`)이 확정되면, 이 건물을 필요로 하는 다음 건물(v)들의 완공 시간을 갱신합니다. `completion_time[v]`는 `completion_time[u] + v의 건설 시간`과 기존 값 중 더 큰 값으로 계속 갱신됩니다.
- 복잡도: O(N + E)
- 구현 스케치(C++):
vector<int> completion_time(n + 1, 0);
queue<int> q;

for (int i = 1; i <= n; ++i) {
    if (indegree[i] == 0) {
        q.push(i);
        completion_time[i] = reqtime[i];
    }
}

while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v : A[u]) { // A는 u -> v 방향의 인접 리스트
        completion_time[v] = max(completion_time[v], completion_time[u] + reqtime[v]);
        if (--indegree[v] == 0) {
            q.push(v);
        }
    }
}