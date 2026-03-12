def solution(cap, n, deliveries, pickups):
    answer = 0
    while deliveries and not deliveries[-1]:
        deliveries.pop()
    while pickups and not pickups[-1]:
        pickups.pop()
    while deliveries or pickups:
        answer += 2 * max(len(deliveries), len(pickups))
        newcap = cap
        while deliveries:
            newcap -= deliveries.pop()
            if newcap < 0:
                deliveries.append(-newcap)
                break
        newcap = cap
        while pickups:
            newcap -= pickups.pop()
            if newcap < 0:
                pickups.append(-newcap)
                break
    return answer