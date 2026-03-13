# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Platinum/1854. K번째 최단경로 찾기/K번째 최단경로 찾기.cc`

## 한 줄 결론
- (이 문제는) **다익스트라 변형** / 복잡도: O(MK log(MK)) / 제일 위험한 실수: 불필요한 경로 탐색

## 더 빠른/더 안전한 풀이(필수)
- 현 접근이 거의 최선입니다. K번째 최단경로 문제는 다익스트라를 변형하여 각 노드마다 K개의 최단 경로 후보를 유지하는 방식이 표준 풀이이며, 시간 복잡도상 더 개선하기 어렵습니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) 초기값/시작점/종료조건: `ans[1].push(0)`와 `pq.push({0, 1})`로 시작점을 올바르게 초기화했습니다. 만약 이 부분이 누락되면 알고리즘이 동작하지 않습니다.
- 2) 인덱스/경계/오버플로/방문처리: 경로 비용이 계속 누적되므로 `new_dist`가 `int` 범위를 초과할 수 있습니다. (예: 긴 사이클을 k번 순회). `long long` 사용이 안전합니다.
- 3) 자료구조/성능 함정: `pq`에서 꺼낸 경로 `(cost, node)`가, 이미 `ans[node]`에 저장된 k번째 경로보다 길다면 더 탐색할 가치가 없습니다. 이 가지치기(pruning) 로직이 없어 불필요한 연산이 발생합니다.

## 즉시 수정 액션(최대 4개)
1.  **조기 중단 최적화:** `pq`에서 원소를 꺼낸 직후, 현재 경로가 해당 노드의 k번째 최단경로보다 길면 즉시 건너뛰도록 코드를 추가하세요. 성능 향상에 결정적입니다.
    ```cpp
    edge cur = pq.top();
    pq.pop();
    // 이 노드의 k번째 경로보다 긴 경로에서는 탐색을 중단
    if (ans[cur.second].top() < cur.first) continue; 
    ```
2.  **경로 비용 타입 변경:** 오버플로 방지를 위해 경로 비용(pair의 첫 번째 값)을 `long long`으로 바꾸세요.
    `typedef pair<long long, int> edge;`
3.  **코드 구조 명확화:** `if-else` 블록의 의도를 명확히 하여 가독성을 높이세요.
    ```cpp
    // 현재 코드
    if (ans[b.second].size() < k) {}
    else if (ans[b.second].top() > new_dist) { ans[b.second].pop(); }
    else continue;
    ans[b.second].push(new_dist);
    pq.push({ new_dist, b.second });

    // 추천 구조
    if (ans[b.second].size() < k) {
        ans[b.second].push(new_dist);
        pq.push({new_dist, b.second});
    } else if (ans[b.second].top() > new_dist) {
        ans[b.second].pop();
        ans[b.second].push(new_dist);
        pq.push({new_dist, b.second});
    }
    ```