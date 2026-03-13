# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Gold/15683. 감시/감시.cc`

## 한 줄 결론
- (이 문제는) **백트래킹 완전탐색** / 복잡도: O(4^K * N * M) / 재귀 호출마다 맵 전체를 복사하는 실수

## 더 빠른/더 안전한 풀이(필수)
- 아이디어: `memcpy`로 맵을 복사하는 대신, 재귀 호출 전에 감시 영역을 표시하고, 호출 후에 다시 원래대로 되돌리는 방식(상태 변경 및 복구)을 사용합니다.
- 복잡도: O(4^K * N * M) (복잡도는 같지만 상수 시간이 크게 개선됨)
- 왜 이게 더 좋은지: 불필요한 메모리 복사를 제거하여 훨씬 빠르고 효율적입니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) 초기값/시작점/종료조건: `minCells`를 64로 초기화하고, 빈 칸(0) 개수를 세어 시작하는 방식은 안전합니다.
- 2) 인덱스/경계/오버플로: `watched` 함수 내에서 벽(6)을 만나거나 맵의 끝에 도달했을 때 탐색을 멈추는 경계 처리는 정확합니다.
- 3) **자료구조/성능 함정**: `dfs` 함수에서 매번 `memcpy`로 맵 전체를 복사하고 `vector`를 값으로 전달하여, 모든 재귀 호출마다 큰 오버헤드가 발생합니다.

## 즉시 수정 액션(최대 4개)
- 1. `dfs`에서 `memcpy`를 제거하고, 상태 변경 -> 재귀 호출 -> 상태 원상 복구 패턴으로 바꾸세요.
- 2. `dfs`의 `vector<cctvTy> cctvs` 매개변수를 값 전달 대신 `const vector<cctvTy>&`와 현재 처리할 CCTV 인덱스를 넘기는 방식으로 변경하여 불필요한 벡터 복사를 막으세요. (예: `void dfs(int cctv_idx, ...)` )
- 3. `watched` 함수에서 감시 영역을 표시할 때, 원상 복구를 위해 어떤 좌표가 바뀌었는지 기록하거나, 동일한 로직으로 되돌리는 함수를 구현해야 합니다.
- 4. (가독성) `typedef pair<loc, short> cctvTy;`보다 `struct CCTV { loc p; short type; };`가 가독성이 좋습니다.

```REVIEW_EXAMPLE
# 제목: 더 효율적인 백트래킹 풀이 스케치
- 적용 조건: 현재 풀이의 `memcpy`와 벡터 복사 오버헤드를 제거하고 싶을 때.
- 핵심 아이디어: `dfs` 함수는 처리할 CCTV의 인덱스를 인자로 받습니다. 재귀 호출 전 맵을 직접 변경하고, 재귀 호출이 끝나면 변경 사항을 원상 복구하여 다음 경우의 수를 탐색합니다.
- 복잡도: O(4^K * N * M)

- 구현 스케치(C++):
```cpp
// 맵 상태를 변경하고 복구하는 함수
void update_board(short board[8][8], const cctvTy& cctv, short dir, short marker) {
    // cctv의 위치와 dir을 기반으로 marker(7 또는 0)로 맵을 채우는 로직
    // ... 기존 watched 함수 로직과 유사하게 구현 ...
}

// cctv_idx: 현재 처리할 cctv의 인덱스
void dfs(int cctv_idx, short board[8][8], const vector<cctvTy>& cctvs) {
    if (cctv_idx == cctvs.size()) {
        // 모든 CCTV 방향 결정 완료. 사각지대 계산 및 minCells 갱신
        return;
    }

    cctvTy cctv = cctvs[cctv_idx];
    for (short dir : cctvDir[cctv.second]) {
        short temp_board[8][8];
        memcpy(temp_board, board, sizeof(temp_board));
        
        // 상태 변경
        update_board(temp_board, cctv, dir, 7);
        // 재귀 호출
        dfs(cctv_idx + 1, temp_board, cctvs);
        // 상태 복구는 필요 없음 (다음 루프에서 원본 board를 복사하므로)
        // 만약 복사 대신 board를 직접 수정한다면 복구 로직이 필수
    }
}
```
*수정: 위 스케치는 원본 코드의 `memcpy`를 유지한 채 인덱스 기반 탐색만 적용한 버전입니다. 진정한 최적화는 `memcpy`까지 제거하고 상태 변경/복구를 하는 것입니다.*