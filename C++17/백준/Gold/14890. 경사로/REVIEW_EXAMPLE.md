# 제목: 더 안전한 풀이 스케치
- 적용 조건: 현재 풀이의 복잡한 상태 관리가 버그를 유발할 때
- 핵심 아이디어: `bool` 배열로 경사로 설치 위치를 명시적으로 추적. 높이 변화 지점에서 경사로 설치 조건을(범위, 평평함, 미설치) 하나씩 직접 검사.
- 복잡도: O(N^2)
- 구현 스케치(C++):
bool check(const vector<short>& path) {
    vector<bool> placed(n, false);
    for (int i = 0; i < n - 1; ++i) {
        int diff = path[i] - path[i+1];

        if (abs(diff) > 1) return false;
        if (diff == 0) continue;

        if (diff == 1) { // 내리막: i -> i+1
            for (int j = 1; j <= l; ++j) {
                if (i + j >= n || path[i+1] != path[i+j] || placed[i+j]) return false;
            }
            for (int j = 1; j <= l; ++j) placed[i+j] = true;
        } else { // 오르막: i -> i+1 (diff == -1)
            for (int j = 0; j < l; ++j) {
                if (i - j < 0 || path[i] != path[i-j] || placed[i-j]) return false;
            }
            for (int j = 0; j < l; ++j) placed[i-j] = true;
        }
    }
    return true;
}