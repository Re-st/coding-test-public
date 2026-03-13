# 제목: 재귀를 이용한 백트래킹 풀이 스케치
- 적용 조건: 현재처럼 추가할 개수(0~3)가 정해져 있고, 모든 조합을 탐색해야 할 때.
- 핵심 아이디어: 추가할 사다리 개수(target)를 0, 1, 2, 3으로 늘려가며, 재귀 함수로 target개의 사다리를 놓는 모든 유효한 조합을 탐색. 성공하는 즉시 종료.
- 복잡도: O( ( (N-1)H C 3 ) * N*H )
- 구현 스케치(선택):
bool found = false;

// count: 현재 추가한 사다리 수, target: 목표 개수, r_start, c_start: 탐색 시작 위치
void solve(int count, int target, int r_start, int c_start) {
    if (count == target) {
        if (all_identical()) found = true;
        return;
    }
    if (found) return;

    for (int r = r_start; r <= h; ++r) {
        for (int c = (r == r_start ? c_start : 1); c < n; ++c) {
            if (lad[r][c] || lad[r][c-1] || lad[r][c+1]) continue;
            
            lad[r][c] = true;
            solve(count + 1, target, r, c + 2); // 연속 방지를 위해 c+2부터
            lad[r][c] = false;

            if (found) return;
        }
    }
}
// main()에서 target=0..3 루프, solve(0, target, 1, 1) 호출, found면 break 후 target 출력