# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Gold/1753. 최단경로/최단경로.cc`

## 한 줄 결론
- (이 문제는) **다익스트라** / 복잡도: O(E log V) / 경로 갱신이 없어도 큐에 원소를 추가하여 성능이 저하되는 것이 가장 큰 문제입니다.

## 더 빠른/더 안전한 풀이(필수)
- 아이디어: 간선 가중치가 10 이하로 매우 작으므로, 우선순위 큐 대신 '버킷 큐'(Dial's Algorithm)를 사용합니다.
- 복잡도: O(E + W*V) (W: 최대 가중치)
- 왜 이게 더 좋은지: 우선순위 큐의 `log V` 비용이 사라져, 이론적으로 O(E log V)보다 빠릅니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) 자료구조/성능 함정: 현재 코드는 경로 단축 여부와 관계없이 모든 인접 정점을 우선순위 큐에 추가합니다. 이는 큐의 크기를 불필요하게 늘려 성능을 크게 저하시킵니다.
- 2) 미세한 버그 가능성: `ans[b.second]`를 갱신 후, 그 값을 다시 `pq.push`에 사용하고 있습니다. `new_dist`와 같은 임시 변수를 사용해 갱신 로직을 명확히 분리하는 것이 실수를 줄입니다.
- 3) 경계/오버플로: `ans`의 초기값 `1e9`는 `int` 범위 내에서 안전합니다. 문제의 최대 경로 합(약 3,000,000)보다도 충분히 커서 INF 값으로 적절합니다.

## 즉시 수정 액션(최대 4개)
- 1. 경로가 실제로 짧아지는 경우에만 우선순위 큐에 `push` 하도록 로직을 수정하세요.

   ```cpp
   // 수정 전
   for (edge b : A[a.second]) {
       ans[b.second] = min(ans[b.second], ans[a.second] + b.first);
       pq.push({ ans[b.second], b.second });
   }

   // 수정 후
   for (edge b : A[a.second]) {
       int new_dist = ans[a.second] + b.first;
       if (new_dist < ans[b.second]) {
           ans[b.second] = new_dist;
           pq.push({new_dist, b.second});
       }
   }
   ```
- 2. `visited` 배열 대신, 큐에서 꺼낸 거리와 현재 최단 거리를 비교하는 방식으로 메모리를 절약하고 코드를 단순화할 수 있습니다.
   ```cpp
   // if (visited[a.second]) continue; 대신
   if (a.first > ans[a.second]) continue; // 큐에 저장된 거리가 최신 정보가 아니면 무시
   // 이후 visited 배열 관련 코드 모두 제거
   ```

```REVIEW_EXAMPLE
# 제목: 더 빠른 풀이: 다이얼(Dial) 알고리즘 스케치
- 적용 조건: 간선 가중치(W)의 최댓값이 작아 W*V가 E*logV보다 작을 때 유리합니다.
- 핵심 아이디어: 우선순위 큐 대신, 가중치 크기만큼의 '버킷' 배열을 순환하며 사용합니다. i번 버킷은 시작점으로부터의 거리가 i인 정점들을 관리하여, logV 비용을 상수 시간 연산으로 대체합니다.
- 복잡도: O(E + W*V)
- 구현 스케치(C++):
  ```cpp
  vector<vector<pair<int, int>>> adj(V + 1);
  vector<int> dist(V + 1, 1e9);
  vector<vector<int>> buckets(11); // 최대 가중치 10 + 1
  
  dist[start_node] = 0;
  buckets[0].push_back(start_node);
  int nodes_processed = 0;

  for (int d = 0; nodes_processed < V; ++d) {
      int bucket_idx = d % 11;
      while (!buckets[bucket_idx].empty()) {
          int u = buckets[bucket_idx].back();
          buckets[bucket_idx].pop_back();

          if (dist[u] < d) continue; // 이미 더 짧은 경로로 처리됨
          nodes_processed++;

          for (auto& edge : adj[u]) {
              int v = edge.first;
              int weight = edge.second;
              if (dist[u] + weight < dist[v]) {
                  dist[v] = dist[u] + weight;
                  buckets[dist[v] % 11].push_back(v);
              }
          }
      }
  }
  ```
```