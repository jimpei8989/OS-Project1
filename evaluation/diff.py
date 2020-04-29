import sys

def mean(l):
    return sum(l) / len(l)

def main():
    name = sys.argv[1]

    measurement = 'output/TIME_MEASUREMENT_dmesg.txt'
    theoretical = f'theoretical-output/{name}_stdout.txt'
    stdout = f'output/{name}_stdout.txt'
    dmesg = f'output/{name}_dmesg.txt'

    # calculate unit time
    with open(measurement) as f:
        UNIT = mean(list(map(lambda k : float(k[3]) - float(k[2]), map(lambda s : s.split(), f.readlines())))) / 500

    # name <-> PID
    with open(stdout) as f:
        name2PID, PID2name = dict(), dict()
        for a, b in map(lambda s : s.split(), f.readlines()):
            name2PID[a] = b
            PID2name[b] = a

    # theoretical output
    with open(theoretical) as f:
        theoreticalTime = dict()
        for a, b, c in map(lambda s : s.split(), f.readlines()):
            theoreticalTime[a] = int(b), int(c)

    P0 = None
    for p in theoreticalTime:
        if P0 is None or theoreticalTime[P0][0] > theoreticalTime[p][0]:
            P0 = p

    # Calculate 
    with open(dmesg) as f:
        realTime = dict()
        for _, PID, start, end in map(lambda s : s.split(), f.readlines()):
            n = PID2name[PID]
            realTime[n] = float(start), float(end)

    losses = []
    lossPercent = []

    blahes = []
    blahPercent = []

    begin = realTime[P0][0] - theoreticalTime[P0][0] * UNIT
    for pid, (s, e) in realTime.items():
        s = (s - begin) / UNIT
        e = (e - begin) / UNIT

        ts, te = theoreticalTime[pid]
        loss = abs(ts - s) + abs(te - e)
        losses.append(loss)
        lossPercent.append(loss / te)

        bb = abs((te - ts) - (e - s))
        blahes.append(bb)
        blahPercent.append(bb / (te - ts))

    print(name, mean(losses), mean(lossPercent), mean(blahes), mean(blahPercent))

if __name__ == '__main__':
    main()

