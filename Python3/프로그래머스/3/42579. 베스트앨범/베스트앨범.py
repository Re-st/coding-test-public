from collections import defaultdict
def solution(genres, plays):
    answer = []
    genreCount = defaultdict(int)
    genreBest = defaultdict(list)
    for i, (g, p) in enumerate(zip(genres, plays)):
        genreCount[g] += p
        genreBest[g].append((p, i))
        genreBest[g].sort(key=lambda x: (-x[0], x[1]))
        genreBest[g] = genreBest[g][:2]
    print(genreCount, genreBest)
    bestGenres = [(v, k) for k, v in genreCount.items()]
    bestGenres.sort(reverse=True)
    print(bestGenres)
    for _, g in bestGenres:
        answer.extend([i for _, i in genreBest[g]])
    return answer