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