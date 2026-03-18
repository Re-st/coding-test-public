# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./Python3/프로그래머스/3/42579. 베스트앨범/베스트앨범.py`

## 한 줄 결론
- (이 문제는) **해시/정렬** / 복잡도: O(N + M log M) / 가장 위험한 실수는 다중 조건 정렬(재생수 내림차순, 고유번호 오름차순)을 잘못 구현하는 것입니다.

## 더 빠른/더 안전한 풀이(필수)
- 아이디어: 모든 곡 정보를 장르별로 그룹화한 뒤, 장르 총 재생 수 기준으로 정렬하고, 각 장르 내에서 곡을 **한 번만** 정렬합니다.
- 복잡도: O(N log N)
- 왜 이게 더 좋은지: 현재 풀이(O(N))보다 점근적 복잡도는 높지만, 데이터 수집과 정렬 로직이 명확히 분리되어 코드가 더 직관적이고 잠재적 버그(예: 루프 내 슬라이싱 누락) 위험이 적습니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) 정렬 조건: 장르 내 곡 정렬 시 `(-재생수, 고유번호)`라는 2차 정렬 키를 정확히 구현해야 합니다. 부호나 순서가 틀리면 오답이 됩니다.
- 2) 성능 함정: 현재 코드는 루프마다 정렬 후 상위 2개만 남겨 `O(N)`을 달성했습니다. 만약 `genreBest[g] = genreBest[g][:2]` 슬라이싱을 빼먹는다면, 리스트가 계속 커져 시간 복잡도가 `O(N^2)`에 가깝게 저하되어 시간 초과가 발생합니다.
- 3) 자료구조: 장르별 총 재생 수(`genreCount`)와 곡 목록(`genreBest`)을 별도 dict로 관리 중인데, 이를 하나의 dict에 묶어 관리하면 구조가 더 명확해집니다.

## 즉시 수정 액션(최대 4개)
- **로직 분리**: 가독성과 유지보수성을 위해, 곡 정보 수집 루프와 정렬/선택 로직을 분리하는 것을 권장합니다.
- **변수명 개선**: `genreCount` → `genre_total_plays`, `genreBest` → `songs_by_genre` 와 같이 변수명을 더 명확하게 변경해 보세요.
- **`print`문 제거**: 제출 전 디버깅용 `print` 함수 호출을 모두 제거하세요.

```REVIEW_EXAMPLE
# 제목: 가독성을 높인 풀이 스케치
- 적용 조건: 로직의 명확성을 성능보다 우선시할 때, 또는 일반적인 코딩 스타일에 맞추고자 할 때.
- 핵심 아이디어: 데이터를 먼저 모두 수집(O(N))한 후, 장르별 정렬(O(M log M)) 및 장르 내 곡 정렬(최악 O(N log N))을 순차적으로 수행하여 로직을 분리합니다.
- 복잡도: O(N log N)
- 구현 스케치:
  ```python
  from collections import defaultdict
  
  def solution_refactored(genres, plays):
      song_map = defaultdict(lambda: {'total_plays': 0, 'songs': []})
  
      # 1. 데이터 수집 (O(N))
      for i, (g, p) in enumerate(zip(genres, plays)):
          song_map[g]['total_plays'] += p
          song_map[g]['songs'].append((p, i))
  
      # 2. 장르 정렬 (O(M log M))
      sorted_genres = sorted(song_map.keys(), 
                             key=lambda g: song_map[g]['total_plays'], 
                             reverse=True)
  
      answer = []
      # 3. 장르 내 노래 정렬 및 선택 (전체 합쳐서 최악 O(N log N))
      for g in sorted_genres:
          sorted_songs = sorted(song_map[g]['songs'], key=lambda s: (-s[0], s[1]))
          answer.extend([song[1] for song in sorted_songs[:2]])
              
      return answer
  ```
```