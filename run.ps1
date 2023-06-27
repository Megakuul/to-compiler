conan profile detect --force
conan install . --output-folder=build --build=missing
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE="conan_toolchain.cmake" -DCMAKE_BUILD_TYPE=Debug
cmake --build .
.\Debug\to-compiler.exe ..\example\example.tor
cd ..