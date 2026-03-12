def solution(participant, completion):
    answer = ''
    participant.sort()
    completion.sort()
    for i, answer in enumerate(participant):
        if i >= len(completion) or completion[i] != answer:
            return answer