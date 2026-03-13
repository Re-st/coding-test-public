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