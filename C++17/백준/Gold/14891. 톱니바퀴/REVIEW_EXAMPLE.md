# 제목: 비재귀(iterative) 풀이 스케치
- 적용 조건: 재귀가 헷갈리거나, 상태 변경과 로직 결정을 명확히 분리하고 싶을 때 유리합니다.
- 핵심 아이디어: 1) 각 톱니의 회전 방향을 배열에 먼저 모두 계산. 2) 계산된 방향에 따라 모든 톱니를 한 번에 회전시킵니다.
- 복잡도: O(K) (기존과 동일)
- 구현 스케치(C++):
void apply_rotation_command(int n, int d) {
    --n; // 0-indexed로 변환

    int dirs[4] = {0};
    dirs[n] = d;

    // 왼쪽으로 전파될 방향 결정
    for (int i = n - 1; i >= 0; --i) {
        if (t[i+1][6] != t[i][2]) dirs[i] = -dirs[i+1];
        else break;
    }

    // 오른쪽으로 전파될 방향 결정
    for (int i = n + 1; i < 4; ++i) {
        if (t[i-1][2] != t[i][6]) dirs[i] = -dirs[i-1];
        else break;
    }
    
    // 결정된 방향으로 실제 회전 적용
    for(int i = 0; i < 4; ++i) {
        if(dirs[i] != 0) rotate_gear(i, dirs[i]); // rotate_gear는 기존 회전 로직
    }
}