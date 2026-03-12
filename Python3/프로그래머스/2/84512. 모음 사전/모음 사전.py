def solution(word):
    words = {""}
    for _ in range(5):
        words = {w + new for new in ['A', 'E', 'I', 'O', 'U', ''] for w in words}
    words = sorted(list(words))
    answer = 0
    return words.index(word)