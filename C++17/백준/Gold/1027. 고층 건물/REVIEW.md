# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `C++17/백준/Gold/1027. 고층 건물/고층 건물.cc`

## 한 줄 결론
- (이 문제는) **[브루트포스/기하학]** / 복잡도: O(N^2) / `double` 기울기 비교 시의 정밀도 오류가 가장 위험합니다.

## 더 빠른/더 안전한 풀이(필수)
- 아이디어: 현재 O(N^2) 접근은 최적이지만, `double` 대신 `long long`을 사용한 분수(기울기) 비교로 부동소수점 오차를 원천 차단해야 합니다.
- 복잡도: O(N^2)
- 왜 이게 더 좋은지: 두 기울기 a/b, c/d 비교를 a*d, c*b 비교로 바꿔, 오차 없는 정수 연산만으로 답을 구하므로 훨씬 안전합니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) 자료구조/성능 함정: `(double) (h[i + di] - h[i]) / di` 와 같이 `double`로 기울기를 계산하고 비교하면, 높이와 거리 차이가 클 때 정밀도 한계로 오답이 발생할 수 있습니다.
- 2) 구현 방식: 현재 코드는 `i` 기준 오른쪽만 탐색하며 `ok[i]`와 `ok[i+di]`를 동시에 갱신합니다. 이 방식은 간결하지만, 각 건물에서 왼쪽/오른쪽을 명시적으로 나누어 세는 방식보다 디버깅이 어렵습니다.
- 3) 최대값 탐색: 최종 결과는 보이는 빌딩의 최대 개수이므로 `max_element`를 쓰는 것이 `pair`를 만들고 루프를 도는 것보다 간결합니다. 현재 코드에선 불필요하게 인덱스까지 찾고 있습니다.

## 즉시 수정 액션(최대 4개)
- 1. 기울기 비교 시 `(h_j-h_i)/(j-i)` 형태의 나눗셈 대신 `(h_j-h_i)*(k-i)` 형태의 곱셈 비교로 바꿔 `long long`으로 오차 없이 계산하세요.
- 2. (권장) 가독성과 디버깅 편의를 위해, 각 건물 `i`에 대해 왼쪽, 오른쪽을 별도 루프로 탐색하는 구조로 리팩토링하세요.
- 3. `maxes` 변수와 관련 루프를 `cout << *max_element(ok, ok + N);` 한 줄로 교체하세요.
- 4. 불필요한 헤더 `<string>`을 제거하세요.

```REVIEW_EXAMPLE
# 제목: 부동소수점 오차 없는 풀이 스케치
- 적용 조건: 기울기 비교가 필요하며, 좌표가 정수일 때 항상 유리합니다.
- 핵심 아이디어: 두 기울기 a/b와 c/d의 대소 비교는 a*d와 c*b의 대소 비교와 같습니다(단, b, d 부호 고려). 이를 이용해 모든 연산을 정수 범위(long long) 내에서 처리하여 오차를 없앱니다.
- 복잡도: O(N^2)
- 구현 스케치(C++):
```cpp
int max_visible = 0;
for (int i = 0; i < N; ++i) {
    int current_visible = 0;
    
    // 오른쪽 탐색
    long long max_n = -2e18, max_d = 1; // 기울기 분자/분모
    for (int j = i + 1; j < N; ++j) {
        long long n = h[j] - h[i];
        long long d = j - i;
        // n/d > max_n/max_d  => n * max_d > max_n * d
        if (n * max_d > max_n * d) {
            current_visible++;
            max_n = n;
            max_d = d;
        }
    }

    // 왼쪽 탐색
    long long min_n = 2e18, min_d = 1; // 기울기 분자/분모
    for (int j = i - 1; j >= 0; --j) {
        long long n = h[j] - h[i];
        long long d = j - i; // d는 음수
        // n/d < min_n/min_d => n * min_d > min_n * d (d가 음수라 부등호 반전)
        if (n * min_d > min_n * d) {
            current_visible++;
            min_n = n;
            min_d = d;
        }
    }
    max_visible = max(max_visible, current_visible);
}
cout << max_visible;
```
```