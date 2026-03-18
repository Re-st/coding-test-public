# 제목: O(sqrt(yellow)) 풀이 스케치 (yellow 약수 활용)
- 적용 조건: 현재 풀이보다 항상 빠르거나 비슷합니다.
- 핵심 아이디어: `yellow = (w-2)*(h-2)` 식을 활용합니다. `yellow`의 약수인 `h-2`를 `sqrt(yellow)`까지만 탐색하고, 파트너 약수 `w-2`를 구해 brown 개수 조건을 만족하는지 확인합니다.
- 복잡도: O(sqrt(yellow))
- 구현 스케치(python):