def toDate(date: str) -> int:
    y, m, d = map(int, date.split('.'))
    return y * 28 * 12 + m * 28 + d

def solution(today, terms, privacies):
    termMap = {x[0]: int(x[1]) for x in [x.split() for x in terms]}
    today = toDate(today)
    answer = [i + 1 for i, p in enumerate(privacies) if toDate(p[:-2]) + termMap[p[-1]] * 28 <= today]
    return answer