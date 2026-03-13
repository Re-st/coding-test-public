# 제목: 더 안전한 Union 연산 (Union by Rank)
- 적용 조건: Union-Find 알고리즘의 안정적인 성능 보장이 필요할 때 항상 권장됩니다.
- 핵심 아이디어: 각 집합(트리)의 높이를 `rank` 배열에 기록하고, `union` 시 높이가 낮은 트리를 높은 트리의 루트에 연결합니다. 높이가 같으면 한쪽에 합치고 `rank`를 1 증가시킵니다.
- 복잡도: O(M * α(N))

- 구현 스케치(C++):
vector<int> parent;
vector<int> ranks; // rank 배열 추가

// Union 함수를 rank 기반으로 수정
void Union(int a, int b) {
    a = Find(a);
    b = Find(b);
    if (a == b) return;

    if (ranks[a] < ranks[b]) {
        parent[a] = b;
    } else if (ranks[a] > ranks[b]) {
        parent[b] = a;
    } else { // ranks[a] == ranks[b]
        parent[b] = a;
        ranks[a]++;
    }
}

// main 함수 내 초기화 부분
// ...
parent.resize(n + 1);
ranks.resize(n + 1, 0); // rank 배열 초기화
for (int i = 0; i <= n; i++) parent[i] = i;
// ...