# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Gold/2042. 구간 합 구하기/구간 합 구하기.cc`

## 한 줄 결론
- **세그먼트 트리(Iterative)** / 복잡도: O(N + (M+K)logN) / `Sum` 함수의 비표준적인 재귀 구현

## 더 빠른/더 안전한 풀이(필수)
- 아이디어: **펜윅 트리(BIT)**를 사용합니다.
- 복잡도: O((M+K)logN)
- 왜 이게 더 좋은지: 점 업데이트와 구간 합 문제에 특화되어, 세그먼트 트리보다 구현이 훨씬 짧고 메모리도 적게 사용하며 버그 가능성이 낮습니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) 초기값/시작점/종료조건: 리프 노드 시작 인덱스(`1<<height`)와 1-based 입력(`b, c`)을 변환하는 `b + (1 << height) - 1` 로직은 복잡하여 실수하기 쉽습니다.
- 2) 인덱스/경계/오버플로: `Sum` 함수에서 `start++` 직후 `start > end`가 될 수 있음에도 다음 `if`문을 검사하는 등, 재귀와 증감 연산자가 섞여 경계 조건 해석이 까다롭습니다.
- 3) 자료구조/성능 함정: `Sum` 함수의 재귀 구현은 반복문에 비해 함수 호출 오버헤드가 있고, 코드를 처음 보는 사람이 의도를 파악하기 어렵습니다.

## 즉시 수정 액션(최대 4개)
1. `Sum` 함수를 직관적인 `while` 루프로 변경하여 가독성과 안정성을 높이세요.
   ```cpp
   long long Sum(int start, int end) {
       long long ans = 0;
       while (start <= end) {
           if (start % 2 == 1) ans += vec[start++];
           if (end % 2 == 0) ans += vec[end--];
           start /= 2;
           end /= 2;
       }
       return ans;
   }
   ```
2. 쿼리 타입(a=2)일 때 `long long c`에 인덱스를 받는 것은 혼동을 유발합니다. 별도 변수를 사용하세요.
3. 리프 노드 오프셋 `(1 << height)`을 `LEAF_OFFSET` 같은 상수로 정의하면 인덱스 계산이 명확해집니다.
4. `Switch` 함수의 루프를 `for(idx /= 2; idx > 0; idx /= 2)`와 같이 더 관습적인 형태로 바꾸는 것을 고려하세요.

```REVIEW_EXAMPLE
# 제목: 더 간결하고 빠른 펜윅 트리(BIT) 풀이
- 적용 조건: 점(point) 업데이트와 구간 합 쿼리만 필요할 때 가장 효율적입니다.
- 핵심 아이디어: 각 원소의 값이 자신의 인덱스에서 LSB(Least Significant Bit)를 더한 위치의 노드에 영향을 주는 방식으로 구간 합을 O(logN)에 계산합니다. 업데이트도 O(logN)에 가능합니다.
- 복잡도: O(NlogN) 또는 O(N) 빌드, O((M+K)logN) 쿼리/업데이트
- 구현 스케치(C++):
  ```cpp
  vector<long long> tree;
  int N;

  void update(int idx, long long diff) {
      for (; idx <= N; idx += idx & -idx) {
          tree[idx] += diff;
      }
  }

  long long query(int idx) {
      long long result = 0;
      for (; idx > 0; idx -= idx & -idx) {
          result += tree[idx];
      }
      return result;
  }
  
  // 1. 초기화: 모든 원소에 대해 update(i, arr[i]) 호출
  // 2. 값 변경: update(b, c - arr[b])
  // 3. 구간 합: query(c) - query(b - 1)
  ```
```