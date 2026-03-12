def solution(begin, target, words):
    di = dict()
    wordlen = len(words[0])
    di[begin] = 0
    for i in words:
        di[i] = 0
    queue = []
    queue.append(begin)
    while queue:
        bigyo = queue.pop(0)
        if bigyo == target:
            break
        n = di[bigyo]
        for word in words:
            cnt = 0
            for (a, b) in zip(word, bigyo):
                if a == b:
                   cnt += 1
            if cnt == wordlen - 1:
                queue.append(word)
                words.remove(word)
                di[word] = n + 1
    try:
        return di[target]
    except:
        return 0
    answer = 0
    return answer