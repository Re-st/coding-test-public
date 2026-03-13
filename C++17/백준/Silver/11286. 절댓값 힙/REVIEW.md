# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Silver/11286. 절댓값 힙/절댓값 힙.cc`

## 한 줄 결론
- (이 문제는) **우선순위 큐(커스텀 비교)** / 복잡도: O(N log N) / 비교 함수 로직 오류

## 더 빠른/더 안전한 풀이(필수)
- 현 접근이 거의 최선입니다. 문제의 요구사항(특정 조건의 최솟값 반복 추출)은 우선순위 큐를 사용하는 것이 가장 정석적이고 효율적입니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) (문제 없음)
- 2) 인덱스/경계/오버플로/방문처리: `x`의 범위가 `-2^31`을 포함했다면 `abs(INT_MIN)`에서 오버플로가 발생할 수 있었으나, 문제 조건(`-2^31 < x`) 덕분에 안전합니다.
- 3) 자료구조/성능 함정: `priority_queue`는 기본이 max-heap이라, min-heap을 만들려면 비교 함수가 `a > b`를 반환해야 합니다. 현재 코드는 이 규칙을 올바르게 구현했습니다.

## 즉시 수정 액션(최대 4개)
- 1. 변수명 `mydeque`를 `abs_heap` 또는 `pq`로 변경해 자료구조의 역할을 명확히 하세요.
- 2. (선택) C++11 이상 람다(lambda)를 사용하면 `compare` 구조체 없이 코드를 더 간결하게 작성할 수 있습니다.

```REVIEW_EXAMPLE
# 제목: 람다(lambda)를 이용한 간결한 풀이
- 적용 조건: C++11 이상 환경에서 코드를 더 깔끔하게 작성하고 싶을 때.
- 핵심 아이디어: 별도 구조체 선언 없이, 람다 표현식으로 비교 로직을 정의하여 `priority_queue` 생성자에 바로 전달합니다.
- 복잡도: O(N log N) (동일)
- 구현 스케치(C++):
```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <cmath> // abs

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    auto cmp = [](int left, int right) {
        if (abs(left) != abs(right)) {
            return abs(left) > abs(right);
        }
        return left > right;
    };
    std::priority_queue<int, std::vector<int>, decltype(cmp)> pq(cmp);

    int n, x;
    std::cin >> n;
    while (n--) {
        std::cin >> x;
        if (x == 0) {
            if (pq.empty()) {
                std::cout << 0 << '\n';
            } else {
                std::cout << pq.top() << '\n';
                pq.pop();
            }
        } else {
            pq.push(x);
        }
    }
    return 0;
}
```
```