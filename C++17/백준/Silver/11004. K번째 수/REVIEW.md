# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Silver/11004. K번째 수/K번째 수.cc`

## 한 줄 결론
- (이 문제는) **퀵 셀렉트** / 복잡도: O(N) (평균), O(N^2) (최악) / 최악의 피벗 선택 시 시간 초과 위험

## 더 빠른/더 안전한 풀이(필수)
- 아이디어: C++ 표준 라이브러리 `std::nth_element`를 사용해 K번째 원소를 찾습니다.
- 복잡도: O(N)
- 왜 이게 더 좋은지: 직접 구현보다 버그 가능성이 없고, Introselect 알고리즘으로 O(N^2) 최악의 경우를 방지해 훨씬 안정적입니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) 성능 함정: 중앙 인덱스를 피벗으로 삼는 방식은 대부분 잘 작동하지만, 특정 데이터 패턴에서 최악의 경우(O(N^2))를 유발할 수 있습니다. N이 500만이므로 시간 초과 위험이 있습니다.
- 2) 재귀 호출 조건: `if (s < E && k <= E)` 와 `if (S < e && k >= S)`는 분할된 영역 중 어느 쪽을 탐색할지 정하는 핵심입니다. 경계 값 하나만 틀려도 오답이나 무한 루프에 빠집니다.
- 3) 파티션 로직: `while(S <= E)` 루프 내에서 피벗과 값을 비교하고 인덱스를 조정하는 로직은 사소한 실수로도 전체 알고리즘을 망가뜨릴 수 있어 구현 난이도가 높습니다.

## 즉시 수정 액션(최대 4개)
- 1. `quickSelection` 함수와 그 호출부를 `std::nth_element(ai.begin(), ai.begin() + k - 1, ai.end());` 한 줄로 대체하세요. 이것만으로 정답이며, 더 안전하고 간결합니다.

```REVIEW_EXAMPLE
# 제목: std::nth_element를 이용한 풀이
- 적용 조건: K번째로 작거나 큰 수를 찾아야 하고, 나머지 원소의 순서는 중요하지 않을 때.
- 핵심 아이디어: `std::nth_element`는 K번째 원소가 제자리에 오도록 배열을 부분 정렬합니다. K번째 원소보다 작은 모든 원소는 그 앞에, 큰 모든 원소는 그 뒤에 위치합니다.
- 복잡도: O(N)
- 구현 스케치(C++):
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

      // k-1 인덱스에 k번째 작은 원소가 오도록 부분 정렬
      std::nth_element(a.begin(), a.begin() + k - 1, a.end());

      std::cout << a[k - 1] << '\n';
      return 0;
  }
  ```
```