cd ./tests/source
for file in test*.s; do
    filename="${file%.*}"
    arm-none-eabi-gcc -mbig-endian -c "$file" -o "../$filename.o"
done
cd ../..
for file1 in ./Examples_fusion/file?.o; do
    for file2 in ./Examples_fusion/file?.o; do
        if [ "$file1" != "$file2" ]; then
            ./oracle "$file1" "$file2"
        fi
    done
done
for file1 in ./Examples_fusion/exemple?.o; do
    for file2 in ./Examples_fusion/exemple?.o; do
        if [ "$file1" != "$file2" ]; then
            ./oracle "$file1" "$file2"
        fi
    done
done
for file1 in ./tests/test*; do
        ./oracle "$file1"
done