<table border="0">
  <tr>
    <td>
      <img style='width: 100%;' src="https://github.com/IoIxD/os9fetch/assets/30945097/42485293-4dd1-46f8-902e-35bee0be846f">
      <img style='width: 100%;' src="https:// github.com/IoIxD/os9fetch/assets/30945097/63c0a87f-431a-4ffb-ab06-d37836cbf0f0">
     </td>
     <td width="30%">
       <h1>os9fetch</h1>
       <p>Neofetch clone for Classic Mac based computers, so that you can show off your Macs in the same endearingly stupid way that modern Linux users get to! Despite it's namesake, it can be run going back to System 4.0, on both PowerPC and 68k!</p>
     </td>
      
  </tr>
</table>

# Compiling

Install [Retro68](https://github.com/autc04/Retro68), then set `$RETRO68_TOOLCHAIN_PATH` to your toolchain path and `$RETRO68_INSTALL_PATH` to the path of the cloned repo. Then, run `build.sh` to build for both 68k and PowerPC. 

The resulting file will be the stuffit file `os9fetch.bin` in either the `build-68k` or `build-PowerPC` folder.
