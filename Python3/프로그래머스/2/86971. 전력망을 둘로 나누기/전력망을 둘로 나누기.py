def solution(n, wires):
    answer = n
    W = [set() for _ in range(n + 1)]
    for w0, w1 in wires:
        W[w0].add(w1)
        W[w1].add(w0)
    for w0, w1 in wires:
        visited = [False] * (n + 1)
        visited[w0] = visited[w1] = True
        neighbor = { w0 }
        cnt = 1
        while not neighbor == set():
            a = neighbor.pop()
            for b in W[a]:
                if not visited[b]:
                    visited[b] = True
                    neighbor.add(b)
                    cnt += 1
        print(w0, w1, cnt)
        answer = min(answer, abs(n - 2 * cnt))
        # python에서 queue 구현법?
    return answer