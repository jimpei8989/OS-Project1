import numpy as np

allErrors = {}

with open('evaluation/result.txt') as f:
    data = f.readlines()
    for i in range(len(data) // 3):
        aaa = data[i * 3].split()
        bbb = data[i * 3 + 1].split()
        ccc = data[i * 3 + 2].split()
        name=f'{aaa[1]}_{aaa[2]}'
        absError = float(bbb[-1])
        relError = float(ccc[-1])

        allErrors[name] = absError, relError

with open('evaluation/all-error.md', 'w') as f:
    print('| Testcase | Absolute Error | Relative Error (%) |', file = f)
    print('| :------: | :------------: | :----------------: |', file = f)
    for name, (a, b) in allErrors.items():
        print(f'| {name} | {a:9.5f} | {100 * b:.5f} |', file = f)
    absErrs = [a for name, (a, b) in allErrors.items()]
    relErrs = [b for name, (a, b) in allErrors.items()]
    print(f'| **Overall** | **{np.mean(absErrs):9.5f}** | **{np.mean(relErrs) * 100:.5f}** |', file = f)



