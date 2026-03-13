# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Silver/11004. K번째 수/K번째 수.cc`

## 한 줄 결론
- **Quickselect** / 복잡도: 평균 O(N), 최악 O(N^2) / 피벗 선택이 편향될 경우 O(N^2) 시간 초과

## 더 빠른/더 안전한 풀이(필수)
- **`std::nth_element` 사용**이 거의 모든 면에서 우월합니다.
  - 아이디어: K번째 원소를 제자리에 위치시키는 표준 라이브러리 함수를 사용합니다.
  - 복잡도: O(N) (최악의 경우 보장)
  - 왜 이게 더 좋은지: 직접 구현한 Quickselect의 O(N^2) 위험을 원천 차단하며, 코드가 단 한 줄로 간결해져 버그 가능성이 없습니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) **재귀 분기 조건**: `k`가 어느 파티션에 속하는지 판단하는 `k <= E`, `k >= S` 조건이 틀리면 오답 혹은 무한 루프에 빠질 수 있습니다.
- 2) **인덱스/경계**: K(1-based)와 인덱스(0-based)를 변환하는 `k-1`은 올바르나, 파티셔닝 루프의 `S <= E` 등 경계 조건 실수는 디버깅이 어렵습니다.
- 3) **성능 함정**: 현재의 중간 값 피벗 선택 방식은 정렬된 입력 등 단순 케이스는 방어하지만, 특정 패턴의 입력에 O(N^2) 성능 저하를 일으킬 수 있습니다. N이 500만이라 시간 초과 위험이 큽니다.

## 즉시 수정 액션(최대 4개)
1.  `quickSelection` 함수와 호출부를 아래 코드로 대체하세요.
    ```cpp
    #include <algorithm>
    // ... main 함수 내부
    std::nth_element(ai.begin(), ai.begin() + k - 1, ai.end());
    ```
2.  (현 구현 유지 시) 최악의 경우를 피하려면 피벗을 랜덤으로 선택하세요.
    ```cpp
    // 파티션 로직 시작 전
    int pivot_idx = s + rand() % (e - s + 1);
    swap(ai[pivot_idx], ai[(s + e) / 2]); // 중간 값 위치와 스왑
    ```
3.  불필요한 입력 확인 `if (!(cin >> n >> k))` 구문은 `cin >> n >> k;`로 단순화하는 것이 일반적입니다.

```REVIEW_EXAMPLE
# 제목: C++ 표준 라이브러리를 이용한 풀이
- 적용 조건: 전체 정렬이 아닌 K번째 원소만 찾을 때 항상 유리합니다.
- 핵심 아이디어: `std::nth_element`는 K번째 원소가 있어야 할 위치에 해당 원소를 가져다 놓는 O(N) 알고리즘입니다. (다른 원소들의 순서는 보장되지 않음)
- 복잡도: O(N) (Introselect 알고리즘 기반으로 최악의 경우에도 선형 시간 보장)
- 구현 스케치:
  ```cpp
  #include <iostream>
  #include <vector>
  #include <algorithm>

  int main() {
      std::ios_base::sync_with_stdio(false);
      std::cin.tie(NULL);

      int n, k;
      std::cin >> n >> k;

      std::vector<int> a(n);
      for (int i = 0; i < n; ++i) {
          std::cin >> a[i];
      }

      // a.begin() + (k-1) 위치에 k번째 작은 원소를 위치시킴
      std::nth_element(a.begin(), a.begin() + k - 1, a.end());

      std::cout << a[k - 1] << '\n';

      return 0;
  }
  ```
```