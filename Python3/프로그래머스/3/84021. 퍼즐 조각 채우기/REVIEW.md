# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./Python3/프로그래머스/3/84021. 퍼즐 조각 채우기/퍼즐 조각 채우기.py`

## 한 줄 결론
- (이 문제는) **BFS와 도형 정규화/해싱** / 복잡도: O(N^2 + H*P) / 루프 내 `list.remove` 호출이 비효율을 유발하는 핵심 포인트입니다.

## 더 빠른/더 안전한 풀이(필수)
- 아이디어: `list` 대신 `collections.Counter`를 써서 구멍과 조각의 개수를 센 뒤 매칭하세요.
- 복잡도: O(N^2)
- 왜 이게 더 좋은지: 중복 조각/구멍 처리가 간결해지고 매칭 시간 복잡도가 O(H*P)에서 O(H+P)로 개선됩니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) 회전/해싱의 매직넘버: 회전식 `(5 - j, i)`와 해싱 `6*i+j`는 조각이 6x6 안에 들어간다는 가정에 기반합니다. 이 가정이 문제 조건에 의해 보장되지만, 변경 시 버그가 되기 쉬운 부분입니다.
- 2) 자료구조/성능 함정: `for` 루프 안에서 `table.remove(hole)`을 쓰는 것은 리스트 전체를 매번 탐색(O(P))하게 만들어, 구멍(H)과 조각(P)이 많을 때 O(H*P) 복잡도를 유발합니다.
- 3) 정규화 로직: 조각의 기준점을 (0,0)으로 옮기는 `min()` 연산이 조각 발견 시마다 반복됩니다. 조각 크기가 작아 문제없지만, 일반적인 상황에서는 비효율을 초래할 수 있습니다.

## 즉시 수정 액션(최대 4개)
- 1. `collections.Counter`를 이용해 구멍과 조각의 개수를 센 후 매칭 로직을 수정하세요.
- 2. `countll` 함수 이름을 `count_set_bits` 와 같이 역할이 명확한 이름으로 변경하세요.
- 3. 회전 로직의 숫자 `5`, 해싱 로직의 `6`은 `MAX_BLOCK_SIZE = 6` 과 같은 상수로 정의하여 가독성을 높이세요.
- 4. `read` 함수명을 `extract_and_normalize_shapes` 등으로 구체화하여 코드의 역할을 명확히 하는 것을 고려해보세요.

```REVIEW_EXAMPLE
# 제목: collections.Counter를 이용한 O(H+P) 매칭
- 적용 조건: 동일한 모양의 조각이나 구멍이 여러 개 존재할 수 있는 모든 경우에 유리합니다.
- 핵심 아이디어: 각 조각과 구멍의 정규화된 해시값을 키로 사용해 개수를 미리 셉니다. 그 후, 해시값을 기준으로 일치하는 개수만큼 곱하여 총 채운 칸 수를 계산합니다.
- 복잡도: O(N^2) (도형 추출) + O(H+P) (매칭)
- 구현 스케치(선택):
```python
from collections import Counter

def solution(game_board, table):
    # game_board의 빈 공간(0)을 1로 바꿔서 table과 동일한 로직 사용
    inverted_board = [[1 - cell for cell in row] for row in game_board]
    
    # Counter를 사용해 각 도형의 해시값과 개수를 저장
    holes = Counter(read(inverted_board))
    pieces = Counter(read(table))
    
    answer = 0
    for hole_hash, hole_count in holes.items():
        # 해당 구멍 모양과 일치하는 조각이 있는지 확인
        if hole_hash in pieces:
            # 채울 수 있는 개수는 (구멍 개수, 조각 개수) 중 작은 값
            match_count = min(hole_count, pieces[hole_hash])
            # (채운 조각 수) * (조각 당 칸 수)
            answer += match_count * count_set_bits(hole_hash)
            
    return answer

# read, count_set_bits(舊 countll) 함수는 기존 코드 활용
```