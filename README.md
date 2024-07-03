<table border="0">
  <tr>
    <td><img style='width: 100%;' src="https://github.com/IoIxD/os9fetch/assets/30945097/42485293-4dd1-46f8-902e-35bee0be846f">
     </td>
     <td width="30%">
       <h1>os9fetch</h1>
       <p>Neofetch clone for Classic Mac based computers, so that you can show off your Macs in the same endearingly stupid way that modern Linux users get to! Currently only tested on Mac OS 9, but has been tested going back to Mac OS 7.6. Currently only works on PowerPC computers.</p>
     </td>
      
  </tr>
</table>

# Compiling

Install [Retro68](https://github.com/autc04/Retro68), then set `$RETRO68_TOOLCHAIN_PATH` to your toolchain path and `$RETRO68_INSTALL_PATH` to the path of the cloned repo, then run the following commands:

```
mkdir -p build
cd build
cmake .. -DBUILD_QJS_LIBC=OFF -DRETRO68_ROOT=$RETRO68_TOOLCHAIN_PATH -DCMAKE_TOOLCHAIN_FILE=$RETRO68_INSTALL_PATH/cmake/retroppc.toolchain.cmake.in
make -j$(nproc)
```

The resulting file will be the stuffit file `os9fetch.bin`
