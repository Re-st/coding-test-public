def solution(n, computers):
    answer = 0
    visited = [False] * n
    for i in range(n):
        if visited[i]:
            continue
        answer += 1
        queue = [i]
        while queue:
            a = queue.pop()
            for j in range(i + 1, n):
                if not visited[j] and computers[a][j]:
                    queue.append(j)
                    visited[j] = True
            
    return answer