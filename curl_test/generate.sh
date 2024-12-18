
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=/Users/abel/vcpkg/scripts/buildsystems/vcpkg.cmake \
-DCMAKE_VERBOSE_MAKEFILE=OFF \
-DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE \
-DCMAKE_C_COMPILER:FILEPATH=/usr/bin/clang -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/clang++ 

# 目标目录
TARGET_DIR="./build"

# 查找包含目标文本的 .cmake 文件
egrep -rl "MacOSX14" "$TARGET_DIR" --include="*.*" | while read -r file; do
  # 替换文本并就地修改
  gsed -i 's#MacOSX14\.5\.sdk#MacOSX15\.1\.sdk#g' "$file"
done
