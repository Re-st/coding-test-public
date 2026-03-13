# AI 코드 리뷰

- Model: `models/gemini-2.5-pro`
- Source: `./C++17/백준/Gold/3190. 뱀/뱀.cc`

## 한 줄 결론
- (이 문제는) **시뮬레이션** / 복잡도: O(N^2) / `dx, dy` 배열 오류로 뱀이 초기부터 잘못된 방향(아래)으로 이동합니다.

## 더 빠른/더 안전한 풀이(필수)
- 현 접근이 거의 최선입니다. 시뮬레이션 문제의 정석적 풀이로, 뱀의 몸통 충돌을 O(1)에 확인하는 2D 배열과 꼬리/머리 관리에 O(1)인 큐(또는 덱) 사용이 효율적입니다.

## 내가 지금 틀리기 쉬운 포인트 TOP3
- 1) 초기값/시작점/종료조건: 초기 방향은 오른쪽인데, `dx, dy` 배열이 아래쪽으로 이동하도록 잘못 설정되었습니다. `// RDLU` 주석과 실제 `dx, dy` 값이 불일치합니다.
- 2) 인덱스/경계/오버플로/방문처리: 사과 위치 입력(행, 열)을 `apple[열][행]`으로 저장하고, 뱀 위치 변수 `x,y`의 의미가 불분명해 좌표계 혼동 위험이 매우 큽니다.
- 3) 자료구조/성능 함정: 방향 전환 정보 저장을 위해 `char d[10001]` 배열을 사용했는데, X의 최댓값이 10000이라 유효합니다. 다만 `queue<pair<int, char>>`로 관리하면 메모리를 더 효율적으로 사용할 수 있습니다.

## 즉시 수정 액션(최대 4개)
1.  `x, y`를 `row, col`로 명확히 하고, `board[row][col]` 형태로 일관되게 접근하세요.
2.  오른쪽부터 시계방향으로 방향 벡터를 수정하세요: `const int dr[] = {0, 1, 0, -1};`, `const int dc[] = {1, 0, -1, 0};` (우, 하, 좌, 상)
3.  사과 위치 저장을 `cin >> r >> c; apple[r][c] = true;` 로 수정하여 `(행, 열)` 순서를 준수하세요.
4.  뱀의 몸통 표현에 `std::queue`보다 양쪽에서 삽입/삭제가 용이한 `std::deque`가 더 직관적입니다.

```REVIEW_EXAMPLE
# 제목: 좌표계를 통일한 안전한 풀이 스케치
- 적용 조건: 현재 풀이의 좌표계 혼동 및 방향 버그를 수정할 때 유리합니다.
- 핵심 아이디어: 변수명을 row, col로 명확히 하고, 방향 벡터(dr, dc)와 2차원 배열 접근(board[row][col])을 모두 (행, 열) 기준으로 통일하여 실수를 원천 차단합니다.
- 복잡도: O(N^2) (게임 종료까지의 최대 시간)
- 구현 스케치(선택):
```cpp
// 방향: 0:오른쪽, 1:아래, 2:왼쪽, 3:위
const int dr[] = {0, 1, 0, -1};
const int dc[] = {1, 0, -1, 0};

// ... main 함수 내부 ...
int time = 0, dir = 0; // 초기 방향: 오른쪽
int r = 1, c = 1;      // (행, 열) 좌표계 사용
deque<pair<int, int>> snake;
snake.push_back({r, c});
body[r][c] = true;

while(true) {
    time++;
    int nr = r + dr[dir], nc = c + dc[dir];
    if (nr < 1 || nr > n || nc < 1 || nc > n || body[nr][nc]) break;
    
    r = nr; c = nc;
    snake.push_back({r, c});
    body[r][c] = true;
    
    if (apple[r][c]) {
        apple[r][c] = false;
    } else {
        auto tail = snake.front(); snake.pop_front();
        body[tail.first][tail.second] = false;
    }

    if (d[time] == 'L') dir = (dir + 3) % 4;
    else if (d[time] == 'D') dir = (dir + 1) % 4;
}
cout << time;
```