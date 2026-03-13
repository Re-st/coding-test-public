# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Gold/1717. 집합의 표현/집합의 표현.cc`

## 한 줄 결론
- (이 문제는) **Union-Find(경로 압축)** / 복잡도: O(Mα(N)) / Union-by-Size 최적화 부재

## 더 빠른/더 안전한 풀이(필수)
- 아이디어: `Union` 시, 크기가 더 작은 트리를 큰 트리에 합쳐 트리의 균형을 유지합니다 (Union-by-Size).
- 복잡도: O(Mα(N))
- 왜 이게 더 좋은지: 트리의 높이를 낮게 유지하여 최악의 경우에도 빠른 `Find` 성능을 보장하고, 더 안정적입니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) 초기값/시작점/종료조건: `parent[i] = i` 초기화는 분리 집합의 핵심이며, 올바르게 구현되었습니다.
- 2) 인덱스/경계/오버플로/방문처리: `parent` 배열 크기를 `n+1`로 설정하여 0부터 n까지의 원소를 안전하게 다룹니다.
- 3) 자료구조/성능 함정: 경로 압축은 적용되었으나, 현재 `Union` 방식은 트리가 한쪽으로 길어지는 최악의 경우를 만들 수 있습니다.

## 즉시 수정 액션(최대 4개)
- 1. **Union-by-Size 최적화 적용**: 각 집합의 크기를 저장할 `vector<int> sz`를 추가하고, `Union` 시 크기를 비교해 합치도록 수정하세요.
- 2. `Union` 함수 내에서 이미 루트를 찾았으므로, `parent[b] = a` 대신 `parent[root_b] = root_a` 형태가 더 명확합니다(현재 코드는 이미 그렇게 동작).

```REVIEW_EXAMPLE
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
```