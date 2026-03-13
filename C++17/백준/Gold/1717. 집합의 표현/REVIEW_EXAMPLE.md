# 제목: Union-by-Size 최적화 적용
- 적용 조건: N, M이 매우 크거나 최악의 성능을 방지하고 싶을 때.
- 핵심 아이디어: 각 집합의 크기를 기록하는 `sz` 배열을 유지합니다. `Union` 시, 항상 더 작은 집합을 더 큰 집합에 합쳐 트리의 높이가 깊어지는 것을 방지합니다.
- 복잡도: O(Mα(N))
- 구현 스케치(C++):
vector<int> parent;
vector<int> sz; // 각 집합의 크기를 저장

// main 함수에서 sz 초기화
// sz.assign(n + 1, 1);

void Union(int a, int b) {
    a = Find(a);
    b = Find(b);
    if (a == b) return;

    if (sz[a] < sz[b]) swap(a, b); // 항상 b를 a에 합치도록 정렬
    parent[b] = a;
    sz[a] += sz[b];
}

int Find(int a) {
    if (parent[a] == a) return a;
    return parent[a] = Find(parent[a]); // 경로 압축
}