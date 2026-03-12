def solution(n, edge):
    queue = []
    di = [-1] * n
    queue.append(1)
    di[0] = 0
    injub = [[] for _ in range(n)]
    for a, b in edge:
        injub[a - 1].append(b)
        injub[b - 1].append(a)
    while queue:
        elt = queue.pop(0)
        print(elt)
        n = di[elt - 1]
        for b in injub[elt - 1]:
            if di[b - 1] == -1:
                di[b - 1] = n + 1
                queue.append(b)                
            
    print(di)
    maxval = max(di)
    answer = 0
    for i in di:
        if i == maxval:
            answer += 1

    return answer