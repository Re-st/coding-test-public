# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Gold/2343. 기타 레슨/기타 레슨.cc`

## 한 줄 결론
- (이 문제는) **매개 변수 탐색** / 복잡도: O(N log S) (S=총 강의 길이 합) / `fits` 함수의 디스크 개수 차감 로직(`leftBluray--`)이 복잡하여 실수하기 쉽습니다.

## 더 빠른/더 안전한 풀이(필수)
- 현 접근이 거의 최선입니다. 다만, 구현을 더 명확하고 안전하게 개선할 수 있습니다.
  - 아이디어: `fits` 함수에서 남은 디스크를 차감하는 대신, **사용한 디스크 수를 직접 세는 방식**으로 구현합니다.
  - 복잡도: O(N log S)로 동일
  - 왜 이게 더 좋은지: 코드의 의도가 명확해지고, `leftBluray--` 같은 까다로운 증감 연산자 사용을 피해 버그 가능성을 줄입니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) 초기값/시작점/종료조건: 이진 탐색의 시작점 `mMin`을 `max(maxClip, (int) ceil(total / m))`으로 설정했습니다. `mMin = maxClip`만으로도 충분하고 안전하며, 불필요한 부동 소수점 연산을 피할 수 있습니다.
- 2) 인덱스/경계/오버플로/방문처리: `fits` 함수에서 블루레이 크기(`mSize`)가 개별 강의 길이(`is[currClip]`)보다 작을 수 있는 경우를 명시적으로 처리하지 않습니다. 현재는 `main`의 `mMin` 설정 덕분에 문제가 없지만, 함수 자체의 안정성은 떨어집니다.
- 3) 자료구조/성능 함정: `middle = (mMin + mMax) / 2;`는 `mMin + mMax`가 `int` 범위를 초과할 때 오버플로를 일으킬 수 있습니다. 이 문제의 제약(S ≈ 10^9)에서는 괜찮지만, 더 큰 범위에서는 `mMin + (mMax - mMin) / 2`와 같이 작성하는 것이 안전합니다.

## 즉시 수정 액션(최대 4개)
- 1. 이진 탐색의 하한(lower bound)을 `int mMin = maxClip;`으로 단순화하세요.
- 2. `fits` 함수 로직을 사용한 디스크 수를 세는 방식으로 변경하여 가독성과 안정성을 높이세요. (아래 스케치 참고)
- 3. (Best Practice) `middle` 계산 시 `mMin + (mMax - mMin) / 2`를 사용하여 오버플로 가능성을 원천 차단하세요.
- 4. (Best Practice) 전역 변수 대신 `fits` 함수의 인자로 값을 넘겨주는 것을 고려하세요.

```REVIEW_EXAMPLE
# 제목: 더 명확하고 안전한 풀이 스케치
- 적용 조건: 현재 풀이도 정답이지만, 이 스케치는 `fits` 함수의 책임과 경계 조건이 명확하여 실수를 줄입니다.
- 핵심 아이디어: `fits` 함수는 "주어진 블루레이 크기로 M개 이하에 담을 수 있는가?"를 검사합니다. 필요한 디스크 수를 직접 세고, 현재 디스크에 누적된 길이를 관리하는 방식으로 구현하여 명확성을 높입니다.
- 복잡도: O(N log S) (S는 총 강의 길이 합)
- 구현 스케치(C++):
bool fits(int capacity, int m_limit, const vector<int>& lessons) {
    int disk_count = 1;
    int current_len = 0;
    for (int len : lessons) {
        // 이 check는 이진 탐색 하한 설정 덕에 불필요하지만,
        // 함수 단독의 안정성을 위해 넣는 것이 좋습니다.
        if (len > capacity) return false;
        
        if (current_len + len > capacity) {
            disk_count++;
            current_len = len;
        } else {
            current_len += len;
        }
    }
    return disk_count <= m_limit;
}

// main 함수 내 이진 탐색 부분
int low = maxClip, high = total;
while (low < high) {
    int mid = low + (high - low) / 2;
    if (fits(mid, m, is)) {
        high = mid;
    } else {
        low = mid + 1;
    }
}
cout << low;
```