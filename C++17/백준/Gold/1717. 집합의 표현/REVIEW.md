# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Gold/1717. 집합의 표현/집합의 표현.cc`

## 한 줄 결론
- **[분리 집합(Union-Find)]** / 복잡도: O(M * α(N)) / 제일 위험한 실수: `Union` 최적화(rank/size) 부재

## 더 빠른/더 안전한 풀이(필수)
- 현 접근이 거의 최선이지만, `Union` 연산을 더 안정적으로 만들 수 있습니다.
- **아이디어**: Union by Rank/Size 최적화. 합집합 연산 시, 높이가 낮은 트리를 높은 쪽에 붙여 트리의 균형을 유지합니다.
- **복잡도**: O(M * α(N)) (동일하지만, 최악의 경우 성능을 보장)
- **왜 이게 더 좋은지**: `Find` 연산이 한쪽으로 치우친 트리(연결 리스트 형태)를 탐색하는 최악의 경우를 방지하여 성능 안정성을 높입니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
1) 초기값/시작점/종료조건: `parent` 배열을 `parent[i] = i`로 초기화하는 부분은 완벽합니다.
2) 인덱스/경계/오버플로/방문처리: `vector` 크기를 `n+1`로 설정하여 `0`부터 `n`까지의 모든 원소를 문제없이 다룹니다.
3. **자료구조/성능 함정**: `Union` 함수가 두 트리를 임의로 합치고 있습니다. 이는 최악의 경우 트리가 긴 사슬 형태가 되어 `Find` 성능을 저하시킬 수 있습니다. (현재는 경로 압축만으로도 통과)

## 즉시 수정 액션(최대 4개)
1. `Union by Rank` 최적화를 위해 `rank` 배열을 추가하고 0으로 초기화하세요.
   ```cpp
   vector<int> ranks(n + 1, 0);
   ```
2. `Union` 함수에서 두 루트의 `rank`를 비교하여, `rank`가 낮은 트리를 높은 트리에 합병하도록 수정하세요.

```REVIEW_EXAMPLE
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
```