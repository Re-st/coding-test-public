# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Silver/14888. 연산자 끼워넣기/연산자 끼워넣기.cc`

## 한 줄 결론
- (이 문제는) **백트래킹** / 복잡도: O(N!) / 제일 위험한 실수: 재귀 호출 후 연산자 개수 복원 누락

## 더 빠른/더 안전한 풀이(필수)
- 현 접근이 거의 최선입니다. N이 11로 매우 작아 모든 경우의 수를 탐색하는 백트래킹이 정해(intended solution)입니다.
- 단, 전역 변수 대신 함수 파라미터로 상태를 넘기면 더 안전하고 명확한 코드가 됩니다. (아래 예시 참고)

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) 초기값/시작점/종료조건: `dfs(1, a[0])` 호출은 첫 피연산자와 다음 연산할 숫자 인덱스(1)를 올바르게 설정한 것입니다. 종료 조건 `depth == n`도 정확합니다.
- 2) 재귀/백트래킹: `o1--`로 연산자 개수를 차감 후, 재귀 호출이 끝나면 `o1++`로 복원하는 것이 백트래킹의 핵심입니다. 이 복원 로직을 빠뜨리는 것이 흔한 실수입니다. (현재 코드는 올바름)
- 3) 자료구조/성능 함정: `o1, o2, o3, o4` 같은 전역 변수에 직접 의존하는 함수는 외부 상태 변화에 취약하여, 코드가 복잡해질수록 디버깅을 어렵게 만들 수 있습니다.

## 즉시 수정 액션(최대 4개)
- `dfs` 함수가 전역 변수를 직접 수정하는 대신, `void dfs(int depth, int cur, int plus, ...)` 와 같이 연산자 개수를 파라미터로 전달하도록 리팩토링하는 것을 추천합니다. 이렇게 하면 상태 복원 코드가 불필요해져 실수를 줄일 수 있습니다.

```REVIEW_EXAMPLE
# 제목: 전역 변수 대신 파라미터 전달로 안전성 높이기
- 적용 조건: 함수가 외부 상태에 의존하지 않게 하여 코드의 모듈성과 재사용성을 높이고 싶을 때.
- 핵심 아이디어: `dfs` 함수 시그니처를 `dfs(depth, cur, plus, ...)`와 같이 변경. 재귀 호출 시, 사용한 연산자의 개수를 1 감소시켜 다음 함수에 인자로 전달합니다. 이 방식은 상태 복원(예: `o1++`) 코드가 필요 없어 더 간결하고 안전합니다.
- 복잡도: O(N!) (동일)
- 구현 스케치(C++):
```cpp
// void dfs(int depth, int cur) -> void dfs(int depth, int cur, int plus, int minus, int mul, int div)
void dfs(int depth, int cur, int plus, int minus, int mul, int div) {
    if (depth == n) {
        maxans = max(maxans, cur);
        minans = min(minans, cur);
        return;
    }

    if (plus > 0)
        dfs(depth + 1, cur + a[depth], plus - 1, minus, mul, div);
    if (minus > 0)
        dfs(depth + 1, cur - a[depth], plus, minus - 1, mul, div);
    if (mul > 0)
        dfs(depth + 1, cur * a[depth], plus, minus, mul - 1, div);
    if (div > 0)
        dfs(depth + 1, cur / a[depth], plus, minus, mul, div - 1);
}

// main()에서 최초 호출
// dfs(1, a[0], o1, o2, o3, o4);
```
```