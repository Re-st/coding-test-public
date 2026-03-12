def solution(array, commands):
    answer = [sorted(array[a - 1:b])[c - 1] for a, b, c in commands]
    return answer