# 제목: 더 안전하고 직관적인 풀이 (로봇 위치 배열 활용)
- 적용 조건: 현재 풀이는 로봇 위치 추적이 복잡하여 버그 위험이 높으므로, 이 대안이 항상 더 유리합니다.
- 핵심 아이디어: `deque`로는 벨트의 내구성만 관리하고, 로봇의 위치는 `bool robot_on[2*N]` 배열로 별도 관리합니다. 이를 통해 로봇의 존재 여부와 이동 가능 여부를 `O(1)`에 명확하게 확인할 수 있습니다.
- 복잡도: O(단계 수 * N)
- 구현 스케치(의사코드):
vector<bool> robot_on(2 * N, false);
while (zero_count < K) {
    step++;

    // 1. 벨트와 로봇 함께 회전
    belt.push_front(belt.back());
    belt.pop_back();
    for (int i = N - 2; i >= 0; --i) {
        robot_on[i + 1] = robot_on[i];
    }
    robot_on[0] = false;
    if (robot_on[N - 1]) robot_on[N - 1] = false; // 회전 후 즉시 하차

    // 2. 로봇 스스로 이동 (가장 먼저 올라간 로봇부터)
    for (int i = N - 2; i >= 0; --i) {
        if (robot_on[i] && !robot_on[i + 1] && belt[i + 1] >= 1) {
            robot_on[i] = false;
            robot_on[i + 1] = true;
            if (--belt[i + 1] == 0) zero_count++;
        }
    }
    if (robot_on[N - 1]) robot_on[N - 1] = false; // 이동 후 즉시 하차

    // 3. 새 로봇 올리기
    if (belt[0] > 0) {
        robot_on[0] = true;
        if (--belt[0] == 0) zero_count++;
    }
}