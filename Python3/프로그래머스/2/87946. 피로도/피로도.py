from itertools import permutations

def solution(k, dungeons):
    answer = -1
    for perm in permutations(dungeons, len(dungeons)):
        cnt = 0
        health = k
        for dun in perm:
            if health < dun[0]:
                break
            else:
                cnt += 1
                health -= dun[1]
        answer = max(answer, cnt)
    return answer