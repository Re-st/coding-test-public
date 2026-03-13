# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Platinum/11438. LCA 2/LCA 2.cc`

## 한 줄 결론
- (이 문제는) **[LCA/바이너리 리프팅]** / 복잡도: O((N+M)logN) / `LCA` 함수 내 높이 맞추기 로직이 가장 복잡한 부분입니다.

## 더 빠른/더 안전한 풀이(필수)
- 현 접근이 거의 최선입니다. 전처리 O(N log N), 쿼리당 O(log N)은 온라인 LCA 쿼리에 대한 표준 최적 풀이입니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) 초기값/시작점/종료조건: DFS 시작 시 루트(1번)의 `height`와 `parent` 초기화가 중요합니다. 현재 코드는 전역 변수 0초기화에 의존하여 `height[1]=0`, `parent[1][0]=0`이 되어 올바르게 동작합니다.
- 2) 인덱스/경계/오버플로/방문처리: `kmax` 값, 즉 희소 배열의 2번째 차원 크기 설정이 중요합니다. N=100,000일 때 `ceil(log2(N)) ≈ 17`이므로, 배열 크기 21과 `kmax` 계산은 안전합니다.
- 3) 자료구조/성능 함정: 재귀 기반 `setHeightParent`는 트리가 한쪽으로 치우친 경우(예: 1-2-..-N) 스택 오버플로를 유발할 수 있습니다. BFS로 바꾸면 더 안전합니다.

## 즉시 수정 액션(최대 4개)
- 1. **(안전성)** `setHeightParent`를 BFS로 변경하여 스택 오버플로 위험을 원천 차단하세요.
- 2. **(가독성)** `LCA` 함수의 불필요한 `doneHeightCalibration` 파라미터를 제거하세요.
- 3. **(단순화)** `LCA` 함수의 `return a != b ? parent[a][0] : a;`를 `return parent[a][0];`로 바꾸세요. `for`문 이후에는 항상 `a != b`이고, `parent[a][0]`가 답입니다.
- 4. **(명확성)** `kmax` 계산을 `(int)floor(log2(n))`으로 하면 의도가 더 명확해집니다.

```REVIEW_EXAMPLE
# 제목: 스택 오버플로 방지를 위한 BFS 기반 전처리
- 적용 조건: N이 크고(10만 이상) 트리의 깊이가 깊어질 수 있는 환경에서 안정성을 높입니다.
- 핵심 아이디어: 큐(Queue)를 사용한 너비 우선 탐색으로 각 노드의 깊이(`height`)와 직계 부모(`parent[i][0]`)를 계산합니다. 재귀를 사용하지 않아 스택 깊이와 무관하게 동작합니다.
- 복잡도: O(N)
- 구현 스케치(C++):
#include <queue>
void setHeightParentWithBFS() {
    queue<int> q;
    q.push(1);
    visited[1] = true;
    height[1] = 0;

    while(!q.empty()){
        int curr = q.front(); q.pop();
        for(int next : T[curr]){
            if(!visited[next]){
                visited[next] = true;
                height[next] = height[curr] + 1;
                parent[next][0] = curr;
                q.push(next);
            }
        }
    }
}
```