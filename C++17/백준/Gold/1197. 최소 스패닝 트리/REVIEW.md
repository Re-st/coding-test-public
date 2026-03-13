# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Gold/1197. 최소 스패닝 트리/최소 스패닝 트리.cc`

## 한 줄 결론
- **크루스칼(Union-Find)** / 복잡도: O(E log E) / 간선을 불필요하게 두 번씩 우선순위 큐에 넣는 실수.

## 더 빠른/더 안전한 풀이(필수)
- 아이디어: 모든 간선을 `vector`에 저장 후 `sort()` 함수로 한 번에 정렬하는 방식.
- 복잡도: O(E log E)
- 왜 이게 더 좋은지: `priority_queue`에 간선을 중복 저장하는 실수를 원천 차단하고, 구현이 더 간결해집니다.

```cpp
// 스니펫: vector와 sort 사용
vector<tuple<int, int, int>> edges;
// ... 입력 루프
  cin >> a >> b >> c;
  edges.emplace_back(c, a, b);
// ...
sort(edges.begin(), edges.end());
for (auto& edge : edges) {
    // ...
}
```

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) 자료구조/성능 함정: 무방향 간선을 `pq.push({c, {a,b}})`와 `pq.push({c, {b,a}})`로 두 번 저장하여 메모리(2*E)와 시간(log(2*E))을 낭비합니다.
- 2) 오버플로: `ans`의 타입. 이 문제는 결과가 `int` 범위 내임을 보장했지만, 일반적인 MST 가중치 합은 `(V-1) * |C|_max`로 `long long` 범위를 쉽게 초과할 수 있습니다.
- 3) Union-Find 구현: `parent[b] = parent[a];`는 `a`가 루트 노드이므로 동작하지만, `parent[Find(b)] = Find(a);` 형태가 더 명확하고 일반적입니다.

## 즉시 수정 액션(최대 4개)
- 1. `pq.push({ c, {b, a} });` 라인을 제거하세요. 간선은 한 번만 추가해야 합니다.
- 2. `int ans = 0;`를 `long long ans = 0;`로 변경하여 잠재적 오버플로 위험을 차단하세요.
- 3. `n = n - 1; while(n)` 루프 대신, `int edge_count = 0; while (edge_count < V - 1)` 형태를 사용하면 MST의 종료 조건이 더 명확해집니다.