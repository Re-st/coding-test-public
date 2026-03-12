def solution(citations):
    answer = 0
    citations.sort(reverse=True)
    while True:
        if answer == len(citations):
            return answer
        if citations[answer] >= answer + 1:
            answer+=1
        else:
            return answer