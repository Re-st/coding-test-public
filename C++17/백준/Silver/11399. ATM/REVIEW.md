# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Silver/11399. ATM/ATM.cc`

## 한 줄 결론
(이 문제는) **그리디(정렬)** / 복잡도: O(N^2) / 수동 구현한 삽입 정렬의 복잡성과 실수 위험

## 더 빠른/더 안전한 풀이(필수)
- **아이디어**: 모든 값을 입력받은 후, `std::sort`로 한 번에 정렬합니다.
- **복잡도**: O(N log N)
- **왜 이게 더 좋은지**: 코드가 훨씬 간결해지고, 더 빠르며, 직접 구현 시 발생할 수 있는 버그를 원천 차단합니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
1. **로직 복잡성**: 입력을 받으면서 동시에 정렬(삽입 정렬)하는 로직은, 간단히 정렬 라이브러리를 쓰는 것보다 불필요하게 복잡하고 실수할 가능성이 높습니다.
2. **인덱스/경계**: `for (int j = i - 1; j >= nowLoc; j--) pi[j + 1] = pi[j];` 와 같은 수동 메모리 이동은 경계 값 실수 시 `out-of-bounds` 접근 위험이 있습니다.
3. **성능 함정**: 현재 O(N^2) 풀이는 N=1000 제약에서 충분히 빠르지만, N이 더 커지면(예: 10^5) 시간 초과가 발생할 수 있는 잠재적 성능 문제입니다.

## 즉시 수정 액션(최대 4개)
- `#include <algorithm>` 후, 복잡한 정렬 로직을 `sort(pi.begin(), pi.end());` 한 줄로 대체하세요.
- 로직을 분리하세요: (1) 모든 입력을 벡터에 저장 (2) 정렬 (3) 결과 계산.
- 총합 계산 시, 현재 방식(`(n-i) * pi[i]`)도 좋지만 아래와 같이 누적합을 이용하면 더 직관적일 수 있습니다.
  ```cpp
  int total = 0, prefix_sum = 0;
  for(int time : pi) {
      prefix_sum += time;
      total += prefix_sum;
  }
  ```

---
```REVIEW_EXAMPLE
# 제목: std::sort를 활용한 더 간결한 풀이
- 적용 조건: N이 클 때(O(N^2)가 부담될 때) 유리하며, 일반적으로 코드 간결성을 위해 항상 권장됩니다.
- 핵심 아이디어: 모든 인출 시간을 vector에 저장한 뒤, <algorithm> 헤더의 std::sort 함수로 오름차순 정렬하고, 이후 누적 합을 계산합니다.
- 복잡도: O(N log N)
- 구현 스케치(C++):
  ```cpp
  #include <iostream>
  #include <vector>
  #include <algorithm>

  int main() {
      std::ios::sync_with_stdio(false);
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
```