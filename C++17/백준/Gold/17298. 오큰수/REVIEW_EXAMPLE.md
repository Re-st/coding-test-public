# 제목: 구현 스타일 대안 (인덱스 스택)
- 적용 조건: 코드를 더 간결하게 만들고 싶을 때. 메모리 사용량이 미세하게 줄어듭니다.
- 핵심 아이디어: 입력 배열을 먼저 모두 저장합니다. 스택에는 값 대신 인덱스만 저장하고, 필요할 때마다 `A[index]`로 값을 조회합니다.
- 복잡도: O(N)
- 구현 스케치(C++):
  vector<int> A(n);
  for (int i = 0; i < n; i++) cin >> A[i];
  
  stack<int> s;
  vector<int> ans(n, -1);

  for (int i = 0; i < n; i++) {
      while (!s.empty() && A[s.top()] < A[i]) {
          ans[s.top()] = A[i];
          s.pop();
      }
      s.push(i);
  }