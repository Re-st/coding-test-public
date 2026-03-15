#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int countCrosswords(string H1, string H2, string V1, string V2) {
    int cnt = 0;
    int l1 = H1.length(), l2 = H2.length(), l3 = V1.length(), l4 = V2.length();
    
    // H1에서 V1과 교차하는 위치
    for (int h1_v1 = 0; h1_v1 < l1; h1_v1++) {
        // V1의 시작 y좌표 (음수 가능)
        for (int v1_start = -l3 + 1; v1_start < 1; v1_start++) {
            int v1_idx_at_0 = -v1_start;
            if (v1_idx_at_0 < 0 || v1_idx_at_0 >= l3) continue;
            if (V1[v1_idx_at_0] != H1[h1_v1]) continue;
            
            // H1에서 V2와 교차하는 다른 위치
            for (int h1_v2 = 0; h1_v2 < l1; h1_v2++) {
                if (abs(h1_v1 - h1_v2) < 2) continue;
                
                // V2의 시작 y좌표
                for (int v2_start = -l4 + 1; v2_start < 1; v2_start++) {
                    int v2_idx_at_0 = -v2_start;
                    if (v2_idx_at_0 < 0 || v2_idx_at_0 >= l4) continue;
                    if (V2[v2_idx_at_0] != H1[h1_v2]) continue;
                    
                    // H2에서 V1과 교차하는 위치
                    for (int h2_v1 = 0; h2_v1 < l2; h2_v1++) {
                        // H2-V1 교차점의 y좌표
                        for (int cross_y = max(1, v1_start + 1); cross_y <= min(l3 - 1, v1_start + l3 - 1); cross_y++) {
                            if (cross_y < 2) continue;
                            
                            int v1_idx_at_cross = cross_y - v1_start;
                            if (v1_idx_at_cross < 0 || v1_idx_at_cross >= l3) continue;
                            if (V1[v1_idx_at_cross] != H2[h2_v1]) continue;
                            
                            // H2에서 V2와 교차하는 위치 (평행선 성질 이용)
                            int h2_v2 = h2_v1 + (h1_v2 - h1_v1);
                            if (h2_v2 < 0 || h2_v2 >= l2) continue;
                            
                            // H2-V2 교차점의 y좌표는 H2-V1과 같음
                            int v2_idx_at_cross = cross_y - v2_start;
                            if (v2_idx_at_cross < 0 || v2_idx_at_cross >= l4) continue;
                            if (V2[v2_idx_at_cross] != H2[h2_v2]) continue;
                            
                            cnt++;
                        }
                    }
                }
            }
        }
    }
    
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    vector<string> words(4);
    for (int i = 0; i < 4; i++) {
        cin >> words[i];
    }
    
    int ans = 0;
    sort(words.begin(), words.end());
    
    // 24가지 순열 모두 처리
    do {
        ans += countCrosswords(words[0], words[1], words[2], words[3]);
    } while (next_permutation(words.begin(), words.end()));
    
    cout << ans << endl;
    
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    vector<string> words(4);
    for (int i = 0; i < 4; i++) {
        cin >> words[i];
    }
    
    cout << solve(words) << endl;
    
    return 0;
}
