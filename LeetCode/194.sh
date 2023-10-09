# Read from the file file.txt and print its transposed content to stdout.
n=$(cat file.txt | head -n 1 | wc -w)
for i in $(seq 1 $n); do
    cut -d ' ' -f"$i" file.txt | paste -s -d' ' -
done
