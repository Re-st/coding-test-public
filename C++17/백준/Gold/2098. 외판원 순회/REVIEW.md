# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Gold/2098. 외판원 순회/외판원 순회.cc`

## 한 줄 결론
- (이 문제는) **[비트마스크 DP]** / 복잡도: O(N² * 2^N) / `cost` 배열을 0으로 초기화하고 `if(cost[...])`로 방문 여부를 확인하는 것.

## 더 빠른/더 안전한 풀이(필수)
- 현 접근이 거의 최선입니다. N ≤ 16 제약에서 외판원 순회 문제는 O(N² * 2^N) 복잡도의 비트마스크 DP가 가장 표준적이고 효율적인 풀이입니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) 초기값/시작점/종료조건: `cost` 배열을 0으로 초기화하면, '계산된 비용 0'과 '미방문 상태'를 구분할 수 없습니다. 이 문제에서는 비용이 양수라 우연히 통과하지만, 항상 -1로 초기화하고 `!= -1`로 검사하는 것이 안전합니다.
- 2) 인덱스/경계/오버플로/방문처리: `cost[(curr << n) + leftover]`와 같이 2차원 상태를 1차원 인덱스로 압축하는 것은 가독성을 해치고 잠재적 버그를 유발합니다. `cost[curr][leftover]` 형태의 2차원 배열이 훨씬 명확합니다.
- 3) 자료구조/성능 함정: `100000000` 같은 매직 넘버는 `const int INF = ...;` 형태로 상수로 정의하여 관리하는 것이 좋습니다. 반환 값 `-1`도 '불가능'을 나타내는 상수로 정의하면 가독성이 향상됩니다.

## 즉시 수정 액션(최대 4개)
- 1. `cost` 배열을 -1로 초기화: `memset(cost, -1, sizeof(cost));` 또는 `fill` 사용.
- 2. 메모이제이션 확인 변경: `if (cost[(curr << n) + leftover])` -> `if (cost[...] != -1)`
- 3. (권장) `cost` 배열을 2차원으로 변경: `int cost[16][1 << 16];`
- 4. `INF` 값 상수로 정의: `const int INF = 1e9;`

```REVIEW_EXAMPLE
# 제목: 더 안전하고 읽기 쉬운 풀이 스케치
- 적용 조건: 현재 풀이와 동일한 알고리즘이지만, 코드 안정성과 가독성을 높이고 싶을 때 항상 권장됩니다.
- 핵심 아이디어: 2차원 DP 배열과 명시적인 `INF` 및 초기값(-1)을 사용하여 의도를 명확히 하고, '미방문'과 '경로 없음' 상태를 확실하게 구분합니다.
- 복잡도: O(N² * 2^N)
- 구현 스케치(C++):
const int INF = 1e9;
int N;
int W[16][16];
int dp[16][1 << 16]; // dp[현재 도시][방문한 도시 비트마스크]

int tsp(int curr, int visited) {
    // 모든 도시를 방문했다면 시작 도시(0)로 복귀
    if (visited == (1 << N) - 1) {
        return W[curr][0] ? W[curr][0] : INF;
    }

    // 메모이제이션 확인
    if (dp[curr][visited] != -1) return dp[curr][visited];

    dp[curr][visited] = INF;
    for (int next = 0; next < N; ++next) {
        // 이미 방문했거나 경로가 없는 경우 스킵
        if ((visited & (1 << next)) || W[curr][next] == 0) continue;

        int cost = W[curr][next] + tsp(next, visited | (1 << next));
        dp[curr][visited] = min(dp[curr][visited], cost);
    }
    return dp[curr][visited];
}

int main() {
    // ... 입력 처리 ...
    memset(dp, -1, sizeof(dp));
    cout << tsp(0, 1 << 0); // 0번 도시에서 시작 (0번 방문 처리)
}
```