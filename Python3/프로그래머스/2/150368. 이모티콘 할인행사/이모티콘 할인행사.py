from itertools import product
def solution(users, emoticons):
    emoticons = [e // 100 for e in emoticons]
    answer = []
    ne = len(emoticons)
    static_dcs = [[40, 30, 20, 10] for _ in range(ne)]
    for discounts in product(*static_dcs):
        membercount = 0
        moneytotal = 0
        prices = [e * (100 - dc) for (e, dc) in zip(emoticons, discounts)]
        for user in users:
            money = 0
            for i, dc in enumerate(discounts):
                if user[0] <= dc:
                    money += prices[i]
            if money >= user[1]:
                membercount += 1
            else:
                moneytotal += money
        if (membercount, moneytotal) > tuple(answer):
            answer = [membercount, moneytotal]
            
    return answer