# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `C++/SWEA/Unrated/5658. ［모의 SW 역량테스트］ 보물상자 비밀번호/［모의 SW 역량테스트］ 보물상자 비밀번호.cpp`

## 한 줄 결론
- (이 문제는) **[시뮬레이션, Set 활용]** / 복잡도: O(N^2) / 직접 구현한 16진수 변환 함수(`read_number`)의 실수 위험

## 더 빠른/더 안전한 풀이(필수)
- 아이디어: `std::string`으로 입력을 받고 `substr`와 `stoi(s, nullptr, 16)`를 써서 16진수 변환을 자동화.
- 복잡도: O(N^2)
- 왜 이게 더 좋은지: 16진수 변환을 직접 구현할 필요가 없어 코드가 매우 간결해지고 버그 가능성이 줄어듭니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) 16진수 변환: `read_number` 함수 로직이 일반적인 N진법 변환(`ans = ans*16 + digit`)과 달라 가독성이 낮고, 마지막 자릿수 처리가 분리되어 실수하기 쉽습니다.
- 2) K번째 큰 수 찾기: `set`은 오름차순이므로 K번째 큰 수는 `size() - K` 인덱스에 해당합니다. `prev(it)`를 K번 반복하는 현재 방식도 동작하지만, `vector`로 변환 후 인덱스로 접근하는 것이 더 명확합니다.
- 3) 전역 변수 상태: `digit` 벡터가 전역 변수라 테스트케이스 간 상태 공유 위험이 있습니다. `resize`로 문제는 없지만, 지역 변수로 바꾸는 것이 더 안전한 구조입니다.

## 즉시 수정 액션(최대 4개)
- 1. (`read_number` 대체) `string`과 `substr`, `stoi(hex_str, nullptr, 16)`을 사용해 16진수 변환 로직을 표준 라이브러리 호출로 바꾸세요.
- 2. (K번째 원소 접근) `set`을 `vector`로 복사한 뒤 `v[v.size() - K]`와 같이 인덱스로 K번째 큰 수를 찾으세요.
- 3. (전역 변수 지양) `digit` 벡터를 `main` 함수 내 지역 변수로 선언해 명확성을 높이세요.
- 4. (입출력 통일) `printf` 대신 `cout`을 사용하여 C++ 입출력 스타일을 일관되게 유지하세요.

```REVIEW_EXAMPLE
# 제목: `std::string`과 `stoi`를 활용한 풀이 스케치
- 적용 조건: 현재 풀이보다 코드를 간결하고 안전하게 만들고 싶을 때.
- 핵심 아이디어: 원본 16진수 입력을 `string`으로 받은 후, `rotate`로 회전시키며 `substr`로 각 변의 문자열을 잘라냄. `stoi(hex_str, nullptr, 16)`를 이용해 10진수로 변환.
- 복잡도: O(N^2) (시간 복잡도는 동일)
- 구현 스케치:
  ```cpp
  // ... main 함수 및 test_case 반복문 내 ...
  int N, K;
  string s;
  cin >> N >> K >> s;
  
  set<int> numbers;
  int side_len = N / 4;
  
  for (int i = 0; i < side_len; ++i) {
      for (int j = 0; j < 4; ++j) {
          string sub = s.substr(j * side_len, side_len);
          numbers.insert(stoi(sub, nullptr, 16));
      }
      // 시계방향 회전은 문자열의 좌측 shift와 동일
      rotate(s.begin(), s.begin() + 1, s.end());
  }
  
  vector<int> result(numbers.begin(), numbers.end());
  cout << "#" << test_case << " " << result[result.size() - K] << "\n";
  ```
```