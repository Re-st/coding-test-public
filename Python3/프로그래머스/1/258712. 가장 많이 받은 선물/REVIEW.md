# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./Python3/프로그래머스/1/258712. 가장 많이 받은 선물/가장 많이 받은 선물.py`

## 한 줄 결론
- (이 문제는) **구현/시뮬레이션** / 복잡도: O(M\*N + N^2) / `gifts` 루프 내 `friends.index()` 호출이 가장 큰 성능 병목입니다.

## 더 빠른/더 안전한 풀이(필수)
- 아이디어: `friends` 배열을 미리 {이름: 인덱스} `dict`로 만들어 `O(1)` 조회를 사용합니다.
- 복잡도: O(M + N^2)
- 왜 이게 더 좋은지: `friends.index()`의 `O(N)` 비용을 `O(1)`로 줄여, `M`이 클 때 훨씬 빠릅니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) 초기값/시작점/종료조건: 모든 사람의 다음 달 선물 개수(`newGifts`)를 0으로 초기화하고 시작하는 것은 올바른 접근입니다.
- 2) 인덱스/경계/오버플로/방문처리: `range(a)`를 사용해 `(a, b)` 쌍을 중복 없이 한 번만 비교한 것은 효율적이고 정확합니다.
- 3) 자료구조/성능 함정: `gifts` 루프(최대 10,000번) 안에서 `friends.index()`(최대 50번)를 반복 호출해 `O(M*N)` 복잡도를 유발하는 것이 가장 큰 성능 저하 지점입니다.

## 즉시 수정 액션(최대 4개)
- 1. `gifts` 처리 루프 전에 `friend_map = {name: i for i, name in enumerate(friends)}`를 생성하세요.
- 2. `a = friends.index(e[0])`를 `a = friend_map[e[0]]`으로 교체하여 조회 성능을 개선하세요.
- 3. (선택) 변수명 `A`를 `gift_matrix` 등으로 더 명확하게 바꾸면 가독성이 향상됩니다.
- 4. `max(newGifts)`는 제약(`n>=2`) 덕에 안전하지만, 일반적으로는 `max(newGifts) if newGifts else 0`이 안전합니다.

```REVIEW_EXAMPLE
# 제목: O(1) 조회를 이용한 빠른 풀이
- 적용 조건: 친구 이름(문자열)을 인덱스로 변환하는 과정이 반복될 때 유리합니다.
- 핵심 아이디어: 친구 목록을 미리 {이름: 인덱스} 형태의 딕셔너리로 만들어, gifts를 처리할 때 O(N)의 index() 탐색 대신 O(1)의 딕셔너리 조회를 사용합니다.
- 복잡도: O(M + N^2)
- 구현 스케치(선택):
```python
def solution(friends, gifts):
    n = len(friends)
    friend_map = {name: i for i, name in enumerate(friends)}
    
    gift_matrix = [[0] * n for _ in range(n)]
    gift_rate = [0] * n

    for gift in gifts:
        giver, receiver = gift.split()
        g_idx, r_idx = friend_map[giver], friend_map[receiver]
        
        gift_matrix[g_idx][r_idx] += 1
        gift_rate[g_idx] += 1
        gift_rate[r_idx] -= 1
    
    # ... (이후 로직은 기존 코드와 동일)
```
```