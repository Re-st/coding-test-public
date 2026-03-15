# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Silver/2751. 수 정렬하기 2/수 정렬하기 2.cc`

## 한 줄 결론
- (이 문제는) **병합 정렬(Merge Sort)** / 복잡도: O(N log N) / 여러 테스트케이스 환경에서 전역 변수 초기화 누락 위험

## 더 빠른/더 안전한 풀이(필수)
- **C++ 표준 라이브러리 `std::sort` 사용을 권장합니다.**
  - 아이디어: 고도로 최적화된 정렬 알고리즘(Introsort)을 바로 사용합니다.
  - 복잡도: O(N log N)
  - 왜 이게 더 좋은지: 코드가 한 줄로 매우 간결해지고, 직접 구현 시 생기는 버그 가능성을 원천 차단하며, 일반적으로 성능도 더 좋습니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) **재귀 내 불필요한 복사**: `mergesort` 함수가 호출될 때마다 `for (int i = s; i <= e; i++)` 루프에서 데이터를 `tmp` 배열로 복사합니다. 이는 상당한 오버헤드를 유발할 수 있습니다.
- 2) **인덱스 오버플로**: `mid = (e + s) / 2`는 `s`와 `e`가 매우 클 때 오버플로를 일으킬 수 있습니다. 이 문제의 N 범위(최대 100만)에서는 안전하지만, `mid = s + (e - s) / 2`와 같은 안전한 패턴을 습관화하는 것이 좋습니다.
- 3) **전역 변수 사용**: `ai`, `tmp`를 전역 변수로 사용하면, 만약 테스트케이스가 여러 개인 문제였다면 매번 데이터를 비우고 크기를 재설정하는 코드가 없어 오답의 원인이 됩니다.

## 즉시 수정 액션(최대 4개)
- 학습 목적이 아니라면, `mergesort` 구현 전체를 `std::sort(ai.begin(), ai.end());` 한 줄로 교체하세요.
- `static` 키워드는 전역 변수에 붙일 때 C++에서는 내부 연결을 의미하는데, 이 코드에서는 불필요하므로 제거해도 무방합니다.

```REVIEW_EXAMPLE
# 제목: 더 빠른 풀이 스케치 (계수 정렬 활용)
- 적용 조건: 수의 절댓값 범위(K)가 크지 않을 때(이 문제: 100만) O(N+K)로 가장 빠릅니다.
- 핵심 아이디어: 음수를 인덱스로 사용하기 위해 모든 수에 오프셋을 더합니다. 해당 수의 존재 여부를 boolean 배열에 기록한 뒤, 배열 전체를 순회하며 존재하는 수만 출력합니다.
- 복잡도: O(N + K) (N: 수의 개수, K: 수의 범위)
- 구현 스케치(C++):
```cpp
#include <iostream>
#include <vector>

const int OFFSET = 1000000;
const int MAX_SIZE = 2000001;

// N, K가 모두 100만 수준이라 스택 대신 정적/전역 데이터 영역 사용
bool appeared[MAX_SIZE] = {false};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        appeared[x + OFFSET] = true;
    }

    for (int i = 0; i < MAX_SIZE; ++i) {
        if (appeared[i]) {
            std::cout << i - OFFSET << '\n';
        }
    }
    return 0;
}
```
```