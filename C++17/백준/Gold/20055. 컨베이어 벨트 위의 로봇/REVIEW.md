# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Gold/20055. 컨베이어 벨트 위의 로봇/컨베이어 벨트 위의 로봇.cc`

## 한 줄 결론
- (이 문제는) **시뮬레이션** / 복잡도: O(단계수 × N) / 로봇의 위치와 순서를 관리하는 로직에 결함이 있습니다.

## 더 빠른/더 안전한 풀이(필수)
- **아이디어**: 로봇의 위치를 `deque<bool> has_robot`으로 관리하고, 내구도 `deque`와 함께 회전시키세요.
- **복잡도**: O(단계수 × N)
- **왜 이게 더 좋은지**: 로봇 위치를 직접 추적해 복잡한 인덱스 계산과 순서 관리 로직을 없애 버그 가능성을 크게 줄입니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) **자료구조 함정**: `deque<short> robot`을 `pop_back()` -> `push_front()` 하며 순회하면 로봇들의 상대적 순서(먼저 올린 순서)가 매 단계마다 뒤섞입니다.
- 2) **로봇 충돌**: 로봇 이동 시 `robot.front() != r + 1` 조건은 바로 직전 로봇만 확인하므로, 이동하려는 칸에 다른 로봇이 있는지 완벽히 확인할 수 없어 로봇이 겹칠 수 있습니다.
- 3) **로직 분리**: 벨트 회전, 로봇 이동, 로봇 하차 로직이 하나의 루프에 섞여 있어 코드를 이해하고 검증하기 어렵습니다. 문제의 단계별로 로직을 명확히 분리하는 것이 안전합니다.

## 즉시 수정 액션(최대 4개)
- 1. 로봇 위치 관리를 `deque<short> robot`에서 `deque<bool> has_robot(2*n, false)`로 변경하세요.
- 2. 벨트 회전 시, 내구도(`a`)와 로봇 위치(`has_robot`) `deque`를 동일하게 회전시키세요.
- 3. 로봇 이동은 `for (int i = n-2; i>=0; --i)` 루프로 N-1번 칸 직전의 로봇부터 처리해야 "가장 먼저 올라간 로봇" 순서가 됩니다.
- 4. 로봇이 내리는 위치(`n-1`)에 도달하면 즉시(`has_robot[n-1]=false`) 내리도록 처리하세요. (벨트 회전 직후, 로봇 이동 로직 직후 총 두 번 필요)

```REVIEW_EXAMPLE
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
```