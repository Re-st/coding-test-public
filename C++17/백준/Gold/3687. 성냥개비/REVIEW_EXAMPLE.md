# 제목: DP를 이용한 안정적인 최소값 계산
- 적용 조건: N의 범위가 작아(<=100) 전처리가 가능한 모든 경우
- 핵심 아이디어: `dp[i]`를 `i`개 성냥개비로 만들 수 있는 가장 작은 수(문자열)로 정의합니다. `dp[i]`는 `dp[i-k]`(k는 각 숫자를 만드는 성냥개비 수)에 해당 숫자를 덧붙인 값들 중 가장 작은 값으로 갱신합니다.
- 복잡도: O(N * |사용 가능 숫자|)
- 구현 스케치(C++):
string dp[101];

// 문자열 비교 함수 (길이가 짧거나, 길이가 같으면 사전순)
string min_str(string a, string b) {
    if (a.length() != b.length()) return a.length() < b.length() ? a : b;
    return min(a, b);
}

void precompute() {
    int cost[] = {6, 2, 5, 5, 4, 5, 6, 3, 7}; // digits 0-8
    fill(dp, dp + 101, string(51, '9')); // 매우 큰 값으로 초기화

    dp[2]="1"; dp[3]="7"; dp[4]="4"; dp[5]="2"; dp[6]="6"; dp[7]="8";

    for (int i = 8; i <= 100; ++i) {
        for (int j = 0; j <= 8; ++j) { // 9는 6과 비용이 같으므로 생략
             if (i - cost[j] >= 2) {
                 dp[i] = min_str(dp[i], dp[i - cost[j]] + to_string(j));
             }
        }
    }
}