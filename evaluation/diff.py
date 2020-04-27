import sys

def mean(l):
    return sum(l) / len(l)

def main():
    if len(sys.argv) != 5:
        print('usage:\tpython3 diff.py measurement.txt theoretical.txt stdout.txt dmesg.txt')
        exit(0)

    measurement = sys.argv[1]
    theoretical = sys.argv[2]
    stdout = sys.argv[3]
    dmesg = sys.argv[4]

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
            name = PID2name[PID]
            realTime[name] = float(start), float(end)

    losses = []
    lossPercent = []
    begin = realTime[P0][0] - theoreticalTime[P0][0] * UNIT
    for pid, (s, e) in realTime.items():
        s = (s - begin) / UNIT
        e = (e - begin) / UNIT

        ts, te = theoreticalTime[pid]
        loss = abs(ts - s) + abs(te - e)
        losses.append(loss)
        lossPercent.append(loss / te)

        #  print(s, e, ts, te)

    print('Average absolute error:', mean(losses))
    print('Average relative error (%):', mean(lossPercent))

if __name__ == '__main__':
    main()

