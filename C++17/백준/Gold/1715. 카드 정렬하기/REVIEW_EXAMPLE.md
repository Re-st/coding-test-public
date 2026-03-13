# 제목: 더 안전하고 간결한 풀이 스케치
- 적용 조건: 항상 현재 코드보다 버그 위험이 적고 간결합니다.
- 핵심 아이디어: `long long`으로 오버플로를 방지하고, `std::greater`와 지역 변수를 사용해 코드 안정성과 가독성을 높입니다.
- 복잡도: O(N log N)
- 구현 스케치(C++):
#include <functional> // greater

// main 함수 내에서
int n;
cin >> n;

priority_queue<long long, vector<long long>, greater<long long>> pq;
for (int i = 0; i < n; ++i) {
    int card_size;
    cin >> card_size;
    pq.push(card_size);
}

long long total_comparisons = 0;
while (pq.size() > 1) {
    long long first = pq.top(); pq.pop();
    long long second = pq.top(); pq.pop();
    
    long long sum = first + second;
    total_comparisons += sum;
    pq.push(sum);
}
cout << total_comparisons;