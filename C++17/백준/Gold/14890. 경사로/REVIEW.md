# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Gold/14890. 경사로/경사로.cc`

## 한 줄 결론
- **구현(시뮬레이션)** / 복잡도: O(N^2) / 인덱스 기반의 압축적인 로직이 매우 영리하지만, 사소한 실수에 치명적일 수 있는 위험한 풀이입니다.

## 더 빠른/더 안전한 풀이(필수)
- 아이디어: `bool installed[101]` 배열로 각 길마다 경사로 설치 여부를 명시적으로 기록하면, 중복 설치나 복잡한 인덱스 계산 없이 훨씬 안전하고 명확하게 조건을 검사할 수 있습니다.
- 복잡도: O(N^2) (동일)
- 왜 이게 더 좋은지: 현재 풀이는 버그가 발생했을 때 원인 파악이 매우 어렵습니다. `installed` 배열을 쓰는 방식은 문제의 제약조건(평평함, 중복 불가)을 코드로 직접 표현하므로, 더 직관적이고 버그 발생 가능성이 낮습니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) **가독성/유지보수성**: `j - lastdown < 2*l`과 같은 인덱스 연산은 오르막/내리막 경사로 간의 중첩 여부를 암시적으로 계산합니다. 이 로직은 매우 압축적이지만, 의도를 파악하기 어렵고 사소한 오타가 치명적인 버그로 이어지기 쉽습니다.
- 2) **암시적 로직**: '경사로를 놓을 바닥이 평평한가'라는 핵심 조건을 별도 반복문으로 확인하지 않고, `j - lastup` 같은 변수 간의 거리로 간접적으로 확인하고 있습니다. 이는 영리하지만, 코드를 처음 보는 사람은 로직을 이해하고 정확성을 검증하기 매우 어렵습니다.
- 3) 자료구조/성능 함정: `passable` 함수에 `vector`를 값으로 전달(`passable(vector<short> m)`)하고 있습니다. N이 100일 때 200번의 호출마다 벡터 전체가 복사되어 불필요한 오버헤드가 발생합니다.

## 즉시 수정 액션(최대 4개)
- 1. **(강력 권장)** `passable` 함수를 `bool installed[101]` 배열을 사용하는 방식으로 재작성하여 안정성과 가독성을 확보하세요.
- 2. 함수 인자를 `passable(const vector<short>& m)`으로 변경하여 불필요한 벡터 복사를 방지하세요.
- 3. `lastup`, `lastdown` 같은 변수명을 `flat_section_start_idx` 등으로 더 명확하게 하거나 주석을 추가하여 코드의 의도를 명확히 하는 것을 고려해 보세요.
- 4. `main` 함수에서 전치 행렬 `mt`를 만드는 대신, 열을 순회하는 반복문으로 대체하면 메모리를 절약할 수 있습니다.

```REVIEW_EXAMPLE
# 제목: 경사로 설치 여부를 명시적으로 추적하는 안전한 풀이
- 적용 조건: 현재 풀이의 로직이 너무 복잡하여 디버깅이 어렵거나, 실수를 줄이고 싶을 때 항상 유리합니다.
- 핵심 아이디어: 각 행/열을 검사할 때마다 `bool installed[101]` 배열을 사용합니다. 경사로를 놓을 때, (1) L칸이 평평한지, (2) 이미 다른 경사로가 없는지 `installed` 배열로 확인 후, 설치 위치를 `true`로 표시합니다.
- 복잡도: O(N^2)
- 구현 스케치(C++):
bool is_passable(const vector<short>& path) {
    bool installed[101] = {false};
    for (int i = 0; i < n - 1; ++i) {
        int diff = path[i] - path[i+1];
        if (abs(diff) > 1) return false;

        if (diff == 1) { // 내리막 경사로: [i+1, ..., i+L]에 설치
            if (i + l >= n) return false;
            for (int j = i + 1; j <= i + l; ++j) {
                if (path[j] != path[i+1] || installed[j]) return false;
                installed[j] = true;
            }
        } else if (diff == -1) { // 오르막 경사로: [i-L+1, ..., i]에 설치
            if (i - l + 1 < 0) return false;
            for (int j = i; j >= i - l + 1; --j) {
                if (path[j] != path[i] || installed[j]) return false;
                installed[j] = true;
            }
        }
    }
    return true;
}
```