def solution(brown, yellow):
    wPlusH = brown // 2 + 2
    for h in range(1, wPlusH):
        if brown + yellow == h * (wPlusH - h):
            return [wPlusH - h, h]