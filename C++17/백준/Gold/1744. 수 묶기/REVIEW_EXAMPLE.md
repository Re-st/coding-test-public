# 제목: 정렬을 이용한 명시적 풀이
- 적용 조건: 0, 1, 양수, 음수 케이스를 명시적으로 분리해 가독성을 높이고 싶을 때.
- 핵심 아이디어: 양수(>1), 음수(<0)를 별도 벡터에 저장하고, 1과 0의 개수를 셉니다. 양수는 내림차순, 음수는 오름차순 정렬 후, 각 배열을 앞에서부터 2개씩 묶어 곱합니다. 홀수 개의 음수가 남아있고 0이 없을 때만 남은 음수를 더합니다.
- 복잡도: O(N log N)
- 구현 스케치(C++):
vector<int> pos, neg;
int one_cnt = 0, zero_cnt = 0;
long long ans = 0;
// 입력값을 pos(>1), neg(<0), one_cnt, zero_cnt 로 분리
// ...
sort(pos.rbegin(), pos.rend());
sort(neg.begin(), neg.end());

for (int i = 0; i < pos.size() / 2; ++i) ans += (long long)pos[2*i] * pos[2*i+1];
if (pos.size() % 2 != 0) ans += pos.back();

for (int i = 0; i < neg.size() / 2; ++i) ans += (long long)neg[2*i] * neg[2*i+1];
if (neg.size() % 2 != 0 && zero_cnt == 0) {
    ans += neg.back();
}
ans += one_cnt;