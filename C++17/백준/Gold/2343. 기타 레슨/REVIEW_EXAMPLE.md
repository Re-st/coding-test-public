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