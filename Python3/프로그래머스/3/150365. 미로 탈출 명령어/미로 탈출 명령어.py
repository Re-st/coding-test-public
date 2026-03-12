def solution(n, m, x, y, r, c, k):
    # down, left, right, up
    # dddllllll
    if (x + y - r - c - k) % 2:
        return 'impossible'
    if (x + y - r - c - k) > 0:
        return 'impossible'
    answer = ''
    downpoint = r - x
    leftpoint = y - c
    while abs(downpoint) + abs(leftpoint) < k:
        # can do what we want
        if x < n:
            answer += 'd'
            downpoint -= 1
            x += 1
        elif y > 1:
            answer += 'l'
            leftpoint -= 1
            y -= 1
        else:
            answer += 'r'
            leftpoint += 1
            y += 1
        k -= 1
    # finish
    if downpoint > 0:
        answer += 'd' * downpoint
        downpoint = 0
    if leftpoint > 0:
        answer += 'l' * leftpoint
    else:
        answer += 'r' * (-leftpoint)
    answer += 'u' * (-downpoint)
    return answer