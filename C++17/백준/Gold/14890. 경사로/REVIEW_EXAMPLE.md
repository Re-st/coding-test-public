# 제목: 경사로 설치 여부를 명시적으로 추적하는 안전한 풀이
- 적용 조건: 현재 풀이의 로직이 너무 복잡하여 디버깅이 어렵거나, 실수를 줄이고 싶을 때 항상 유리합니다.
- 핵심 아이디어: 각 행/열을 검사할 때마다 `bool installed[101]` 배열을 사용합니다. 경사로를 놓을 때, (1) L칸이 평평한지, (2) 이미 다른 경사로가 없는지 `installed` 배열로 확인 후, 설치 위치를 `true`로 표시합니다.
- 복잡도: O(N^2)
- 구현 스케치(C++):
bool is_passable(const vector<short>& path) {
    bool installed[101] = {false};
    for (int i = 0; i < n - 1; ++i) {
        int diff = path[i] - path[i+1];
        if (abs(diff) > 1) return false;

        if (diff == 1) { // 내리막 경사로: [i+1, ..., i+L]에 설치
            if (i + l >= n) return false;
            for (int j = i + 1; j <= i + l; ++j) {
                if (path[j] != path[i+1] || installed[j]) return false;
                installed[j] = true;
            }
        } else if (diff == -1) { // 오르막 경사로: [i-L+1, ..., i]에 설치
            if (i - l + 1 < 0) return false;
            for (int j = i; j >= i - l + 1; --j) {
                if (path[j] != path[i] || installed[j]) return false;
                installed[j] = true;
            }
        }
    }
    return true;
}