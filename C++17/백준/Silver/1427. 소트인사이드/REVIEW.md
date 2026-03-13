# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Silver/1427. 소트인사이드/소트인사이드.cc`

## 한 줄 결론
- (이 문제는) **선택 정렬 직접 구현** / 복잡도: O(L²) / C++ 표준 라이브러리 미사용

## 더 빠른/더 안전한 풀이(필수)
- 아이디어: `<algorithm>` 헤더의 `std::sort` 함수를 사용해 한 줄로 정렬을 끝냅니다.
- 복잡도: O(L log L) (L: N의 자릿수)
- 왜 이게 더 좋은지: 코드가 극도로 간결해지고, 직접 구현 시 발생할 수 있는 실수를 원천 차단합니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) **직접 구현의 비효율**: 자릿수(최대 10개)가 적어 성능 문제는 없으나, C++에서는 `std::sort` 사용이 표준입니다.
- 2) **자료형 불일치**: `swap` 로직에서 `char` 타입인 `n[maxIdx]`를 `int tmp`에 담고 있습니다. 현재 문제에선 괜찮지만, 타입을 일치시키거나(`char tmp`) `std::swap`을 쓰는 것이 안전합니다.
- 3) **헤더 관리**: 사용하지 않는 `<vector>` 헤더가 포함되어 있습니다. 불필요한 헤더는 제거하는 것이 좋습니다.

## 즉시 수정 액션(최대 4개)
- 1. `#include <algorithm>`과 `#include <functional>`을 추가하세요.
- 2. 직접 구현한 for 루프 전체를 `sort(n.begin(), n.end(), greater<char>());` 한 줄로 교체하세요.
- 3. 불필요한 `#include <vector>`를 제거하세요.
- 4. `#include <string>`을 명시적으로 추가하는 것이 좋은 습관입니다.

```REVIEW_EXAMPLE
# 제목: std::sort를 이용한 한 줄 풀이
- 적용 조건: C++에서 정렬이 필요할 때 항상 가장 먼저 고려해야 할 표준적인 방법입니다.
- 핵심 아이디어: 문자열을 문자(char)의 배열로 보고, `std::sort`에 내림차순 정렬 옵션(`std::greater<char>()`)을 주어 정렬합니다.
- 복잡도: O(L log L) (L은 자릿수)
- 구현 스케치(선택):
```cpp
#include <iostream>
#include <string>
#include <algorithm>
#include <functional> // std::greater

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string n;
    std::cin >> n;

    // 문자열의 문자들을 내림차순으로 정렬
    std::sort(n.begin(), n.end(), std::greater<char>());

    std::cout << n;
    return 0;
}
```