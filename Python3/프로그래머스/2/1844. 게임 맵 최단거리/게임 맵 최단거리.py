from collections import deque

def solution(maps):
    answer = 1
    robot = (1, 1)
    goal = (len(maps), len(maps[0]))
    if robot == goal:
        return 0
    # add boundary
    maps = [[0] + row + [0] for row in maps]
    maps.insert(0, [0] * len(maps[0]))
    maps.append([0] * len(maps[0]))
    # go
    visited = [[False] * len(maps[0]) for _ in range(len(maps))]
    queue = deque()
    queue.append((1, 1))
    visited[1][1] = True
    while True:
        answer += 1
        newdeque = deque()
        for q in queue:
            for newq in [(q[0] + a, q[1] + b) for a, b in zip([0,0, 1, -1], [1, -1, 0, 0])]:
                if not visited[newq[0]][newq[1]] and maps[newq[0]][newq[1]]:
                    visited[newq[0]][newq[1]] = True
                    newdeque.append(newq)
                    if goal == newq:
                        return answer
        if len(newdeque) == 0:
            return -1
        queue = newdeque
    return answer