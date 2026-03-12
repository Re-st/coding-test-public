def solution(N, number):
    # answer = 1
    # covered = [{}, {N}]
    # if number == N:
    #     return answer
    answer = 0
    covered = [{}]
    while True:
        answer += 1
        if answer > 8:
            return -1
        newfinds = {(10**answer - 1) * N / 9}
        for i in range(1, answer):
            for a in covered[i]:
                for b in covered[answer - i]:
                    newfinds.update([a + b, a - b, a * b, a // b, \
                                    b - a, b // a])
        if number in newfinds:
            return answer
        if 0 in newfinds:
            newfinds.remove(0)
        covered.append(newfinds)
        
        
    return answer