# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Gold/2042. 구간 합 구하기/구간 합 구하기.cc`

## 한 줄 결론
- (이 문제는) **세그먼트 트리** / 복잡도: O((M+K)logN) / `Sum` 함수의 재귀 구현으로 인한 미미한 스택 깊이 위험

## 더 빠른/더 안전한 풀이(필수)
- 아이디어: 펜윅 트리(BIT)를 사용하여 점 업데이트와 구간 합을 모두 O(logN)에 처리합니다.
- 복잡도: O((M+K)logN)
- 왜 이게 더 좋은지: 구현이 세그먼트 트리보다 훨씬 짧고, 상수 시간이 빨라 실전에서 더 효율적입니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) 인덱스 변환: 문제의 1-based 인덱스(b, c)를 트리 내부 인덱스 `b + (1 << height) - 1`로 정확히 바꾸는 것이 핵심입니다.
- 2) 재귀 종료 조건: `Sum` 함수의 `start > end` 베이스 케이스가 없다면 무한 재귀에 빠집니다. (현재 코드는 올바름)
- 3) 자료형 범위: 쿼리 결과가 `long long` 범위를 초과할 수 있으므로, 트리와 변수 모두 `long long` 사용이 필수입니다. (현재 코드는 올바름)

## 즉시 수정 액션(최대 4개)
- 1. `Sum` 함수를 `while (start <= end)` 반복문으로 변경해 재귀 호출을 제거하여 안정성을 높이세요.
- 2. `(int) c` 캐스팅은 불필요합니다. `c`는 `long long`이므로 그대로 사용하세요.
- 3. `operations` 변수 대신 `for (int i = 0; i < m + k; ++i)`와 같이 명시적인 루프를 사용하세요.
- 4. 인덱스 계산 오프셋 `(1 << height) - 1`을 상수로 추출하면(`const int offset = ...`) 가독성이 향상됩니다.

```REVIEW_EXAMPLE
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
```