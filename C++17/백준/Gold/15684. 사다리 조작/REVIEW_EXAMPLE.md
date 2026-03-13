# 제목: 재귀(DFS)를 이용한 백트래킹 풀이
- 적용 조건: 현재처럼 추가할 개수(k)가 3 이하로 정해진 조합 탐색 문제에 가장 이상적입니다.
- 핵심 아이디어: 추가할 사다리 개수(0~3)를 목표로 설정하고, DFS로 해당 개수만큼 사다리를 놓는 조합을 탐색합니다. 목표 개수만큼 사다리를 놓았다면 성공 여부를 체크하고, 성공 시 즉시 프로그램을 종료합니다.
- 복잡도: O((NH)³ × NH)
- 구현 스케치(C++):
int ans = -1;
void dfs(int count, int target, int start_r) {
    if (count == target) {
        if (all_identical()) {
            ans = target;
        }
        return;
    }

    for (int i = start_r; i <= h; ++i) {
        for (int j = 1; j < n; ++j) {
            if (lad[i][j] || lad[i][j - 1] || lad[i][j + 1]) continue;
            lad[i][j] = true;
            dfs(count + 1, target, i); // 다음 탐색은 현재 행부터 시작해 중복 방지
            lad[i][j] = false;
            if (ans != -1) return; // 하위 탐색에서 답을 찾았으면 즉시 복귀
        }
        if (ans != -1) return;
    }
}

int main() {
    // ... 입력 처리 ...
    for (int i = 0; i <= 3; ++i) {
        dfs(0, i, 1);
        if (ans != -1) {
            cout << ans;
            return 0;
        }
    }
    cout << -1;
}