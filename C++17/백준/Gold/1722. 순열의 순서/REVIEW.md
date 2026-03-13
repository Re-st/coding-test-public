# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Gold/1722. 순열의 순서/순열의 순서.cc`

## 한 줄 결론
- **[조합론/팩토리얼]** / 복잡도: O(N^2) / 소문제 2의 순서 계산 로직이 복잡하여 실수 유발 가능성이 높음.

## 더 빠른/더 안전한 풀이(필수)
- 아이디어: Fenwick Tree(BIT)로 'k번째 미사용 숫자 탐색', '특정 수보다 작은 미사용 숫자 개수 세기'를 O(logN)에 처리.
- 복잡도: O(N log N)
- 왜 이게 더 좋은지: 기존 O(N^2)보다 빠르며, 두 소문제의 핵심 로직을 일관되고 명료하게 구현할 수 있어 버그 가능성이 줄어듭니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) 자료구조/성능 함정: 소문제 2의 순서 계산 로직 `ord = (ord + curr) * i`는 팩토리얼 기수법(Factoradic) 계산의 한 형태로, 정답은 나오지만 `ord += count * factorial[i]` 방식보다 직관적이지 않아 실수하기 쉽습니다.
- 2) 구현 실수: 소문제 1에서 k번째 미사용 숫자를 찾는 `while(curr >= 0)` 루프나, 소문제 2에서 `curr--`를 이용해 개수를 세는 방식은 로직이 복잡합니다. 단순 순회로 같은 기능을 명확히 구현하는 것이 안전합니다.
- 3) 코드 구조: `fact_array`가 `if (op == 1)` 블록 내에 선언되어 재사용성이 떨어집니다. `main` 함수 시작점에 선언하면 두 소문제에서 일관되게 활용할 수 있습니다.

## 즉시 수정 액션(최대 4개)
- `op == 2`에서 사용 가능한 더 작은 수의 개수를 세는 로직을 아래처럼 명시적으로 변경하세요.
  ```cpp
  int smaller_available = 0;
  for (int j = 1; j < curr; ++j) {
      if (!visited[j]) smaller_available++;
  }
  // 이후 계산에 smaller_available 사용
  ```
- 팩토리얼 배열(`fact_array`)을 `if-else`문 바깥으로 옮겨 두 소문제에서 모두 접근 가능하게 하세요.
- `_trash`와 같이 의도를 알 수 없는 변수명 대신 `last_num` 등 의미 있는 이름을 사용하세요.

```REVIEW_EXAMPLE
# 제목: Fenwick Tree(BIT)를 이용한 O(N log N) 풀이
- 적용 조건: N이 더 커져서(e.g., N=10^5) O(N^2)이 시간 초과될 때 필수적이며, N=20에서도 더 깔끔한 구현이 가능합니다.
- 핵심 아이디어: BIT에 1~N까지 숫자의 사용 가능 여부(1: 미사용, 0: 사용)를 저장합니다.
  - 소문제 1 (k번째 순열): k번째 미사용 숫자를 찾을 때, BIT 위에서 이분 탐색을 하여 O(logN)만에 찾습니다.
  - 소문제 2 (순서 찾기): 특정 숫자 `p`보다 작은 미사용 숫자 개수는 BIT의 구간 합 `query(p-1)`으로 O(logN)만에 구합니다.
- 복잡도: O(N log N)
- 구현 스케치(의사코드):
  ```cpp
  // 초기화
  FenwickTree bit(N);
  for(int i=1; i<=N; ++i) bit.update(i, 1); // 모두 사용 가능

  // 소문제 1: k번째 순열 찾기
  for i from n-1 down to 0:
      k_th = bit.find_kth(ord / fact[i] + 1); // BIT에서 k번째 1 찾기
      print(k_th);
      bit.update(k_th, -1); // 사용 처리
      ord %= fact[i];

  // 소문제 2: 순서 찾기
  for i from n-1 down to 0:
      cin >> p;
      smaller_count = bit.query(p - 1); // p보다 작은 미사용 숫자 수
      ord += smaller_count * fact[i];
      bit.update(p, -1); // 사용 처리
  ```
```