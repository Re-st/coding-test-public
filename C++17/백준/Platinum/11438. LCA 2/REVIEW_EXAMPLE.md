# 제목: BFS를 이용한 더 안전한 전처리
- 적용 조건: N이 커서 재귀 깊이가 시스템 스택 제한을 초과할 수 있을 때 유리합니다.
- 핵심 아이디어: 재귀 DFS 대신 큐(Queue)를 사용하는 BFS로 각 노드의 깊이(`height`)와 직계 부모(`parent[i][0]`)를 계산합니다. 이는 스택 메모리 대신 힙 메모리를 사용하므로 스택 오버플로 위험을 원천적으로 방지합니다.
- 복잡도: O(N)
- 구현 스케치(C++):
#include <queue>

void setup_tree_by_bfs() {
    queue<int> q;
    
    visited[1] = true;
    height[1] = 0;
    q.push(1);
    
    while(!q.empty()){
        int u = q.front();
        q.pop();
        
        for(int v : T[u]){
            if(!visited[v]){
                visited[v] = true;
                height[v] = height[u] + 1;
                parent[v][0] = u;
                q.push(v);
            }
        }
    }
}