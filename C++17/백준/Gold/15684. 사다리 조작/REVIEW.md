# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Gold/15684. 사다리 조작/사다리 조작.cc`

## 한 줄 결론
- (이 문제는) **백트래킹 완전탐색** / 복잡도: O((N*H C 3) * N*H) / `all_identical` 함수의 최종 결과 검증 루프 범위 오류

## 더 빠른/더 안전한 풀이(필수)
- 아이디어: 목표 추가 개수(0~3)를 정하고, 재귀 함수(DFS)로 해당 개수의 사다리를 놓는 모든 조합을 백트래킹으로 탐색합니다.
- 복잡도: O( ( (N-1)H C k ) * N*H ) (k=0~3)
- 왜 이게 더 좋은지: 6중 for문보다 코드가 훨씬 간결하고, 조합 생성 로직의 실수를 줄이며, 가지치기 등 추가 최적화가 용이합니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) 종료조건: `all_identical` 함수에서 `for (int j = 1; j < n; j++)`는 마지막 `n`번째 세로선을 확인하지 않아 오답의 원인이 됩니다. `j <= n`까지 확인해야 합니다.
- 2) 조합 생성: 중첩 for문으로 조합 생성 시, `(a2, b2)`는 `(a1, b1)`보다 사전 순으로 뒤에 와야 중복을 피할 수 있습니다. 현재 코드는 `b2`를 항상 1부터 시작하여 비효율적이며 로직이 복잡합니다.
- 3) 성능 함정: `all_identical` 함수는 비용(O(N*H))이 큰 연산입니다. 2개로 답을 찾았다면, 즉시 모든 탐색을 중단해야 최적입니다. 현재 코드는 답을 찾고도 불필요한 탐색을 계속합니다.

## 즉시 수정 액션(최대 4개)
1. `all_identical()` 내 결과 검증 루프를 `for (int j = 1; j <= n; j++)`로 수정하세요.
2. `ans = 2`를 찾은 경우, 즉시 `cout << 2; return 0;`으로 프로그램을 종료하여 불필요한 탐색을 방지하세요.
3. `collide(a, b)` 함수 내의 `lad[a][b]` 확인은 불필요합니다. 해당 함수는 `lad[a][b]`가 `false`인 위치에 놓기 전에 호출되기 때문입니다.
4. (장기적) 6중 for문 구조를 재귀 함수로 리팩토링하여 가독성과 정확성을 높이는 것을 권장합니다.

```REVIEW_EXAMPLE
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
```