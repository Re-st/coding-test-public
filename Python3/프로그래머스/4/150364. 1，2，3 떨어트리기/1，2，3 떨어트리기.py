def solution(edges, target):
    # shift indexes of target to 1 right
    target.insert(0, 0)
    answer = []
    n = len(edges) + 1
    tree = [[] for _ in range (n + 1)]
    numChild = [0] * (n + 1)
    currChildIndex = [0] * (n + 1)

    # initialize tree, numChild, and currChildIndex
    for [a, b] in edges:
        tree[a].append(b)
        numChild[a] += 1

    for v in range(1, n + 1):
        if numChild[v] != 0:
            tree[v].sort()
            currChildIndex[v] = 0
    # fill order and count
    order = []
    count = [0] * (n + 1)
    while not all([count[v] * 3 >= target[v] for v in range(1, n + 1)]):
        v = 1
        while numChild[v] != 0:
            newv = tree[v][currChildIndex[v]]
            currChildIndex[v] = (currChildIndex[v] + 1) % numChild[v]
            v = newv
        order.append(v)
        count[v] += 1
        if count[v] > target[v]:
            return [-1]

    # fill answer
    for currLeaf in order:
        count[currLeaf] -= 1
        countVMax = count[currLeaf] * 3
        targetV = target[currLeaf]
        if countVMax >= targetV - 1:
            answer.append(1)
            target[currLeaf] -= 1
        elif countVMax >= targetV - 2:
            answer.append(2)
            target[currLeaf] -= 2
        else:
            answer.append(3)
            target[currLeaf] -= 3

    return answer