	#include <iostream>
	#include <vector>
	#include <algorithm>
	#include <string>

	using namespace std;

	int N, h[50], ok[50];

	int main() {
		cin >> N;
		for (int i = 0; i < N; i++)
			cin >> h[i];
		for (int i = 0; i < N; i++) {
			double tilt = -1e9;
			for (int di = 1; di < N - i; di++) {
				if (h[i + di] > h[i] + di * tilt) {
					tilt = (double) (h[i + di] - h[i]) / di;
					ok[i]++;
					ok[i + di]++;
					//if (i == 1) printf("i + di: %d tilt : %f\n", i + di, tilt);
				}
			}
		}
		pair<int, int> maxes = { 0, 0 }; // buildingNum, buildingIdx
		for (int i = 0; i < N; i++) {
			maxes = max(make_pair(ok[i], i), maxes);
		}
		cout << maxes.first;
		return 0;
	}