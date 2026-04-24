	#include <iostream>
	#include <vector>
	#include <algorithm>
	#include <string>

	using namespace std;

	int T, N;
	string tc;

	bool check(int idx) {
		//printf("T is %d, idx is %d, N is %d\n", T, idx, N);
		if (idx == N) return true;
		else if (idx + 1 < N and tc[idx] == '0' and tc[idx + 1] == '1' and check(idx + 2)) return true;
		else if (idx + 3 < N and tc[idx] == '1' and tc[idx + 1] == '0' and tc[idx + 2] == '0') {
			idx += 3;
			while (idx < N and tc[idx] == '0') {
				idx++;
			}
			if (idx >= N) return false;
			if (check(++idx)) return true;
			while (idx < N and tc[idx] == '1') {
				if (check(++idx)) return true;
			}
		}
		return false;
	}

	int main() {
		cin >> T;
		while (T--) {
			cin >> tc;
			N = tc.size();
			if (check(0)) cout << "YES\n"; else cout << "NO\n";
		}
		return 0;
	}