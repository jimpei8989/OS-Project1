# Operating Systems - Project 1

###### By: Wu-Jun Pei (B06902029)

### Useful Links

- Project Spec: <https://hackmd.io/@Ue96nvjESj2XsDXw532-qA/ryYqceUrU>
- Due: <font color="red">**2020/04/29 (Wed.) 23:59 **</font>

## Scheduler

#### Compilication
```bash
make
```

#### Execute

```bash
./scheuler
```

#### Run All

```bash
bash run.sh
```

- 執行所有 testdata

#### Run Demo

```bash
bash run_demo.sh
```

- 執行所有 demo 的 input，並將執行指令印出。
- 使用螢幕錄影，結果放置於 `demo/demo.mp4`

## Evaluation

#### Calculate Theoretical Output

```bash
python3 evaluation/theoretial.output
```
#### Calculate Error

```bash
python3 evaluation/diff.py POLICY_ID		# Lists the errors
python3 evaluation/diff-show.py POLICY_ID	# Draws a md table and a barh
```

