import sys
import numpy as np
import matplotlib.pyplot as plt

COLORS = ['#31a769', '#33ae87', '#36b5a8', '#38afbd', '#3a99c4', '#3d81cb', '#3f67d2']
_COLORS = ['#51c789', '#53cea7', '#56d5c8', '#58cfdd', '#5ab9e4', '#5da1eb', '#5f87f2']

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

    result = []
    begin = realTime[P0][0] - theoreticalTime[P0][0] * UNIT
    for p, (s, e) in realTime.items():
        s = (s - begin) / UNIT
        e = (e - begin) / UNIT

        ts, te = theoreticalTime[p]
        loss = abs(ts - s) + abs(te - e)

        result.append((p, ts, te, s, e))


    result.sort()
    print('| Name | Theo. Start Time | Theo. End Time | Real Start Time | Real End Time |')
    print('| :--: | :--------------: | :------------: | :-------------: | :-----------: |')
    for line in result:
        print('| ' + ' | '.join(map(lambda k : k if isinstance(k, str) else f'{k:.5f}', line)) + ' |')

    print(f'![](demo/{name}.png)')

    N = len(result)

    # Handle 
    lefts = [p[1] for p in result] + [p[3] for p in result]
    widths = [p[2] - p[1] for p in result] + [p[4] - p[3] for p in result]
    labels = [p[0] for p in result] + [p[0] for p in result]
    colors = _COLORS[:N] + COLORS[:N]

    ys = list(np.arange(N) + 1) + list(-N + np.arange(N))

    plt.grid(axis = 'y')
    plt.barh(y = ys, left = lefts, width = widths, height = 0.6, tick_label = labels, color = colors)
    plt.title(name)
    plt.xlabel('Timeline (Unit time)')
    plt.ylabel('Processes')

    plt.savefig(f'demo/{name}.png')

if __name__ == '__main__':
    main()

