from math import ceil, sqrt
from itertools import permutations
def solution(numbers):
    MAX_SQRT = 5000
    primeInfo = [True] * MAX_SQRT
    primes = set()
    primeInfo[0] = primeInfo[1] = False
    for p in range(2, MAX_SQRT):
        for q in range(2, int(sqrt(p)) + 1):
            if primeInfo[q] and not p % q:
                primeInfo[p] = False
                break
    primes = [p for p in range(MAX_SQRT) if primeInfo[p]]
    print(primes)
    def isPrime(num):
        if num < MAX_SQRT:
            return primeInfo[num]
        else:
            return all([num % q for q in primes])
    allNums = {
        int(''.join(p)) 
        for length in range(1, len(numbers) + 1) 
        for p in permutations(numbers, length)
    }
    print(allNums)
    answer = sum(isPrime(num) for num in allNums)
    return answer