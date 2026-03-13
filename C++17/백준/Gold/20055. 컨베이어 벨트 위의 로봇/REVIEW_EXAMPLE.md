# 제목: `deque<bool>`을 이용한 더 안전한 풀이 스케치
- 적용 조건: 현재 풀이의 로봇 위치 관리 로직이 복잡하여 실수가 발생하기 쉬울 때.
- 핵심 아이디어: 로봇의 존재 여부를 `bool` 타입 `deque`로 만들어 컨베이어 벨트와 동기화시켜 회전시킵니다. 이를 통해 로봇의 위치를 직관적으로 관리하고 충돌을 명확하게 확인할 수 있습니다.
- 복잡도: O(단계수 × N)
- 구현 스케치(의사코드):
deque<int> durability(2 * n);
deque<bool> on_robot(2 * n, false);
// ... 입력 처리 ...

while (zero_count < k) {
    step++;
    // 1. 벨트와 로봇 함께 회전
    durability.push_front(durability.back()); durability.pop_back();
    on_robot.push_front(on_robot.back()); on_robot.pop_back();
    on_robot[n - 1] = false; // 내리는 위치 로봇 하차

    // 2. 로봇 이동 (가장 먼저 올린 로봇부터)
    for (int i = n - 2; i >= 0; --i) {
        if (on_robot[i] && !on_robot[i+1] && durability[i+1] > 0) {
            on_robot[i] = false;
            on_robot[i+1] = true;
            if (--durability[i+1] == 0) zero_count++;
        }
    }
    on_robot[n - 1] = false; // 이동 후 내리는 위치 로봇 하차

    // 3. 로봇 올리기
    if (durability[0] > 0) {
        on_robot[0] = true;
        if (--durability[0] == 0) zero_count++;
    }
}