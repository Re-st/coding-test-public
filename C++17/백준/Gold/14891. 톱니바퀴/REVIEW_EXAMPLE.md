# 제목: 더 안전하고 명확한 2-Phase 풀이
- 적용 조건: 현재 문제처럼 상태 변화의 전파가 '동시에' 일어나야 할 때 항상 유리합니다.
- 핵심 아이디어: 회전 명령이 들어오면, (1) 어떤 기어들이 어떤 방향으로 돌지 먼저 전부 계산해서 배열에 저장하고, (2) 계산이 모두 끝난 뒤 그 배열을 보고 한꺼번에 실제 회전을 적용합니다.
- 복잡도: O(K)
- 구현 스케치(C++):
void solve_one_turn() {
    int n, d;
    cin >> n >> d;
    --n; // 0-indexed

    // 1. 회전 방향 결정 단계
    int dirs[4] = {0};
    dirs[n] = d;

    // 왼쪽으로 전파
    for (int i = n; i > 0; --i) {
        if (t[i][6] != t[i - 1][2]) {
            dirs[i - 1] = -dirs[i];
        } else {
            break; // 전파 중단
        }
    }
    // 오른쪽으로 전파
    for (int i = n; i < 3; ++i) {
        if (t[i][2] != t[i + 1][6]) {
            dirs[i + 1] = -dirs[i];
        } else {
            break; // 전파 중단
        }
    }

    // 2. 실제 회전 적용 단계
    for (int i = 0; i < 4; ++i) {
        if (dirs[i] != 0) {
            rotate_gear(i, dirs[i]); // 기존 회전 로직 함수화
        }
    }
}