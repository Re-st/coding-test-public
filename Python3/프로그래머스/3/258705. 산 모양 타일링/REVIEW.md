# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./Python3/프로그래머스/3/258705. 산 모양 타일링/산 모양 타일링.py`

## 한 줄 결론
- **DP(동적 계획법)** / 복잡도: O(N) / 최종 결과값 계산 시 마지막 삼각형 처리를 놓치는 실수

## 더 빠른/더 안전한 풀이(필수)
- 아이디어: DP 상태 전이가 직전(`i-1`) 상태에만 의존하므로, O(N) 크기 배열 대신 상수 공간(변수 2개)만으로 최적화할 수 있습니다.
- 복잡도: O(N) 시간, O(1) 공간
- 왜 이게 더 좋은지: 메모리 사용량을 극적으로 줄여(N=10만일 때 약 1.6MB -> 1KB 미만) 더 효율적이고, 코드도 간결해집니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) 초기값/시작점/종료조건: `i=1`의 DP 값을 하드코딩하고 루프를 `i=2`부터 시작했는데, 이는 `i=0`에 대한 항등원(시작 상태)을 설정하고 `i=1`부터 루프를 도는 방식보다 초기화 실수가 발생하기 쉽습니다.
- 2) 인덱스/경계/오버플로/방문처리: 최종 결과가 `wom[n]`이 아니라 `(wom[n] + withm[n])`인 이유를 놓치기 쉽습니다. `n`번째 블록에서 마름모가 튀어나오는 경우(`withm[n]`)가 사다리꼴의 마지막 남은 삼각형 하나를 채우면서 유효한 타일링이 되기 때문입니다.
- 3) 자료구조/성능 함정: N이 10만이므로 O(N)보다 느린 알고리즘은 시간 초과입니다. 현재 DP 접근은 시간 복잡도 면에서 거의 최선입니다.

## 즉시 수정 액션(최대 4개)
- 1. **(성능)** O(1) 공간 복잡도 최적화를 적용하세요. (DP 배열 대신 `prev_wom`, `prev_withm` 같은 변수 사용)
- 2. **(가독성)** `wom`, `withm` 변수명을 `dp_complete`, `dp_protruding`처럼 역할이 드러나는 이름으로 변경을 고려하세요.
- 3. **(간결성)** `if/else`로 분기된 `wom[i]` 계산 로직을 아래와 같이 하나로 통합할 수 있습니다.
   ```python
   wom[i] = (wom[i-1] * (2 + tops[i-1]) + withm[i-1] * (1 + tops[i-1])) % MOD
   ```

```REVIEW_EXAMPLE
# 제목: 공간 복잡도 O(1) 최적화 풀이
- 적용 조건: DP 상태가 바로 이전 상태에만 의존하는 모든 경우.
- 핵심 아이디어: DP 테이블 전체를 저장하는 대신, (이전 상태, 현재 상태)를 저장하는 변수 쌍만으로 점화식을 계속 갱신합니다.
- 복잡도: O(N) 시간, O(1) 공간
- 구현 스케치:
```python
def solution(n, tops):
    MOD = 10007
    # dp_complete: i번째 열까지 완전히 채운 경우의 수
    # dp_protruding: i번째 열에서 (i+1)로 마름모가 돌출된 경우의 수
    dp_complete, dp_protruding = 1, 0  # i=0 (시작) 상태

    for top in tops:
        prev_complete, prev_protruding = dp_complete, dp_protruding

        # 점화식에 따라 현재 상태 업데이트
        dp_protruding = (prev_complete + prev_protruding) % MOD
        dp_complete = (prev_complete * (2 + top) + prev_protruding * (1 + top)) % MOD
    
    # 마지막 삼각형 처리까지 고려한 최종 결과
    return (dp_complete + dp_protruding) % MOD
```
```