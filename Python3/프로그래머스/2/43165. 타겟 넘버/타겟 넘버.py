def solution(numbers, target):
    answer = 0
    # minus할 원소들을 구한다.
    if (sum(numbers) - target) % 2:
        return 0
    goal = (sum(numbers) - target) // 2
    candidates = [0]
    for num in numbers:
        new_cand = []
        for cand in candidates:
            trial = cand + num
            if trial < goal:
                new_cand.append(trial)
            elif trial == goal:
                answer+=1
        candidates += new_cand
    return answer