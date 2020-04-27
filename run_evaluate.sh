mkdir -p theoretical-output

policies=("FIFO" "RR" "SJF" "PSJF")

for policy in ${policies[@]}; do
    for i in {1..5}; do
        tmp=$(printf "%-4s" $policy)
        echo "------ ${tmp} ${i} ------"
        python3 evaluation/diff.py output/TIME_MEASUREMENT_dmesg.txt \
                                   theoretical-output/${policy}_${i}_stdout.txt \
                                   output/${policy}_${i}_stdout.txt \
                                   output/${policy}_${i}_dmesg.txt
    done
done

