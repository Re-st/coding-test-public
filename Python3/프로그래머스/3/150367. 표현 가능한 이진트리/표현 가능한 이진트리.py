def binary(num):
    k = 1
    while (1 << ((1 << k) - 1)) - 1 < num:
        k += 1
    return ((1 << (k - 1)) - 1, [1 if num & (1 << i) else 0 for i in range((1 << k) - 1)][::-1])

def able(middle, numlist):
    if not numlist.count(1):
        return 1
    elif not numlist[middle]:
        return 0
    else:
        return able(middle // 2, numlist[:middle]) and able(middle // 2, numlist[middle + 1:])
        
        
def solution(numbers):
    return [able(v[0], v[1]) for v in map(binary, numbers)]
