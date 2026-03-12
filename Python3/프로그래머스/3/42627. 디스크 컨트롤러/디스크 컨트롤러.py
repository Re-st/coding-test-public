def solution(jobs):
    jobs = sorted(jobs, key = lambda x:x[1])
    time = 0
    total = 0
    length = len(jobs)
    for _ in range(length):
        breaking = False
        while True:
            for start, duration in jobs:
                if start <= time:
                    time += duration
                    total += time - start
                    breaking = True
                    break
            if breaking:
                break
            time += 1
        jobs.remove([start, duration])
    return (total / length) // 1
    answer = 0
    return answer