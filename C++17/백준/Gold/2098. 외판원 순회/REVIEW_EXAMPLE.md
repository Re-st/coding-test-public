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