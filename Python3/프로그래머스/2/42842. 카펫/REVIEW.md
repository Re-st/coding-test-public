# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./Python3/프로그래머스/2/42842. 카펫/카펫.py`

## 한 줄 결론
- (이 문제는) **[수학 기반 완전탐색]** / 복잡도: O(brown) / `O(sqrt(yellow))` 풀이가 가능한데 놓친 점이 아쉬움.

## 더 빠른/더 안전한 풀이(필수)
- 아이디어: `yellow`의 약수를 탐색해 `brown` 타일 개수 조건을 만족하는지 확인합니다.
- 복잡도: `O(sqrt(yellow))`
- 왜 이게 더 좋은지: `brown`이 아닌 `yellow`의 제곱근까지만 탐색하므로 훨씬 빠르고 안정적입니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) 문제의 핵심 조건 활용: `yellow = (가로-2) * (세로-2)`라는 핵심 조건을 직접 활용하면 `yellow`의 약수만 탐색하는 최적화가 가능합니다.
- 2) 루프 범위 최적화: `가로 >= 세로` 조건에 따라 루프는 `h <= (w+h)/2` 까지만 돌면 충분합니다. 현재는 불필요한 값을 중복 탐색하고 있습니다.
- 3) 비효율적 탐색 기준: 현재 풀이는 `brown` 값에 따라 성능이 결정됩니다. `brown`이 크고 `yellow`가 작을 때 매우 비효율적일 수 있습니다.

## 즉시 수정 액션(최대 4개)
- `yellow`의 약수를 찾는 방식으로 알고리즘 변경을 강력히 권장합니다. (아래 예시 참고)
- 현 풀이를 유지한다면, `for h in range(3, wPlusH // 2 + 1):`로 루프 범위를 최적화하세요.
- `wPlusH`와 같은 축약된 변수명 대신 `sum_of_sides` 등 명확한 이름을 사용해 가독성을 높이세요.

```REVIEW_EXAMPLE
# 제목: O(sqrt(yellow)) 풀이 스케치 (yellow 약수 활용)
- 적용 조건: 현재 풀이보다 항상 빠르거나 비슷합니다.
- 핵심 아이디어: `yellow = (w-2)*(h-2)` 식을 활용합니다. `yellow`의 약수인 `h-2`를 `sqrt(yellow)`까지만 탐색하고, 파트너 약수 `w-2`를 구해 brown 개수 조건을 만족하는지 확인합니다.
- 복잡도: O(sqrt(yellow))
- 구현 스케치(python):
```python
def solution_fast(brown, yellow):
    # yellow의 약수 h_inner (h-2)를 찾는다.
    for h_inner in range(1, int(yellow**0.5) + 1):
        if yellow % h_inner == 0:
            w_inner = yellow // h_inner # w-2
            
            # brown 개수 = 2 * ((w-2) + (h-2)) + 4
            if 2 * (w_inner + h_inner) + 4 == brown:
                # 가로(w) >= 세로(h)
                return [w_inner + 2, h_inner + 2]
```
```