function make_for() {
    echo "=================="
    echo "Making $1"
    echo "=================="
    mkdir -p build-$1
    cd build-$1
    cmd="cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_QJS_LIBC=OFF -DPLATFORM=$2 -DRETRO68_ROOT=$RETRO68_TOOLCHAIN_PATH -DCMAKE_TOOLCHAIN_FILE=$RETRO68_INSTALL_PATH/cmake/$2.toolchain.cmake.in"
    cmd2="make -j$(nproc)"
    $cmd && $cmd2
    status=$?
    cd .. 
    return $status
}

make_for "68k" "retro68" && make_for "PowerPC" "retroppc"