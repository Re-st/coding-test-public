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