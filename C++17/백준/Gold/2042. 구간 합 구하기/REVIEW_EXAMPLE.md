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
