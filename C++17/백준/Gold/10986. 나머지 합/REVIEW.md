# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Gold/10986. 나머지 합/나머지 합.cc`

안녕하세요! 코딩 테스트 코드 리뷰어입니다. 제출하신 '나머지 합' 문제의 C++ 코드에 대한 리뷰를 시작하겠습니다.

## 1) 요약
누적 합과 모듈러 연산의 성질을 활용한 매우 효율적인 풀이입니다. `(S[j] - S[i-1]) % M == 0` 이 `S[j] % M == S[i-1] % M` 과 같다는 점을 이용하여, 누적 합을 M으로 나눈 나머지가 같은 것들의 개수를 세어 조합(Combination)으로 정답을 구했습니다.

- 시간 복잡도: O(N + M)
- 공간 복잡도: O(M)

## 2) 시간 / 공간 복잡도 점검
- **시간 복잡도**: 입력 배열을 한 번 순회하며 누적 합 나머지를 계산하는 데 O(N), 나머지 개수를 바탕으로 정답을 계산하는 데 O(M)이 소요됩니다. N이 최대 10<sup>6</sup>, M이 최대 10<sup>3</sup>이므로 O(N+M)은 시간 제한 내에 충분히 동작하는 매우 효율적인 알고리즘입니다.
- **공간 복잡도**: 나머지의 개수를 저장하기 위해 크기 M의 배열을 사용하므로 O(M)의 공간을 사용합니다. M이 최대 10<sup>3</sup>이므로 메모리 사용량도 매우 안정적입니다.

## 3) 구현/버그 리스크
현재 코드에는 **정수 오버플로(Integer Overflow)** 위험이 있습니다.

1.  **누적 합 계산 시 오버플로 위험**
    - `acc` 변수가 `int`로 선언되었습니다. `acc`는 `0` ~ `m-1`의 값을 가지지만, 입력 `tmp`는 최대 10<sup>9</sup>까지 가능합니다.
    - `acc + tmp` 연산은 `int + int` 연산이 되어 결과가 `int`의 최댓값(약 2 * 10<sup>9</sup>)을 초과할 수 있습니다. 예를 들어, `acc`가 999이고 `tmp`가 2*10<sup>9</sup>일 경우 오버플로가 발생하여 잘못된 나머지를 계산하게 됩니다.

    ```cpp
    // 위험한 부분
    int acc = 0;
    while (n--) {
        cin >> tmp;
        acc = (acc + tmp) % m; // acc + tmp 에서 오버플로 발생 가능
        bin[acc]++;
    }
    ```

    - **해결책**: 누적 합을 저장하는 `acc` 변수를 `long long`으로 선언하여 오버플로를 방지해야 합니다.

2.  **결과값 계산 시 오버플로 위험**
    - 만약 모든 누적 합의 나머지가 0이라면, `bin[0]`의 값은 `N+1` (초기값 1 포함)이 됩니다. N이 최대 10<sup>6</sup>이므로 `bin[0]`은 약 10<sup>6</sup>이 될 수 있습니다.
    - `bin[m] * (bin[m] - 1)` 연산은 `(10^6)^2 = 10^12`에 가까운 값이 될 수 있어 `long long`의 범위가 필요합니다.
    - 코드에서 `bin`과 `ans`를 `long`으로 선언했는데, 일부 채점 환경에서는 `long`이 `int`와 동일한 32비트일 수 있습니다. 이식성과 안정성을 위해 64비트 정수형임이 보장되는 `long long`을 사용하는 것이 좋습니다.

## 4) 엣지 케이스 체크리스트
현재 로직은 대부분의 엣지 케이스를 잘 처리하지만, 오버플로와 관련된 최대 입력 케이스에서 문제가 발생할 수 있습니다.

- **최대 입력**: N = 10<sup>6</sup>, M = 1000 이고 모든 A<sub>i</sub> = 10<sup>9</sup>일 때 `acc + tmp`에서 오버플로가 발생할 수 있습니다.
- **값이 한쪽으로 쏠리는 경우**: 모든 A<sub>i</sub>가 M의 배수(예: 0)일 경우, 모든 누적 합의 나머지가 0이 됩니다. 이때 `bin[0]`은 `10^6 + 1`이 되고, `ans`를 계산할 때 `long long` 타입이 필수적입니다.

## 5) 리팩토링/가독성 개선 (선택)
코드는 매우 간결하지만, 변수명과 루프 구조를 조금 더 명확하게 개선할 수 있습니다.

1.  **더 명확한 변수명 사용**
    - `bin`: `remainder_counts` 또는 `mod_counts`와 같이 목적이 드러나는 이름으로 바꾸면 좋습니다.
    - `acc`: `prefix_sum_mod` 등으로 바꾸면 누적 합의 나머지라는 의미를 명확히 할 수 있습니다.

2.  **`for` 루프 사용**
    - `while (n--)`이나 `while (m--)` 같은 패턴은 간결하지만, 루프의 목적과 범위를 명확히 보여주는 `for` 루프를 사용하는 것이 가독성에 더 도움이 될 수 있습니다.

    ```cpp
    // 개선 제안 (스니펫)
    long long ans = 0;
    for (int i = 0; i < m; ++i) {
        ans += bin[i] * (bin[i] - 1) / 2;
    }
    ```

### 수정 제안 코드
아래와 같이 오버플로 위험을 해결한 코드를 제안합니다.

```cpp
#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    int m;
    std::cin >> n >> m;

    std::vector<long long> remainder_counts(m, 0);
    long long prefix_sum_mod = 0;
    
    // S[0] % M = 0 인 경우를 미리 카운트
    remainder_counts[0] = 1;

    for (int i = 0; i < n; ++i) {
        int num;
        std::cin >> num;
        prefix_sum_mod = (prefix_sum_mod + num) % m;
        remainder_counts[prefix_sum_mod]++;
    }

    long long ans = 0;
    for (int i = 0; i < m; ++i) {
        if (remainder_counts[i] > 1) {
            ans += remainder_counts[i] * (remainder_counts[i] - 1) / 2;
        }
    }

    std::cout << ans << "\n";
    return 0;
}
```

## 6) 한 줄 평
"누적 합 나머지를 활용한 접근법은 매우 훌륭하지만, 연산 과정에서 발생할 수 있는 정수 오버플로를 방지하기 위해 `long long` 자료형을 사용하면 더욱 안정적인 코드가 될 것입니다."