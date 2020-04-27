mkdir -p output

echo "------ TIME MEASUREMENT ------"
./scheduler < testdata/TIME_MEASUREMENT.txt > output/TIME_MEASUREMENT_stdout.txt 2> output/TIME_MEASUREMENT_dmesg.txt

for i in {1..5}; do
    echo "------ FIFO $i ------"
    ./scheduler < testdata/FIFO_$i.txt > output/FIFO_${i}_stdout.txt 2> output/FIFO_${i}_dmesg.txt
done

for i in {1..5}; do
    echo "------ RR $i ------"
    ./scheduler < testdata/RR_$i.txt > output/RR_${i}_stdout.txt 2> output/RR_${i}_dmesg.txt
done

for i in {1..5}; do
    echo "------ SJF $i ------"
    ./scheduler < testdata/SJF_$i.txt > output/SJF_${i}_stdout.txt 2> output/SJF_${i}_dmesg.txt
done

for i in {1..5}; do
    echo "------ PSJF $i ------"
    ./scheduler < testdata/PSJF_$i.txt > output/PSJF_${i}_stdout.txt 2> output/PSJF_${i}_dmesg.txt
done

