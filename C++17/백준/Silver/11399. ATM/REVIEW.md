# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Silver/11399. ATM/ATM.cc`

## 한 줄 결론
- (이 문제는) **그리디+정렬** / 복잡도: O(N^2) / 제일 위험한 실수: C++ 표준 `sort` 대신 O(N^2) 삽입 정렬을 직접 구현한 점.

## 더 빠른/더 안전한 풀이(필수)
- 아이디어: 모든 시간을 `vector`에 저장한 후, `std::sort`로 한 번에 정렬합니다.
- 복잡도: O(N log N)
- 왜 이게 더 좋은지: 표준 라이브러리 함수가 훨씬 빠르고(N=1000일 때 약 100배), 코드가 간결하며, 직접 구현 시 발생할 수 있는 버그를 원천 차단합니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) 정렬 구현 실수: 직접 구현한 삽입 정렬의 `for (int j = i - 1; j >= nowLoc; j--)` 루프는 경계 조건(off-by-one) 실수가 발생하기 쉽습니다.
- 2) 시간 복잡도 함정: N이 1,000이라 O(N^2) 풀이가 통과되지만, N이 10^5 규모였다면 시간 초과가 발생했을 것입니다.
- 3) 오버플로 가능성: 현재 제약(N, Pi ≤ 1000)에선 `int`로 충분하나, 값이 조금만 더 커지면 총합이 `int` 범위를 넘을 수 있어 `long long`을 고려하는 습관이 안전합니다.

## 즉시 수정 액션(최대 4개)
- 1. `#include <algorithm>` 헤더를 추가하세요.
- 2. 입력을 받는 반복문과 정렬하는 반복문을 분리하세요.
- 3. 입력 로직을 `for(int i=0; i<n; i++) cin >> pi[i];`로 단순화하세요.
- 4. 정렬 로직 전체를 `std::sort(pi.begin(), pi.end());` 한 줄로 대체하세요.

```REVIEW_EXAMPLE
# 제목: 더 효율적인 std::sort 기반 풀이
- 적용 조건: 거의 항상 현재 풀이보다 유리하며, 특히 N이 클 때 성능 차이가 극명합니다.
- 핵심 아이디어: 입력을 모두 받은 뒤, 내장 정렬 함수 `std::sort`를 사용해 O(N log N)으로 정렬하고, 그 후 누적합을 계산합니다.
- 복잡도: O(N log N)
- 구현 스케치(C++):
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n;
    std::cin >> n;
    std::vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> p[i];
    }

    std::sort(p.begin(), p.end());

    int total_wait_time = 0;
    int accumulated_time = 0;
    for (int time : p) {
        accumulated_time += time;
        total_wait_time += accumulated_time;
    }
    std::cout << total_wait_time;
    return 0;
}
```