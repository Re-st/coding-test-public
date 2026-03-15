# next_permutation 완벽 이해하기

## 기본 개념

`next_permutation`은 `algorithm` 헤더에 있는 함수로, **벡터의 원소들을 다음 순열로 재배치**합니다.

## 함수 시그니처

```cpp
#include <algorithm>

bool next_permutation(Iterator first, Iterator last);
```

- **입력**: 벡터의 시작과 끝 반복자
- **동작**: 벡터의 원소들을 사전식 순서로 다음 순열로 재배치
- **반환값**: 
  - `true`: 다음 순열이 존재하여 재배치함
  - `false`: 더 이상 다음 순열이 없음 (마지막 순열)

## 핵심 포인트

### 1. 벡터 자체를 수정함
```cpp
vector<string> words = {"a", "b", "c"};
next_permutation(words.begin(), words.end());
// words가 {"a", "c", "b"}로 변경됨!
```

### 2. 사전식 순서로 정렬됨
- "a" < "b" < "c" 순서로 정렬
- 모든 가능한 순열을 사전식 순서로 생성

### 3. do-while 패턴 사용
```cpp
do {
    // 현재 순열 처리
    process(words);
} while (next_permutation(words.begin(), words.end()));
```

**왜 do-while?**
- 첫 번째 순열(원래 순서)도 처리해야 하기 때문
- while을 쓰면 첫 번째 순열을 건너뛰게 됨

## 실제 예시

### 3개 원소: 3! = 6가지
```
초기: [a, b, c]
1: [a, b, c]  ← 원래 순서
2: [a, c, b]
3: [b, a, c]
4: [b, c, a]
5: [c, a, b]
6: [c, b, a]  ← 마지막 순열
```

### 4개 원소: 4! = 24가지
```
초기: [a, b, c, d]
1: [a, b, c, d]
2: [a, b, d, c]
3: [a, c, b, d]
...
24: [d, c, b, a]  ← 마지막 순열
```

## 우리 코드에서의 사용

```cpp
vector<string> words(4);
for (int i = 0; i < 4; i++) {
    cin >> words[i];  // 예: "abc", "def", "ghi", "jkl"
}

sort(words.begin(), words.end());  // 중요! 정렬 필수
// 정렬 후: ["abc", "def", "ghi", "jkl"]

int ans = 0;
do {
    // words가 각 순열로 변경됨:
    // 1번째: ["abc", "def", "ghi", "jkl"]
    // 2번째: ["abc", "def", "jkl", "ghi"]
    // 3번째: ["abc", "ghi", "def", "jkl"]
    // ...
    // 24번째: ["jkl", "ghi", "def", "abc"]
    
    ans += countCrosswords(words[0], words[1], words[2], words[3]);
} while (next_permutation(words.begin(), words.end()));
```

## 왜 sort가 필요한가?

`next_permutation`은 **사전식 순서**로 다음 순열을 생성합니다.
정렬되지 않은 상태에서 시작하면, 모든 순열을 다 보지 못할 수 있습니다!

```cpp
// 잘못된 예
vector<string> words = {"c", "a", "b"};
do {
    // 처리
} while (next_permutation(...));
// "a", "b", "c"로 시작하는 순열들을 건너뜀!

// 올바른 예
vector<string> words = {"c", "a", "b"};
sort(words.begin(), words.end());  // ["a", "b", "c"]로 정렬
do {
    // 모든 6가지 순열을 다 봄
} while (next_permutation(...));
```

## 동작 원리 (간단히)

1. **오른쪽에서 왼쪽으로** 스캔하면서
2. **왼쪽보다 큰 원소**를 찾음
3. 그 원소를 **더 작은 원소와 교환**
4. 그 오른쪽 부분을 **역순으로 뒤집음**

예: `[1, 3, 2]` → `[2, 1, 3]`
- 오른쪽에서 `3`을 찾음
- `3`보다 작은 `2`를 찾아서 교환: `[1, 2, 3]`
- `2` 오른쪽을 역순: `[1, 2, 3]` (이미 정렬됨)

## 요약

- ✅ `algorithm` 헤더에 있음
- ✅ 벡터의 원소 순서를 **직접 변경**함
- ✅ 사전식 순서로 다음 순열 생성
- ✅ `sort` 후 사용해야 모든 순열을 다 볼 수 있음
- ✅ `do-while` 패턴으로 사용
- ✅ 4개 원소면 24가지 순열 생성
