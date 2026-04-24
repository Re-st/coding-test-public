#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

int N, px[21], py[21], total_x, total_y;
double ans = 1e9;

void dfs(int idx, int cnt, long long x, long long y) {
    if (cnt == N / 2) {
        double vx = 2 * x - total_x;
        double vy = 2 * y - total_y;
        ans = min(ans, sqrt(vx * vx + vy * vy));
        return;
    }
    if (idx > N) return;

    dfs(idx + 1, cnt + 1, x + px[idx], y + py[idx]);
    dfs(idx + 1, cnt, x, y);
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		cin >> N;
        total_x = 0; total_y = 0; ans = 1e9;
        for (int i = 1; i <= N; i++) {
            cin >> px[i];
            cin >> py[i];
            total_x += px[i];
            total_y += py[i];
        }
        dfs(2, 1, px[1], py[1]);
        printf("%f\n", ans);
	}
	return 0;
}