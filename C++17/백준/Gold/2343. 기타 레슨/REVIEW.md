# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Gold/2343. 기타 레슨/기타 레슨.cc`

## 한 줄 결론
- **매개 변수 탐색** / 복잡도: O(N * log(S)) / 제일 위험한 실수: 이진 탐색 하한선의 부정확한 계산

## 더 빠른/더 안전한 풀이(필수)
- 현 접근이 거의 최선입니다. 블루레이 크기가 커질수록 필요한 개수가 줄어드는 단조성이 있어, 매개 변수 탐색이 정석적인 최적 풀이입니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) 초기값/시작점: 이진 탐색 하한선 `mMin` 설정 시, `(int) ceil(total / m)`은 정수 나눗셈으로 인해 실제 `ceil` 값보다 작을 수 있어 위험합니다. `maxClip`만으로도 충분히 안전한 하한선입니다.
- 2) 경계/로직: `fits` 함수의 `leftSpace`와 `leftBluray`를 이용한 현재 로직은 다소 복잡합니다. 필요한 블루레이 개수를 1부터 세고, 용량이 초과될 때마다 개수를 늘리는 방식이 더 직관적이고 실수가 적습니다.
- 3) 자료구조/오버플로: 강의 길이 총합 `total`이 `int` 범위(`~2*10^9`)에 가깝습니다(`10^5 * 10^4 = 10^9`). 문제 제약이 조금만 더 커지면 `long long`이 필요하므로 항상 오버플로를 염두에 두어야 합니다.

## 즉시 수정 액션(최대 4개)
- 1. 이진 탐색 하한선을 `int mMin = maxClip;` 으로 단순화하여 잠재적 버그를 제거하세요.
- 2. `fits` 함수를 가독성과 안정성이 높은 아래 방식으로 수정하는 것을 권장합니다.
   ```cpp
   bool fits(int mSize) {
       int count = 1, current_sum = 0;
       for (int len : is) {
           if (current_sum + len > mSize) {
               count++;
               current_sum = len;
           } else {
               current_sum += len;
           }
       }
       return count <= m;
   }
   ```

```REVIEW_EXAMPLE
# 제목: 더 간결하고 안전한 매개 변수 탐색 구현
- 적용 조건: 현재 풀이와 알고리즘은 동일하나, 구현을 더 명확하고 안전하게 만들고 싶을 때.
- 핵심 아이디어: 이진 탐색의 하한선은 `maxClip`만으로 충분하며, `fits` 함수는 필요한 블루레이 개수를 직접 세는 방식으로 구현하면 훨씬 직관적입니다.
- 복잡도: O(N * log(S)) (동일)
- 구현 스케치(C++):
bool fits(int mSize, int M, const vector<int>& lectures) {
    int count = 1, current_sum = 0;
    for (int len : lectures) {
        // 단일 강의가 용량을 초과하는 경우는 low 경계에서 이미 필터링됨
        if (current_sum + len > mSize) {
            count++;
            current_sum = len;
        } else {
            current_sum += len;
        }
    }
    return count <= M;
}

// main 함수 내 이진 탐색 부분
int mMin = maxClip, mMax = total;
while (mMin < mMax) {
    int middle = mMin + (mMax - mMin) / 2;
    if (fits(middle, m, is)) {
        mMax = middle;
    } else {
        mMin = middle + 1;
    }
}
cout << mMin;
```