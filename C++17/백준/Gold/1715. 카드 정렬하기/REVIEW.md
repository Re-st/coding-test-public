# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Gold/1715. 카드 정렬하기/카드 정렬하기.cc`

## 한 줄 결론
- **그리디 알고리즘 + 우선순위 큐** / 복잡도: O(N log N) / 누적 합계(`acc`) 변수의 `int` 오버플로가 가장 위험한 실수입니다.

## 더 빠른/더 안전한 풀이(필수)
- 현 접근이 거의 최선입니다. 매번 가장 작은 두 묶음을 합치는 그리디 전략이 최적해를 보장하며(허프만 코드 원리), 우선순위 큐는 이 전략을 O(N log N)으로 가장 효율적으로 구현하는 자료구조입니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) **초기값/시작점/종료조건**: N=1일 때 비교가 0번 필요하며, `while (is.size() > 1)` 조건이 이를 올바르게 처리합니다.
- 2) **인덱스/경계/오버플로/방문처리**: **`acc` 변수의 오버플로** 가능성이 매우 높습니다. N 최대(10만), 카드 크기 최대(1000)일 때 누적 비교 횟수는 `int` 범위를 훨씬 초과하므로(`약 8.5 * 10^9` 추정) `long long` 타입이 필수입니다.
- 3) **자료구조/성능 함정**: `Compare` 구조체 대신 C++ 표준 라이브러리의 `greater<int>`를 사용하면 코드가 더 간결하고 표준적입니다.

## 즉시 수정 액션(최대 4개)
- 1. `int acc = 0;` -> `long long acc = 0;` (오버플로 방지)
- 2. `priority_queue<int, vector<int>, Compare> is;` -> `priority_queue<long long, vector<long long>, greater<long long>> pq;` (가독성/안전성)
- 3. 전역 변수 `is`, `n` 대신 `main` 함수 내 지역 변수로 선언하여 코드의 재사용성과 안정성을 높이세요.

```REVIEW_EXAMPLE
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
```