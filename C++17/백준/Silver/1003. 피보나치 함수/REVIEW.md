# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Silver/1003. 피보나치 함수/피보나치 함수.cc`

## 한 줄 결론
- (이 문제는) **DP(메모이제이션)** / 복잡도: O(max(N)) / `cout` 내 두 함수 호출의 불명확한 평가 순서가 가장 위험합니다.

## 더 빠른/더 안전한 풀이(필수)
- **아이디어:** 0의 개수와 1의 개수를 담는 DP 배열을 Bottom-up 방식으로 N=40까지 미리 계산합니다.
- **복잡도:** O(max_N) 선계산 후, 테스트케이스당 O(1)
- **왜 이게 더 좋은지:** 재귀 호출과 부수 효과(side effect)가 없어 코드가 명확하고 안전하며, 테스트케이스가 많을수록 효율적입니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) **구현 순서 함정:** `cout << fibo(n-1) << " " << fibo(n)`에서 두 함수의 평가 순서는 C++ 표준이 보장하지 않습니다. 현재 코드는 `fibo(n-1)`이 먼저 실행된다는 우연에 의존하는 위험한 코드입니다.
- 2) **인덱스/경계:** `n=0`일 때 `fibo(n-1)`은 음수 인덱스 접근 위험이 있어 `if`문으로 따로 처리했습니다. DP로 풀면 이런 예외 분기 없이 일관되게 처리 가능합니다.
- 3) **자료구조:** 문제의 요구사항은 '0과 1의 호출 횟수'입니다. 피보나치 수 자체를 계산하기보다, `{0의 개수, 1의 개수}`를 쌍으로 저장하는 DP 배열(`pair<int, int> dp[41]`)이 더 직관적입니다.

## 즉시 수정 액션(최대 4개)
- 1. **(필수)** `fibo` 함수 호출을 두 줄로 분리해 평가 순서를 명시적으로 제어하세요.
   ```cpp
   int count_zero = (n == 0) ? 1 : fibo(n - 1);
   int count_one = fibo(n);
   cout << count_zero << " " << count_one << '\n';
   ```
- 2. **(권장)** 재귀 대신 for 루프를 사용하는 Bottom-up DP 방식으로 전환하여 안정성을 높이세요.
- 3. `endl` 대신 `'\n'` 사용: `cin.tie(NULL)`과 함께 사용할 때 불필요한 버퍼 플러시를 막아 성능에 유리합니다.

```REVIEW_EXAMPLE
# 제목: 더 직관적이고 안전한 Bottom-up DP 풀이
- 적용 조건: N의 최대값이 작고(e.g., ~40), 테스트케이스가 여러 개인 경우 매우 유리합니다.
- 핵심 아이디어: `dp[i] = {i일 때 0의 개수, i일 때 1의 개수}`로 정의. `dp[i]`의 각 원소는 `dp[i-1]`과 `dp[i-2]`의 각 원소 합과 같다는 점화식을 이용해 `dp[40]`까지 미리 계산합니다.
- 복잡도: O(max_N) 선계산 후, 테스트케이스당 O(1)
- 구현 스케치(C++):
```cpp
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

pair<int, int> dp[41];

void precompute() {
    dp[0] = {1, 0}; // N=0일 때 {0 개수, 1 개수}
    dp[1] = {0, 1}; // N=1일 때 {0 개수, 1 개수}
    for (int i = 2; i <= 40; ++i) {
        dp[i].first = dp[i-1].first + dp[i-2].first;
        dp[i].second = dp[i-1].second + dp[i-2].second;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    precompute();

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << dp[n].first << " " << dp[n].second << "\n";
    }
    return 0;
}
```
```