# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Gold/15683. 감시/감시.cc`

## 한 줄 결론
- (이 문제는) **백트래킹** / 복잡도: O(4^K * N*M) / 재귀 호출 시 상태 복원을 위해 2D 배열 전체를 복사하는 방식이 핵심.

## 더 빠른/더 안전한 풀이(필수)
- 현 접근이 거의 최선. CCTV 개수(K≤8)가 적어, 모든 경우의 수를 탐색하는 백트래킹이 정해입니다. 상태 복원을 위해 `memcpy`를 사용했는데, 보드 크기(≤8x8)가 작아 성능 문제는 없습니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) **재귀 상태 관리**: `dfs` 함수에 `vector<cctvTy> cctvs`를 값으로 전달해 매 호출마다 불필요한 복사가 발생합니다. `const&`와 인덱스 `k`를 쓰는 게 더 효율적입니다.
- 2) **가독성 및 중복**: `watched` 함수 내 4개 방향(L, U, R, D) 처리 로직이 거의 동일하게 반복됩니다. `dx`, `dy` 배열로 리팩토링하면 코드가 간결해지고 버그 가능성도 줄어듭니다.
- 3) **데이터 표현**: 방향을 비트마스크로 표현한 것은 흥미롭지만, `dx/dy` 배열과 직접 연동되는 방향 인덱스(0~3)로 바꾸면 `watched` 함수 구현이 더 직관적이게 됩니다.

## 즉시 수정 액션(최대 4개)
- `dfs` 시그니처를 `void dfs(int k, ...)`로 변경하고, CCTV 목록은 `const vector<...>&`로 한 번만 전달하여 `vector` 복사를 방지하세요.
- `watched` 함수 로직을 `dx[]={-1,0,1,0}, dy[]={0,1,0,-1}` 같은 방향 배열과 루프를 사용하도록 단일화하여 중복을 제거하세요.
- `cctvDir` 자료구조를 비트마스크 대신 방향 인덱스의 `vector<vector<int>>`로 변경하여 `watched` 함수와 연계를 단순화하세요.
- `cctvs.pop_back()` 대신 인덱스 `k`를 사용(`cctvs[k]`)하여 더 직관적인 순서로 탐색하는 것을 권장합니다.

```REVIEW_EXAMPLE
# 제목: 재귀 구조 개선 및 코드 단순화
- 적용 조건: 현재 풀이의 백트래킹 구조를 유지하면서 가독성과 효율성을 개선하고 싶을 때.
- 핵심 아이디어:
  - 재귀 함수에서 vector를 복사하는 대신 인덱스(k)를 넘겨 다음 CCTV를 처리.
  - 4방향 탐색 로직을 dx/dy 배열로 통일하여 코드 중복을 제거.
- 복잡도: O(4^K * N*M) (동일)
- 구현 스케치(C++):
  // 방향: 0:상, 1:우, 2:하, 3:좌
  int dx[] = {-1, 0, 1, 0};
  int dy[] = {0, 1, 0, -1};

  // CCTV 종류별 회전 시 감시할 방향들 (인덱스 기준)
  vector<vector<int>> cctv_dirs[6] = {
      {},
      {{0}, {1}, {2}, {3}},
      {{0, 2}, {1, 3}},
      {{0, 1}, {1, 2}, {2, 3}, {3, 0}},
      {{0, 1, 3}, {0, 1, 2}, {1, 2, 3}, {2, 3, 0}},
      {{0, 1, 2, 3}}
  };

  void solve(int k, short board[8][8], const vector<cctvTy>& cctvs) {
      if (k == cctvs.size()) { /* 사각지대 계산 후 min_val 갱신 */ return; }

      short type = cctvs[k].second;
      int r = cctvs[k].first.first, c = cctvs[k].first.second;

      for (const auto& dirs_to_watch : cctv_dirs[type]) {
          short temp_board[8][8];
          memcpy(temp_board, board, sizeof(temp_board));
          for (int dir : dirs_to_watch) {
              int nr = r, nc = c;
              while (true) {
                  nr += dx[dir]; nc += dy[dir];
                  if (nr<0 || nr>=n || nc<0 || nc>=m || temp_board[nr][nc]==6) break;
                  if (temp_board[nr][nc] == 0) temp_board[nr][nc] = 7;
              }
          }
          solve(k + 1, temp_board, cctvs);
      }
  }
```