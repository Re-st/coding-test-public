# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Silver/1920. 수 찾기/수 찾기.cc`

## 한 줄 결론
- (이 문제는) **이분 탐색** / 복잡도: O(N log N + M log N) / 제일 위험한 실수는 직접 구현한 이분 탐색의 경계 값 설정 오류입니다.

## 더 빠른/더 안전한 풀이(필수)
- **아이디어:** `std::unordered_set`을 사용해 N개 수를 모두 저장 후, M개 수의 존재 여부를 평균 O(1)에 확인합니다.
- **복잡도:** O(N + M) (평균)
- **왜 이게 더 좋은지:** 정렬 과정이 불필요해 코드가 더 간단하고, 평균 시간 복잡도도 더 우수합니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) **초기값/시작점/종료조건:** 재귀 호출의 종료 조건 `if (a > b) return false;`는 올바르나, 이런 경계 조건은 직접 구현 시 실수하기 가장 쉬운 부분입니다.
- 2) **인덱스/경계/오버플로:** `int m = (a + b) / 2;`는 인덱스 `a`, `b`의 합이 int 범위를 초과하면 오버플로가 발생할 수 있습니다. 여기서는 N이 10만이므로 안전하지만 `a + (b - a) / 2`가 더 안전한 습관입니다.
- 3) **자료구조/성능 함정:** 불필요한 `<queue>` 헤더를 포함했습니다. 또한, 전역 변수 `is`는 여러 테스트케이스가 있는 문제에서 초기화 누락의 원인이 될 수 있습니다.

## 즉시 수정 액션(최대 4개)
- 1. 직접 구현한 `exists` 함수 대신, C++ STL의 `std::binary_search(is.begin(), is.end(), now)`를 사용하세요. 코드가 한 줄로 줄고 실수가 사라집니다.
- 2. `exists` 함수에 전역 변수 `is` 대신 `const vector<int>&`로 참조 전달하여 의존성을 낮추는 것이 좋습니다.
- 3. 사용하지 않는 `<queue>` 헤더를 제거하세요.
- 4. `using namespace std;`는 실무에서 충돌 위험이 있으므로, `std::` 접두사를 사용하는 습관을 권장합니다.

```REVIEW_EXAMPLE
# 제목: 더 빠른 풀이 스케치 (해시셋)
- 적용 조건: 데이터의 순서와 무관하게 존재 여부만 빠르게 판별해야 할 때 유리합니다.
- 핵심 아이디어: N개의 숫자를 `std::unordered_set`에 모두 삽입(평균 O(N))한 후, M개의 각 숫자에 대해 `count()` 메소드로 존재 여부를 평균 O(1)에 확인합니다.
- 복잡도: O(N + M)

- 구현 스케치(C++):
```cpp
#include <iostream>
#include <unordered_set>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;
    std::unordered_set<int> s;
    for (int i = 0; i < n; ++i) {
        int num;
        std::cin >> num;
        s.insert(num);
    }

    int m;
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        int target;
        std::cin >> target;
        std::cout << s.count(target) << "\n";
    }
    return 0;
}
```
```