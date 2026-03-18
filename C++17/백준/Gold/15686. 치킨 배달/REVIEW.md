# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Gold/15686. 치킨 배달/치킨 배달.cc`

## 한 줄 결론
- (이 문제는) **백트래킹(조합)** / 복잡도: O((C choose M) * H * M) / 재귀 호출 시 `set`을 값으로 전달하여 발생하는 비효율이 가장 위험합니다.

## 더 빠른/더 안전한 풀이(필수)
- 현 접근이 거의 최선입니다. M개의 치킨집을 고르는 조합 문제를 백트래킹으로 탐색하는 정석적인 풀이입니다. 다만, 조합을 생성하는 재귀함수 구현을 더 효율적으로 개선할 수 있습니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) **자료구조/성능 함정**: `dfs` 함수에 `set<int> acc`를 값으로 전달하면, 재귀 호출마다 set 전체가 복사되어 상당한 성능 저하가 발생합니다.
- 2) **백트래킹 구현**: 현재는 상태(선택된 치킨집)를 복사해서 다음 재귀로 넘기고 있습니다. `vector`를 참조로 넘기고 원소를 추가(`push_back`)/제거(`pop_back`)하는 표준적인 백트래킹 방식이 훨씬 효율적입니다.
- 3) **DFS 시작/종료 로직**: `main`의 루프와 `dfs`의 `m-1` 방식은 동작하지만, `dfs(0, ...)`으로 시작해 선택한 개수가 `m`개가 될 때를 종료 조건으로 삼는 단일 진입점 구조가 더 간결하고 일반적입니다.

## 즉시 수정 액션(최대 4개)
- 1. `dfs` 시그니처를 `void dfs(int start_idx, vector<int>& selected)` 와 같이 변경하세요.
- 2. `set` 대신 `vector`를 참조(`&`)로 전달해 복사 비용을 없애세요.
- 3. 재귀 호출 시 `selected.push_back(i); dfs(i + 1, selected);` 후, `selected.pop_back();` 으로 상태를 되돌리는 백트래킹 로직을 적용하세요.
- 4. `dfs`의 종료 조건을 `if (selected.size() == m)` 으로 명확하게 변경하세요.

```REVIEW_EXAMPLE
# 제목: 더 효율적인 백트래킹(조합) 구현
- 적용 조건: 현재 풀이처럼 재귀로 조합을 구할 때, 상태(선택된 목록) 복사 없이 관리하여 성능을 높이고 싶을 경우.
- 핵심 아이디어: `vector`를 참조로 전달하고, 재귀 진입 전에 원소를 추가(`push_back`), 재귀 탈출 후 원소를 제거(`pop_back`)하여 상태를 되돌립니다.
- 복잡도: O((C choose M) * H * M) (복잡도는 동일하나, 재귀 호출당 상수 시간(복사 비용)이 크게 줄어 실질적 속도 향상)
- 구현 스케치(C++):
```cpp
vector<int> selected_indices; // 선택된 치킨집 인덱스 저장

void dfs(int start_idx) {
    // 1. 종료 조건: M개를 모두 선택한 경우
    if (selected_indices.size() == m) {
        int city_dist = 0;
        for (int i = 0; i < house.size(); ++i) {
            int house_dist = INT_MAX;
            for (int idx : selected_indices) {
                house_dist = min(house_dist, dist[i][idx]);
            }
            city_dist += house_dist;
        }
        ans = min(ans, city_dist);
        return;
    }

    // 2. 재귀 호출: 다음 치킨집 선택
    for (int i = start_idx; i < chicken.size(); ++i) {
        selected_indices.push_back(i);    // 선택
        dfs(i + 1);                       // 다음 원소 탐색
        selected_indices.pop_back();      // 복구 (백트래킹)
    }
}

// main 함수에서 호출:
// dfs(0);
```
```