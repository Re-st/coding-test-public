# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./Python3/프로그래머스/2/42839. 소수 찾기/소수 찾기.py`

## 한 줄 결론
- **[완전탐색 + 소수 판별]** / 복잡도: O(L! * K) (L:자릿수, K:소수판별) / 소수 판별 로직이 비효율적이고 복잡합니다.

## 더 빠른/더 안전한 풀이(필수)
- **아이디어**: 만들 수 있는 가장 큰 수(최대 9,876,543)까지 '에라토스테네스의 체'를 미리 만들고, 모든 순열에 대해 O(1)로 소수 여부를 확인합니다.
- **복잡도**: O(MAX_N * log(log(MAX_N))) (MAX_N: 최대 약 10^7)
- **왜 이게 더 좋은지**: 소수 판별을 매번 반복하지 않고, 한 번의 전처리와 O(1) 조회로 처리하여 훨씬 빠르고 코드가 간결해집니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
1. **자료구조/성능 함정**: `primeInfo` 생성 로직은 표준 '에라토스테네스의 체'가 아니며, 각 숫자에 대해 trial-division을 반복하는 비효율적인 O(N√N) 방식입니다.
2. **인덱스/경계/오버플로**: `isPrime` 함수에서 큰 수 판별 시, `num`의 제곱근까지만 소수로 나누면 충분한데 불필요하게 `primes` 리스트 전체(5000까지)를 순회하여 비효율적입니다.
3. **초기값/시작점/종료조건**: 생성된 숫자에 0 또는 1이 있을 수 있습니다. 현재 코드는 `primeInfo` 배열 덕에 올바르게 처리되지만, `isPrime` 함수 내에 `if num < 2: return False` 처럼 명시적으로 방어하는 것이 안전합니다.

## 즉시 수정 액션(최대 4개)
- 비효율적인 소수 목록 생성 로직을 표준 '에라토스테네스의 체' 알고리즘으로 교체하여 전처리 성능을 개선하세요.
- `isPrime` 함수를 제거하고, 에라토스테네스의 체(boolean 배열)를 이용한 O(1) 조회로 바꾸세요.
- 상수명 `MAX_SQRT`는 오해의 소지가 있습니다. `PRIME_CACHE_LIMIT` 등 역할이 명확한 이름으로 변경하는 것이 좋습니다.
- 불필요한 `print` 문을 제거하여 실행 시간을 줄이세요.

```REVIEW_EXAMPLE
# 제목: 에라토스테네스의 체를 활용한 빠른 풀이
- 적용 조건: 여러 수에 대한 소수 판별이 필요하고, 수의 최댓값이 메모리 허용 범위 내일 때(이 문제에 최적)
- 핵심 아이디어: 순열로 만들 수 있는 수의 최댓값까지 소수 여부를 미리 계산해 둡니다. 이후 각 숫자에 대해 O(1)로 소수 여부를 조회합니다.
- 복잡도: O(M * log(log(M)) + P) (M: 최대 가능 숫자, P: 순열 개수)
- 구현 스케치:
```python
from itertools import permutations

def solution_alternative(numbers):
    # 1. 만들 수 있는 모든 숫자 조합 생성
    candidates = set()
    for i in range(1, len(numbers) + 1):
        for p in permutations(list(numbers), i):
            candidates.add(int("".join(p)))

    # 2. 에라토스테네스의 체로 최대값까지 소수 판별 배열 생성
    if not candidates: return 0
    max_val = max(candidates)
    is_prime = [True] * (max_val + 1)
    if max_val >= 0: is_prime[0] = False
    if max_val >= 1: is_prime[1] = False
    
    for i in range(2, int(max_val**0.5) + 1):
        if is_prime[i]:
            for j in range(i * i, max_val + 1, i):
                is_prime[j] = False
    
    # 3. 생성된 숫자 중 소수 개수 카운트
    return sum(1 for num in candidates if is_prime[num])

```
```