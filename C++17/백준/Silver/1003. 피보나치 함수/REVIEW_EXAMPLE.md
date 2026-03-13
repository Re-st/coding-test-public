# 제목: 바텀업 DP를 이용한 더 직관적인 풀이
- 적용 조건: 재귀 호출의 스택 오버헤드를 피하고 코드를 더 명확하게 만들고 싶을 때.
- 핵심 아이디어: 0과 1의 호출 횟수에 대한 점화식을 직접 사용합니다.
  - `dp[i] = { i번째 피보나치 수를 구할 때 0과 1의 호출 횟수 }`
  - `dp[i].zeros = dp[i-1].zeros + dp[i-2].zeros`
  - `dp[i].ones = dp[i-1].ones + dp[i-2].ones`
- 복잡도: O(N_max) (전처리) + O(T) (쿼리 처리)
- 구현 스케치:
pair<int, int> dp[41];

void precompute() {
    dp[0] = {1, 0};
    dp[1] = {0, 1};
    for (int i = 2; i <= 40; ++i) {
        dp[i].first = dp[i-1].first + dp[i-2].first;
        dp[i].second = dp[i-1].second + dp[i-2].second;
    }
}

int main() {
    // ... 입출력 설정 ...
    precompute();
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << dp[n].first << " " << dp[n].second << '\n';
    }
}