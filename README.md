# Important

## This project is no longer supported.  
Please use the .NET ported version of [ATRACTool Reloaded](https://github.com/XyLe-GBP/ATRACTool-Reloaded) from now on.  
The ported version includes multi-language support, additional functionality and bug fixes.  
This version can still be used, but we are not responsible for any problems that may occur.  

# ATRACTool

![Downloads](https://img.shields.io/github/downloads/XyLe-GBP/ATRACTool/total.svg)
[![GitHub (pre-)release](https://img.shields.io/github/release/XyLe-GBP/ATRACTool/all.svg)](https://github.com/XyLe-GBP/ATRACTool/releases)

Utility tool to convert Sony's ATRAC3/ATRAC3plus/ATRAC9(.AT3/.AT9) to Wave(.WAV) sound.  

Or convert Wave sound to Sony's ATRAC3/ATRAC3plus/ATRAC9.  

User interface functions are provided for SCEI ATRAC3plus Codec Tool (at3tool.exe) and SCEI ATRAC9 Codec Tool (at9tool.exe).

**Download:**
[Release build](https://github.com/XyLe-GBP/ATRACTool/releases)

## Descriptions

This tool uses a multi-threaded(/MT) build, so it can be launched without the Visual C++ redistribution package.

- The SCEI ATRAC3plus Codec TOOL(at3tool.exe) uses <code>MSVCR80.DLL</code>.  

 If you get an error, please install the following package on your PC.

 [Microsoft Visual C++ 2005 SP1 Redistributable Package (x86)](http://www.microsoft.com/ja-jp/download/details.aspx?id=5638)

 [Microsoft Visual C++ 2005 SP1 Redistributable Package (x64)](http://www.microsoft.com/ja-jp/download/details.aspx?id=18471)

- The SCEI ATRAC9 Codec TOOL(at9tool.exe) uses <code>MSVCR90.DLL</code>.  

 If you get an error, please install the following package on your PC.

 [Microsoft Visual C++ 2008 Redistributable Package (x86)](http://www.microsoft.com/ja-jp/download/details.aspx?id=29)

 [Microsoft Visual C++ 2008 Redistributable Package (x64)](http://www.microsoft.com/ja-jp/download/details.aspx?id=15336)

## Details

It is a tool that can decode Sony's ATRAC3/ATRAC3plus/ATRAC9 to Wave sound, and encode Wave sound to ATRAC3/ATRAC3plus/ATRAC9. 

ATRAC3 and ATRAC3plus are mainly used for PSP and PS3, while ATRAC9 is used for PSVita and PS4.

**System**

This application does not work on non-x64 (64 bit) operating systems.  

※This application will not run on non-x64 (64-bit) operating systems. Please note that it cannot run on x86 (32-bit) PCs.  

(Unless you have a very old PC, you should be able to run it.)

## License

MIT
