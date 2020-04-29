mkdir -p theoretical-output

policies=("FIFO" "RR" "SJF" "PSJF")

for policy in ${policies[@]}; do
    for i in {1..5}; do
        tmp=$(printf "%-4s" $policy)
        # echo "------ ${tmp}_${i} ------"
        python3 evaluation/diff.py ${policy}_${i}
    done
done

