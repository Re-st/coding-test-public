# 제목: 더 효율적인 std::sort 기반 풀이
- 적용 조건: 거의 항상 현재 풀이보다 유리하며, 특히 N이 클 때 성능 차이가 극명합니다.
- 핵심 아이디어: 입력을 모두 받은 뒤, 내장 정렬 함수 `std::sort`를 사용해 O(N log N)으로 정렬하고, 그 후 누적합을 계산합니다.
- 복잡도: O(N log N)
- 구현 스케치(C++):
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n;
    std::cin >> n;
    std::vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> p[i];
    }

    std::sort(p.begin(), p.end());

    int total_wait_time = 0;
    int accumulated_time = 0;
    for (int time : p) {
        accumulated_time += time;
        total_wait_time += accumulated_time;
    }
    std::cout << total_wait_time;
    return 0;
}