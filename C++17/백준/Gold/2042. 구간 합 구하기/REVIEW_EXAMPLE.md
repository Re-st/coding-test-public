# 제목: 펜윅 트리(BIT)를 이용한 풀이 스케치
- 적용 조건: 점 업데이트와 구간 합 쿼리가 반복되는 문제에 가장 효율적입니다.
- 핵심 아이디어: 각 숫자의 부분합을 트리 형태로 저장. `update`와 `query` 연산을 O(logN)에 수행하여 구간 합을 계산합니다.
- 복잡도: O((M+K)logN)
- 구현 스케치(C++):
#include <vector>
using namespace std;

vector<long long> tree;
vector<long long> nums;
int N;

// i번째 수에 val만큼 더함
void update(int i, long long diff) {
    while (i <= N) {
        tree[i] += diff;
        i += (i & -i);
    }
}

// 1부터 i까지의 합
long long query(int i) {
    long long sum = 0;
    while (i > 0) {
        sum += tree[i];
        i -= (i & -i);
    }
    return sum;
}

// main 함수 내 로직 예시
// 1. 초기화
// for (int i = 1; i <= N; ++i) { cin >> nums[i]; update(i, nums[i]); }
// 2. 값 변경: a=1, b번째 수를 c로
// long long diff = c - nums[b];
// nums[b] = c;
// update(b, diff);
// 3. 구간 합: a=2, b~c 합
// cout << query(c) - query(b - 1) << '\n';