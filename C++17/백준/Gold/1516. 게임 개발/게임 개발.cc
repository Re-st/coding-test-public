#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> A, Ap;
vector<int> indegree;
vector<int> reqtime;
vector<int> ans;
int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n, tmp;
    cin >> n;
    A.resize(n + 1);
    Ap.resize(n + 1);
    indegree.resize(n + 1);
    reqtime.resize(n + 1);
    ans.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> reqtime[i];
        while (true) {
            cin >> tmp;
            if (tmp == -1) break;
            indegree[i]++;
            A[tmp].push_back(i);
            Ap[i].push_back(tmp);
        }
    }
    queue<int> queue;
    for (int i = 1; i <= n; i++)
        if (!indegree[i]) {
            queue.push(i);
            ans[i] = reqtime[i];
        }
    while (!queue.empty()) {
        int a = queue.front();
        queue.pop();
        for (int i : A[a]) {
            if (!--indegree[i]) {
                queue.push(i);
                for (int j : Ap[i])
                    ans[i] = max(ans[i], ans[j] + reqtime[i]);
            }
        }
    }
    for (int i = 1; i <= n; i++)
        cout << ans[i] << '\n';
    return 0;
}