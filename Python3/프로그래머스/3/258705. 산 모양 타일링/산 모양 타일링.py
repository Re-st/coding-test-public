def solution(n, tops):

    MOD = 10007

    withm = [0] * (n + 1)
    wom = [0] * (n + 1)
    if tops[0]:
        wom[1] = 3
    else:
        wom[1] = 2
    withm[1] = 1

    for i in range(2, n + 1):
        withm[i] = withm[i - 1] + wom[i - 1]
        if tops[i - 1]:
            wom[i] = withm[i - 1] * 2 + wom[i - 1] * 3
        else:
            wom[i] = withm[i - 1] + wom[i - 1] * 2
        withm[i] %= MOD
        wom[i] %= MOD
    return (withm[n] + wom[n]) % MOD