def solution(coin, cards):
    n = len(cards)
    cards = [v - 1 for v in cards]
    answer = 0
    idx = int(n/3)
    hand = [False] * n
    maybuy = [False] * n
    for i in range(int(idx)):
        hand[cards[i]] = True
    while True:
        answer += 1
        if idx == n:
            return answer
        maybuy[cards[idx]] = True
        maybuy[cards[idx + 1]] = True
        idx += 2
        togo = True
        for i in range(int(n/2)):
            if hand[i] and hand[n - 1 - i]:
                print(f"use {i + 1} and {n - i} from hands")
                hand[i] = False
                hand[n - 1 - i] = False
                togo = False
                break
        if togo and coin:
            for i in range(n):
                if hand[i] and maybuy[n - 1 - i]:
                    print(f"use {i + 1} and {n - i}")
                    hand[i] = False
                    maybuy[n - 1 - i] = False
                    togo = False
                    coin -= 1
                    break
        if togo and coin > 1:
            for i in range(int(n/2)):
                if maybuy[i] and maybuy[n - 1 - i]:
                    print(f"use {i + 1} and {n - i}")
                    maybuy[i] = False
                    maybuy[n - 1 - i] = False
                    togo = False
                    coin -= 2
                    break
        if togo:
            print("unused coins ", coin)
            print(maybuy)
            return answer
            
    return answer