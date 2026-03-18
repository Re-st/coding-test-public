# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./Python3/프로그래머스/3/258707. n ＋ 1 카드게임/n ＋ 1 카드게임.py`

## 한 줄 결론
- (이 문제는) **그리디** / 복잡도: O(N^2) / 3단계 탐색 로직의 비효율적 구현

## 더 빠른/더 안전한 풀이(필수)
- 아이디어: `hand`, `maybuy` 카드 목록을 boolean 배열 대신 `set`으로 관리하여 탐색 효율 개선.
- 복잡도: 최악 O(N^2), 평균 O(N * |S|) (S: 카드 셋 크기)
- 왜 이게 더 좋은지: 전체 카드(N)가 아닌 실제 소유한 카드만 탐색하므로 훨씬 빠르고 Pythonic함.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) 초기값/시작점/종료조건: `while True` 루프의 종료 조건(카드 소진)과 라운드 카운팅(`answer`) 로직이 복잡하여 실수 유발 가능.
- 2) 인덱스/경계/오버플로/방문처리: 카드 값을 0-based(`v-1`)로 변환하면서 목표 합이 `n-1`이 되는 등, 인덱스 계산이 직관적이지 않아 오류 발생 가능.
- 3) 자료구조/성능 함정: `hand`, `maybuy` 쌍을 찾기 위해 `for i in range(n)`과 같이 불필요하게 전체 카드 범위를 순회하여 비효율적.

## 즉시 수정 액션(최대 4개)
- 1. 제출 코드에 불필요한 `print`문을 모두 제거하세요.
- 2. `togo` 변수명을 `pair_found = False` 와 같이 명확한 boolean 변수로 변경하여 가독성을 개선하세요.
- 3. 카드 번호를 그대로 인덱스로 쓰도록 배열 크기를 `n+1`로 선언하면, `v-1` 변환 없이 `n+1-i` 등 직관적인 코딩이 가능합니다.
- 4. `while True:` 대신 `for round in range(1, n//3 + 2):` 와 같이 라운드 범위를 명시하여 루프 구조를 단순화하세요.

```REVIEW_EXAMPLE
# 제목: 더 빠르고 Pythonic한 풀이 (set 활용)
- 적용 조건: 현재 풀이보다 평균 성능이 우수하고 코드가 간결해집니다.
- 핵심 아이디어: `hand`와 `maybuy` 카드 목록을 `set`으로 관리합니다. 매 라운드 비용 순서(0→1→2 코인)대로 `set`을 순회하며 `target - card` 존재 여부를 O(1)에 확인합니다.
- 복잡도: 최악 O(N^2), 평균적으로 훨씬 빠름
- 구현 스케치(Python):
```python
def solution_revised(coin, cards):
    n = len(cards)
    target = n + 1
    hand = set(cards[:n//3])
    maybuy = set()
    card_idx = n//3

    for r in range(1, n//3 + 2):
        if card_idx >= n: # 더 뽑을 카드가 없으면 최대 라운드 도달
            return r

        maybuy.add(cards[card_idx])
        maybuy.add(cards[card_idx+1])
        card_idx += 2

        found = False
        # 1. 0 코인: hand 카드 2장 사용
        for card in hand:
            if target - card in hand:
                hand.remove(card); hand.remove(target-card); found = True; break
        if found: continue

        # 2. 1 코인: hand 1장, maybuy 1장 사용
        if coin >= 1:
            for card in hand:
                if target - card in maybuy:
                    hand.remove(card); maybuy.remove(target-card); coin -= 1; found = True; break
        if found: continue
        
        # 3. 2 코인: maybuy 2장 사용
        if coin >= 2:
            for card in maybuy:
                if target - card in maybuy:
                    maybuy.remove(card); maybuy.remove(target-card); coin -= 2; found = True; break
        if found: continue
        
        return r # 페어를 못 만들면 현재 라운드에서 종료
    return 1 # 1라운드도 못 깰 경우
```
```