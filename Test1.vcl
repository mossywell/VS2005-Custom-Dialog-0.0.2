<html>
<body>
<pre>
<h1>Build Log</h1>
<h3>
--------------------Configuration: Test1 - Win32 (WCE ARMV4) Release--------------------
</h3>
<h3>Command Lines</h3>
Creating command line "rc.exe /l 0x409 /fo"ARMV4Rel/Test1.res" /d UNDER_CE=420 /d _WIN32_WCE=420 /d "NDEBUG" /d "UNICODE" /d "_UNICODE" /d "WIN32_PLATFORM_WFSP=200" /d "ARM" /d "_ARM_" /d "ARMV4" /r "C:\Apps\Test11\Test1.rc"" 
Creating temporary file "C:\TEMP\RSP24C1.tmp" with contents
[
/nologo /W3 /D _WIN32_WCE=420 /D "WIN32_PLATFORM_WFSP=200" /D "ARM" /D "_ARM_" /D "ARMV4" /D UNDER_CE=420 /D "UNICODE" /D "_UNICODE" /D "NDEBUG" /Fp"ARMV4Rel/Test1.pch" /YX /Fo"ARMV4Rel/" /O2 /MC /c 
"C:\Apps\Test11\DialogEx.cpp"
"C:\Apps\Test11\Test1.cpp"
]
Creating command line "clarm.exe @C:\TEMP\RSP24C1.tmp" 
Creating temporary file "C:\TEMP\RSP24C2.tmp" with contents
[
commctrl.lib coredll.lib aygshell.lib /nologo /base:"0x00010000" /stack:0x10000,0x1000 /entry:"WinMainCRTStartup" /incremental:no /pdb:"ARMV4Rel/Test1.pdb" /nodefaultlib:"libc.lib /nodefaultlib:libcd.lib /nodefaultlib:libcmt.lib /nodefaultlib:libcmtd.lib /nodefaultlib:msvcrt.lib /nodefaultlib:msvcrtd.lib" /out:"ARMV4Rel/Test1.exe" /subsystem:windowsce,4.20 /align:"4096" /MACHINE:ARM 
.\ARMV4Rel\DialogEx.obj
.\ARMV4Rel\Test1.obj
.\ARMV4Rel\Test1.res
]
Creating command line "link.exe @C:\TEMP\RSP24C2.tmp"
<h3>Output Window</h3>
Compiling resources...
Compiling...
DialogEx.cpp
Test1.cpp
Linking...
Signing C:\Apps\Test11\ARMV4Rel\Test1.exe
Error: Unable to open a CSP provider with the correct private key
Error: Signing Failed.  Result = 80092006, (-2146885626)




<h3>Results</h3>
Test1.exe - 0 error(s), 0 warning(s)
</pre>
</body>
</html>
