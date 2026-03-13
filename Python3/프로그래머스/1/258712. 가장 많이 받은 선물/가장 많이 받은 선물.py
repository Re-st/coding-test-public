def solution(friends, gifts):
    n = len(friends)
    A = [[0] * n for _ in range(n)]
    giftRate = [0] * n
    for gift in gifts:
        e = gift.split()
        a = friends.index(e[0])
        b = friends.index(e[1])
        A[a][b] += 1
        giftRate[a] += 1
        giftRate[b] -= 1
        
    newGifts = [0] * n
    for a in range(n):
        for b in range(a):
            if A[a][b] > A[b][a]:
                newGifts[a] += 1
            elif A[a][b] < A[b][a]:
                newGifts[b] += 1
            elif giftRate[a] > giftRate[b]:
                newGifts[a] += 1
            elif giftRate[a] < giftRate[b]:
                newGifts[b] += 1

    answer = max(newGifts)
    return answer