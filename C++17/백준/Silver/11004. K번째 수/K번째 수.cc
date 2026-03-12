#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// s: 시작, e: 끝, k: 찾고자 하는 타겟 인덱스
void quickSelection(int s, int e, vector<int>& ai, int k) {
    if (s >= e) return; // 기저 사례: 더 이상 분할할 수 없음

    // 1. 피벗을 중간값으로 선택하여 최악의 경우(O(N^2)) 방지
    int pivot = ai[(s + e) / 2];
    int S = s, E = e;

    // 2. 파티션 로직: 피벗을 기준으로 좌우 배분
    while (S <= E) {
        while (ai[S] < pivot) S++;
        while (ai[E] > pivot) E--;
        if (S <= E) {
            swap(ai[S++], ai[E--]); // 데이터를 교환하며 범위를 좁힘
        }
    }

    // 3. 타겟 위치(k)에 따른 재귀 분기
    // S와 E는 현재 교차된 상태임. E는 왼쪽 구간의 끝, S는 오른쪽 구간의 시작.
    if (s < E && k <= E) quickSelection(s, E, ai, k);
    if (S < e && k >= S) quickSelection(S, e, ai, k);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<int> ai(n);
    for (int i = 0; i < n; i++) cin >> ai[i];

    // 전체 범위(0 ~ n-1)에서 k-1번째 인덱스를 찾음
    quickSelection(0, n - 1, ai, k - 1);

    cout << ai[k - 1];
    return 0;
}