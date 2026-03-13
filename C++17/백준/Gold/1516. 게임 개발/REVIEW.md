# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Gold/1516. 게임 개발/게임 개발.cc`

## 한 줄 결론
- (이 문제는) **위상 정렬** / 복잡도: O(N + E) / 선행 작업 완료 시간 계산 로직이 다소 복잡함

## 더 빠른/더 안전한 풀이(필수)
- 아이디어: 큐에서 노드 `u`를 꺼낼 때, `u`에 의존하는 다음 노드 `v`들의 최소 완료 시간을 `ans[v] = max(ans[v], ans[u] + reqtime[v])`로 갱신합니다.
- 복잡도: O(N + E)
- 왜 이게 더 좋은지: 역방향 그래프(`Ap`) 없이 구현 가능해 코드가 더 단순해지고 메모리 사용량이 줄어듭니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) 초기값/시작점/종료조건: 진입 차수가 0인 노드의 `ans` 값만 `reqtime`으로 초기화하고 나머지는 0으로 시작하는데, 이 의존성이 현재 로직을 복잡하게 만듭니다.
- 2) 인덱스/경계/오버플로/방문처리: 건물 N(최대 500), 시간(최대 10만)이므로 총 시간이 `int` 범위를 넘을 가능성은 낮지만, 문제 조건이 바뀌면 오버플로 위험이 있습니다.
- 3) 자료구조/성능 함정: 역방향 인접 리스트(`Ap`)는 불필요합니다. `ans[i]`를 계산하기 위해 `Ap[i]`를 순회하는 로직은 시간을 순방향으로 전파하는 방식으로 대체할 수 있습니다.

## 즉시 수정 액션(최대 4개)
- 1. 역방향 그래프 `Ap`를 제거하고, 위상 정렬 과정에서 시간 값을 순방향으로 전파하는 방식으로 변경하세요.
- 2. (현재 구조 유지 시) `ans[i]` 계산 로직을 `max_p = 0; for(int j: Ap[i]) max_p = max(max_p, ans[j]); ans[i] = max_p + reqtime[i];`와 같이 수정하여 가독성을 높이세요.
- 3. 변수명을 `A`는 `adj`, `ans`는 `completion_time` 등으로 더 명확하게 변경하는 것을 고려해보세요.

```REVIEW_EXAMPLE
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
```