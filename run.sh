mkdir -p output

function cmpp() {
    a=$(cat $1 | cut -d ' ' -f 1)
    b=$(cat $2 | cut -d ' ' -f 1)
    if [[ $a != $b ]]; then
        echo "diff"
    fi
}

echo "------ TIME MEASUREMENT ------"
./scheduler < testdata/TIME_MEASUREMENT.txt > output/TIME_MEASUREMENT_stdout.txt 2> output/TIME_MEASUREMENT_dmesg.txt

policies=("FIFO" "RR" "SJF" "PSJF")
# policies=("SJF" "PSJF")

for policy in ${policies[@]}; do
    for i in {1..5}; do
        tmp=$(printf "%-4s" $policy)
        echo "------ ${tmp} ${i} ------"
        
        dmesg -C
        ./scheduler < testdata/${policy}_$i.txt > output/${policy}_${i}_stdout.txt
        dmesg -t | grep "Project1" > output/${policy}_${i}_dmesg.txt

        cmpp output/${policy}_${i}_stdout.txt sample-output/${policy}_${i}_stdout.txt
    done
done

