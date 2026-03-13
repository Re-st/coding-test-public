# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Silver/1427. 소트인사이드/소트인사이드.cc`

## 한 줄 결론
- (이 문제는) **선택 정렬** / 복잡도: O(L²), L은 자릿수 / 직접 구현보다 표준 라이브러리 사용이 안전합니다.

## 더 빠른/더 안전한 풀이(필수)
- **아이디어**: C++ 표준 라이브러리의 `std::sort` 함수를 사용해 한 줄로 정렬합니다.
- **복잡도**: O(L log L)
- **왜 이게 더 좋은지**: 코드가 극도로 간결해지고, 직접 구현 시 발생할 수 있는 미세한 실수를 원천 차단합니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) **(문제 없음)** 루프 조건 `i < n.length() - 1`과 `j = i + 1`은 선택 정렬의 표준적인 구현으로, 이 문제에서는 올바르게 동작합니다.
- 2) **변수 타입:** 문자를 임시 저장하는 `tmp` 변수를 `int`로 선언했습니다. `char`가 더 적합하며 의도치 않은 형변환을 막습니다.
- 3) **성능 함정:** 자릿수(L)가 최대 10개라 O(L²)도 괜찮지만, 일반적인 상황에서는 `std::sort` 같은 검증된 고성능 함수를 쓰는 게 정석입니다.

## 즉시 수정 액션(최대 4개)
- 1. `#include <algorithm>`과 `#include <functional>`을 추가하세요.
- 2. 9~16행의 직접 구현한 이중 for문을 아래 한 줄로 대체하세요.
   ```cpp
   sort(n.begin(), n.end(), greater<char>());
   ```

```REVIEW_EXAMPLE
# 제목: std::sort를 이용한 더 깔끔한 풀이
- 적용 조건: C++에서 컨테이너 정렬이 필요할 때 항상 우선적으로 고려해야 합니다.
- 핵심 아이디어: <algorithm> 헤더의 sort 함수와 비교자(greater)를 이용해 내림차순으로 정렬합니다.
- 복잡도: O(L log L)
- 구현 스케치(C++):
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>  // sort
#include <functional> // greater

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string n;
    std::cin >> n;

    // 이 한 줄로 모든 정렬 로직을 대체할 수 있습니다.
    std::sort(n.begin(), n.end(), std::greater<char>());

    std::cout << n;
    return 0;
}
```