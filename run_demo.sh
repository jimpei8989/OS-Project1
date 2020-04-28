CYAN="\x1b[1;36m"
YELLOW="\x1b[1;33m"
CLEAR="\x1b[0m"

tasks=('TIME_MEASUREMENT' 'FIFO_1' 'PSJF_2' 'RR_3' 'SJF_4')

for task in ${tasks[@]}; do
    echo -e "${CYAN}=> ${task}${CLEAR}"
    echo -e "${YELLOW}sudo dmesg -C${CLEAR}"
    sudo dmesg -C

    echo -e "${YELLOW}sudo ./scheduler < testdata/${task}.txt ${CLEAR}"
    sudo ./scheduler < testdata/${task}.txt

    echo -e "${YELLOW}sudo dmesg -t | grep Project1${CLEAR}"
    sudo dmesg -t | grep Project1
done

