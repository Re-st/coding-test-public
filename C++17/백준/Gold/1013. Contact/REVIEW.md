# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `C++17/백준/Gold/1013. Contact/Contact.cc`

## 한 줄 결론
- **재귀 백트래킹** / 복잡도: O(2^N) / `1+` 패턴 처리 중 `++idx`의 반복 사용이 코드 이해를 방해하고 버그 발생 위험이 높음.

## 더 빠른/더 안전한 풀이(필수)
- 아이디어: 재귀 함수에 메모이제이션(DP)을 적용해 `check(idx)`의 중복 계산을 제거합니다.
- 복잡도: O(N^2)
- 왜 이게 더 좋은지: N=200일 때 지수 시간 복잡도는 시간 초과 위험이 매우 크나, DP 적용 시 N^2으로 안정적인 통과가 보장됩니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) 성능 함정: `10011...1`과 같은 입력에서 `check(k)`가 반복 호출되어 지수 시간이 걸립니다. N 범위(최대 200)를 고려할 때 시간 초과가 발생할 수 있습니다.
- 2) 인덱스 관리: `if(check(++idx))`처럼 재귀 호출과 인덱스 증가를 한 줄에 사용하면, 호출 결과와 무관하게 `idx`가 변경됩니다. 이는 코드 흐름을 예측하기 어렵게 만듭니다.
- 3) 경계 조건 모호성: `100+1+` 패턴에서 여러 개의 `1`이 연속될 때, 어디까지가 현재 패턴의 `1+`이고 어디부터가 다음 패턴의 시작인지 모든 분기점을 탐색해야 합니다. 현재 재귀 구조가 이를 다루지만 매우 복잡합니다.

## 즉시 수정 액션(최대 4개)
- 1. `check` 함수에 `int dp[201]`과 같은 메모이제이션 배열을 추가하여 중복 계산을 방지하세요.
- 2. `100+1+` 패턴의 `1`들을 처리할 때, `++idx` 대신 별도의 `for` 루프를 사용해 가독성과 안정성을 높이세요.
- 3. (필수) 테스트 케이스마다 `dp` 배열을 `-1` 등으로 초기화하는 로직을 추가하세요.
- 4. 빠른 입출력을 위해 `main` 함수 시작에 `ios_base::sync_with_stdio(false); cin.tie(NULL);`를 추가하는 것을 고려하세요.

```REVIEW_EXAMPLE
# 제목: DP(메모이제이션)를 적용한 안정적인 풀이
- 적용 조건: N이 20 이상으로 커져 지수 시간 복잡도의 재귀가 시간 초과될 위험이 있을 때.
- 핵심 아이디어: `check(idx)`의 결과를 `dp[idx]`에 저장하여, 동일한 `idx`에 대한 함수 호출이 발생하면 계산 없이 즉시 저장된 값을 반환합니다.
- 복잡도: O(N^2)
- 구현 스케치(C++):
```cpp
#include <cstring> // for memset

// ... (기존 코드)
int memo[201];
string tc;
int N;

bool check(int idx) {
    if (idx == N) return true;
    if (memo[idx] != -1) return memo[idx] == 1;

    bool res = false;
    // (01) 패턴
    if (idx + 1 < N && tc[idx] == '0' && tc[idx+1] == '1') {
        if (check(idx + 2)) res = true;
    }
    // (100+1+) 패턴
    if (!res && idx + 3 < N && tc[idx] == '1' && tc[idx+1] == '0' && tc[idx+2] == '0') {
        int i = idx + 3;
        while (i < N && tc[i] == '0') i++;
        if (i < N && tc[i] == '1') { // 1+의 시작
            while (i < N && tc[i] == '1') {
                if (check(i + 1)) { res = true; break; }
                i++;
            }
        }
    }
    return (memo[idx] = res) == 1;
}

int main() {
    // ... cin >> T;
    while (T--) {
        cin >> tc;
        N = tc.size();
        memset(memo, -1, sizeof(memo));
        if (check(0)) cout << "YES\n"; else cout << "NO\n";
    }
}
```
```