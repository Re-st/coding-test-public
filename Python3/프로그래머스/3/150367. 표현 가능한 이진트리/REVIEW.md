# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./Python3/프로그래머스/3/150367. 표현 가능한 이진트리/표현 가능한 이진트리.py`

## 한 줄 결론
- **분할 정복** / 복잡도: O(N * L log L) / 재귀 호출 시 리스트 슬라이싱으로 인한 성능 저하가 가장 큰 약점입니다.

## 더 빠른/더 안전한 풀이(필수)
- 아이디어: 재귀 함수에 리스트 조각(슬라이스) 대신 **시작/끝 인덱스**를 넘겨서 불필요한 메모리 복사를 제거합니다.
- 복잡도: O(N * L) (N: `numbers` 길이, L: 이진트리 노드 수)
- 왜 이게 더 좋은지: 메모리 복사와 `list.count()` 연산이 없어 훨씬 빠르고, 코드가 더 명료해집니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) 초기값/시작점/종료조건: `binary()` 함수에서 포화 이진트리의 길이를 찾는 로직이 복잡합니다. `num.bit_length()`를 이용하면 더 직관적으로 길이를 계산할 수 있습니다.
- 2) 인덱스/경계/오버플로/방문처리: `able()` 함수에서 부모 노드가 0일 때 자식 노드가 1인지만 확인하면 됩니다. 현재 `numlist.count(1)`은 모든 자손을 확인하여 비효율적입니다.
- 3) 자료구조/성능 함정: 재귀 호출마다 `numlist[:middle]`처럼 리스트 슬라이싱을 사용하면, 매번 새로운 리스트가 생성되어 성능 저하의 주된 원인이 됩니다.

## 즉시 수정 액션(최대 4개)
- `able` 함수가 리스트 슬라이스 대신 `(binary_list, start, end)` 인덱스를 받도록 리팩토링하세요.
- `binary` 함수에서 `num.bit_length()`를 사용해 필요한 포화 이진트리 길이를 구하도록 수정하세요.
- `able` 함수의 `numlist.count(1)` 호출을 제거하고, 부모가 0일 때 자식 루트가 1인지 확인하는 로직으로 변경하세요.
- `binary` 함수에서 비트 연산으로 이진수 리스트를 만드는 부분은 가독성을 위해 `bin(num)[2:].zfill(length)` 사용을 고려하세요.

```REVIEW_EXAMPLE
# 제목: 인덱스 기반 분할 정복 풀이
- 적용 조건: 현재 풀이의 성능을 개선하고 싶을 때 항상 유리합니다.
- 핵심 아이디어: 전체 이진수 문자열은 한 번만 만들고, 재귀 함수는 `(start, end)` 인덱스만으로 서브트리를 탐색합니다. 부모가 '0'인데 자식 루트가 '1'이면 즉시 실패 처리합니다.
- 복잡도: O(N * L)
- 구현 스케치(선택):
```python
def solution(numbers):
    answer = []
    for num in numbers:
        b_num = bin(num)[2:]
        L = len(b_num)
        k = 1
        while 2**k - 1 < L:
            k += 1
        
        full_b_len = 2**k - 1
        b_num = b_num.zfill(full_b_len)
        
        answer.append(1 if check(b_num, 0, full_b_len - 1) else 0)
    return answer

def check(b_num, start, end):
    if start == end: # 리프 노드는 항상 유효
        return True
    
    mid = (start + end) // 2
    
    # 왼쪽, 오른쪽 서브트리가 유효한지 먼저 확인 (후위 순회)
    left_valid = check(b_num, start, mid - 1)
    right_valid = check(b_num, mid + 1, end)
    
    if not left_valid or not right_valid:
        return False
    
    # 부모가 0(더미)이면 자식도 0이어야 함
    if b_num[mid] == '0':
        left_child_root = b_num[(start + mid - 1) // 2]
        right_child_root = b_num[(mid + 1 + end) // 2]
        if left_child_root == '1' or right_child_root == '1':
            return False
            
    return True
```
```