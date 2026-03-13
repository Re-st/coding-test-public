# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Gold/2098. 외판원 순회/외판원 순회.cc`

## 한 줄 결론
- **비트마스크 DP** / 복잡도: O(N² * 2^N) / DP 테이블을 1차원으로 압축한 인덱싱 방식이 위험합니다.

## 더 빠른/더 안전한 풀이(필수)
- 아이디어: DP 상태를 `dp[현재도시][방문한_도시_마스크]` 2차원 배열로 명확히 하고, 미방문 상태를 -1로 초기화하여 안전성을 높입니다.
- 복잡도: O(N² * 2^N) (동일)
- 왜 이게 더 좋은지: 2차원 배열이 인덱싱 실수를 막고, 코드 의도가 명확해져 유지보수가 쉬워집니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) DP 인덱싱: `(curr << n) + leftover` 방식은 `n`에 따라 메모리 접근 간격이 바뀌어 복잡하고 실수하기 쉽습니다.
- 2) DP 초기값: `cost` 배열을 0으로 초기화하고 `if(cost[...])`로 값을 확인하는데, 이는 "계산 안 됨"과 "계산 결과가 0"을 구분하지 못하는 잠재적 문제입니다(이 문제에선 비용이 양수라 괜찮음).
- 3) '불가능' 경로 처리: `ret = 100000000`으로 초기화 후 이 값과 비교하여 불가능 여부를 판단하는데, `const int INF`를 쓰는 것이 더 명확하고 안전합니다.

## 즉시 수정 액션(최대 4개)
- DP 배열을 `int dp[16][1 << 16];` 로 바꾸고 `dp[curr][leftover]`로 접근하세요.
- DP 배열 초기값을 `0` 대신 `-1`로 채우고, `if (dp[curr][leftover] != -1)`로 명시적으로 검사하세요.
- `100000000` 대신 `const int INF = 1e9;` 같은 상수를 정의해 사용하세요.
- `leftover - (1 << i)`를 비트 연산의 의도가 명확한 `leftover ^ (1 << i)`로 바꾸세요.

```REVIEW_EXAMPLE
# 제목: 더 안전하고 가독성 좋은 풀이 스케치
- 적용 조건: 현재 풀이와 시간 복잡도는 동일하지만, 인덱싱 실수나 상태 값 혼동 같은 버그를 줄이고 싶을 때.
- 핵심 아이디어: DP 테이블을 `int dp[16][1<<16]` 2차원 배열로 명시적으로 선언하고, 아직 계산되지 않은 상태를 `-1`로, 불가능한 경로를 `INF`로 구분하여 관리합니다.
- 복잡도: O(N² * 2^N)
- 구현 스케치(C++):
// dp[curr][visited]: 현재 curr에 있고, visited 마스크의 도시들을 방문했을 때
// 나머지 도시들을 모두 방문하고 시작점(0)으로 돌아가는 최소 비용
const int INF = 1e9;
int dp[16][1 << 16]; // -1로 초기화 필요

int solve(int curr, int visited) {
    if (visited == (1 << n) - 1) { // 모두 방문
        return (w[curr][0] != 0) ? w[curr][0] : INF;
    }
    if (dp[curr][visited] != -1) return dp[curr][visited];

    int min_cost = INF;
    for (int next = 0; next < n; ++next) {
        if (!(visited & (1 << next)) && w[curr][next] != 0) {
            min_cost = min(min_cost, w[curr][next] + solve(next, visited | (1 << next)));
        }
    }
    return dp[curr][visited] = min_cost;
}

// 최초 호출: solve(0, 1 << 0);
```