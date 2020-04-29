import numpy as np

allErrors = {}

with open('evaluation/result.txt') as f:
    for line in f.readlines():
        line = line.split()
        name = line[0]
        errs = list(map(float, line[1:]))
        allErrors[name] = errs

with open('evaluation/all-error.md', 'w') as f:
    print('| Testcase | Timestamp Error<br>Absolute Error | Timestamp Error<br>Relative Error (%) | Turnaround Error<br>Absolute Error | Turnaround Error<br>Relative Error (%) |', file = f)
    print('| :------: | :------------: | :----------------: | :---:| :---: |', file = f)
    for name, (a, b, c, d) in allErrors.items():
        print(f'| {name} | {a:9.5f} | {100 * b:.5f} | {c:9.5f} | {100*d:9.5f} |', file = f)

    absErrs = [a for name, (a, b, c, d) in allErrors.items()]
    relErrs = [b for name, (a, b, c, d) in allErrors.items()]
    tabsErrs = [c for name, (a, b, c, d) in allErrors.items()]
    trelErrs = [d for name, (a, b, c, d) in allErrors.items()]

    print(f'| **Overall** | **{np.mean(absErrs):9.5f}** | **{np.mean(relErrs) * 100:.5f}** | **{np.mean(tabsErrs):9.5f}** | **{np.mean(trelErrs) * 100:.5f}** |', file = f)

