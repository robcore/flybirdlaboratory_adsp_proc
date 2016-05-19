::****************************************************************
:: Filename: adspcrashman.bat
::
:: Version : External_Release_1.6
::
:: Usage:
:: 	adspcrashman.bat Target_Name[8994/8974/9x25/8x10/9x35/8084] EBI_Binary_File Output_folderpath CRM_Buildpath CustomerprovidedOBJPath[Optional]
::
:: Example:
:: 	adspcrashman.bat 8974 C:\Dropbox\8k_dumps\lpass_crash\dram_0x80000000--0xbfffffff.lst C:\dropbox\123456 C:\YUG_M8960AAAAANAZL1047\lpass_proc ::   C:\Dropbox\8k_dumps\lpass_proc\obj\qdsp6v4_ReleaseG
::
::****************************************************************

@echo off

set Crashman_Version= External_Release_1.6

if not "%1"=="" (
for /f "tokens=1,2 delims=_" %%A in ("%1") do (
set TARGET=%%A
set CR=%%B
)
goto argumentspresent
) else (
echo Usage: adspcrashman.bat Target_Name[8974/9x25/8x10] EBI_Binary_File Output_folderpath CRM_Buildpath CustomerprovidedOBJPath[Optional]
goto endall
)
:argumentspresent


if not "%4"=="" (
goto insufficientarguments
) else (
echo Insufficient Arguments
echo Usage: adspcrashman.bat Target_Name[8974/9x25/8x10] EBI_Binary_File Output_folderpath CRM_Buildpath CustomerprovidedOBJPath[Optional]
goto endall
)
:insufficientarguments
echo ************************************
echo *******Crashman Started*************
echo ************************************
echo Crashman version          :%Crashman_Version%

::echo %curdir%
if not "%CR%"=="" (
set UniqueNumber=%CR%
   if "%CR%"=="X" (
   set UniqueNumber=NoUnique
   )
   if "%CR%"=="x" (
   set UniqueNumber=NoUnique
   )
) else (
set UniqueNumber="NotGiven"
)
set hour=%time:~0,2%
if "%time:~0,1%"==" " set hour=0%time:~1,1%
set datetimef=%date:~4,2%_%date:~-7,2%_%hour%h%time:~3,2%m%time:~6,2%s

::echo %UniqueNumber%

set targetid=%TARGET%
set INDumpPath=%2%
if %UniqueNumber%=="NotGiven" (
set OutPath=%3\Crashman_%datetimef%
) else (
set OUTDumpPath=%3\Crashman_%UniqueNumber%
)
set CRM_buildpath=%4%
if exist %CRM_buildpath%\adsp_proc ( set CRM_buildpath=%CRM_buildpath%\adsp_proc )
set CustomerPath=%5%

set OUTDumpPath=%OutPath%
set OUTDumpPath=%OUTDumpPath%\Logs
mkdir %OUTDumpPath%

set Temp_DIR=C:\Temp
if not exist %Temp_DIR% ( mkdir %Temp_DIR% )

:: to convert windows .dmp/.tmp dump into bin format 
for /F "delims=" %%A in ("%2%") do (
set "FILEEXT=%%~xA"
)
set win=false
if "%FILEEXT%" == ".dmp" (
    set win=true
)
if "%FILEEXT%" == ".tmp" (
    set win=true
)
if "%win%" == "true" (
    dexter.exe /v /i %2 /o %OUTDumpPath% /SelImg /Img1 ADSP
    set INDumpPath=%OUTDumpPath%\ADSP0.bin
) else (
set INDumpPath=%2%
)
set CRM_buildpath=%4%
if exist %CRM_buildpath%\adsp_proc ( set CRM_buildpath=%CRM_buildpath%\adsp_proc )
set CustomerPath=%5%


cd > %OUTDumpPath%\currentdir.txt

for /f "tokens=* delims= " %%v in (%OUTDumpPath%\currentdir.txt) do (
set curdir=%%v%
::echo %curdir%
goto donedir
)
:donedir

set CurrDirectory=%curdir%
if not exist %INDumpPath% ( echo Dump File is not accessible/available. Please Check the File Path.
goto endall
)

::Check perl and python versions
::********************

::Verify Python version
::***********
SET versioncheck=%OUTDumpPath%\version_check.txt
echo Version > %versioncheck%
if not exist %versioncheck% ( echo %OUTDumpPath% is not accessible/available. Please Check the Output Path.
goto endall
)
python Version_Check.py  %versioncheck% 
set PythonVersionStatus=NotRecognized
set PythonVersion=NotRecognized
for /f "tokens=1-5 delims= " %%i in (%versioncheck%) do (
    set PythonVersion=%%m
    if  "%%i" == "Python" (
       set PythonVersionStatus=NotFamiliar
    )	    
)
if  "%PythonVersionStatus%" == "NotRecognized" (
  echo ************************************
  echo ***********  ERROR  ****************
  echo ************************************
  echo Python is not installed in your PC . Please intsall Python.
  echo Recommended Python Installation v2.7.6
  echo Crashman tested on Python versions- v2.7.6  v2.5.2  v2.6.2  v2.7.2  v3.0.1  v2.7.6
  goto endall
)  
for /f "tokens=1-2 delims= " %%i in ('echo  Tested List v2.7.6  v2.5.2  v2.6.2  v2.7.2  v3.0.1  v2.7.6  End  ^| findstr /c:"%PythonVersion%"') do (
    if  "%%i" == "Tested" (
	set PythonVersionStatus=Success	
        echo Python version installed  : %PythonVersion%
    )
)
if "%PythonVersionStatus%" == "NotFamiliar" (
  echo **********  WARNING  ***************
  echo Python version installed : %PythonVersion%
  echo Please update your Python version. Recommended Python Installation v2.7.6
  echo Crashman tested on Python versions- v2.7.6  v2.5.2  v2.6.2  v2.7.2  v3.0.1  v2.7.6
)  

::***********
::Verify Perl version
::***********
set PerlVersionStatus=NotRecognized
set PerlVersion=NotRecognized

for /f "tokens=1-10 delims=() " %%i in ('perl -v ^| findstr /c:"This is perl"') do (
  if  "%%o" == "subversion" (
    set PerlVersion=%%q
  ) else (
    set PerlVersion=%%l
  )
  set PerlVersionStatus=NotFamiliar
)
if  "%PerlVersionStatus%" == "NotRecognized" (
  echo ************************************
  echo ***********  ERROR  ****************
  echo ************************************
  echo Perl is not installed in your PC . Please intsall Perl.
  echo Recommended perl Installation v5.6.1
  echo Crashman tested on Perl versions- v5.10.1 , v5.6.1 , v5.8.7 , v5.12.4 , v5.14.2 
  goto endall
) 
echo Perl version Installed   : %PerlVersion% >> %versioncheck%
for /f "tokens=1-2 delims= " %%i in ('echo  Tested List v5.10.1 , v5.6.1 , v5.8.7 , v5.12.4 , v5.14.2  End  ^| findstr /c:"%PerlVersion%"') do (
    if  "%%i" == "Tested" (
	set PerlVersionStatus=Success	
        echo Perl version installed    : %PerlVersion%
    )
) 
if "%PerlVersionStatus%" == "NotFamiliar" (
  echo **********  WARNING  ***************
  perl -v | findstr /c:"This is perl"
  echo Please update your Perl version. Recommended perl Installation v5.6.1
  echo Crashman tested on Perl versions- v5.10.1 , v5.6.1 , v5.8.7 , v5.12.4 , v5.14.2 
)
::***********

echo Crashman Version         :%Crashman_Version% >> %versioncheck%

if "%PerlVersionStatus%" == "NotFamiliar" (
  echo **WARNING** >> %versioncheck%
  perl -v | findstr /c:"This is perl" >> %versioncheck%
  echo Please update your Perl version. Recommended perl Installation v5.6.1 >> %versioncheck%
  echo Crashman tested on Perl versions- v5.10.1 , v5.6.1 , v5.8.7 , v5.12.4 , v5.14.2 >> %versioncheck%
  echo **** >> %versioncheck%
)

if "%PythonVersionStatus%" == "NotFamiliar" (
  echo **WARNING** >> %versioncheck%
  echo Python version installed : %PythonVersion% >> %versioncheck%
  echo Please update your Python version. Recommended Python Installation v2.7.6 >> %versioncheck%
  echo Crashman tested on Python versions- v2.7.6  v2.5.2  v2.6.2  v2.7.2  v3.0.1  v2.7.6 >> %versioncheck%
  echo **** >> %versioncheck%  
)  

echo VersionFileEnd >> %versioncheck%
echo VersionFileEnd >> %versioncheck%
::********************


if "%5"=="SMMU" (
set smmu_flag=1
echo SMMU flag set
)

if "%6"=="SMMU" (
set smmu_flag=1
echo SMMU flag set
)


if "%smmu_flag%"=="1" (
set /p id=Please enter the VMLINUX path: 
echo %id%

For %%A in ("%INDumpPath%") do (
    Set INDumpPathOcMEM=%%~dpA
    Set Name=%%~nxA
)

cd SMMU_scripts

python ramparse.py  -a %INDumpPathOcMEM% -o %OUTDumpPath% -v %id% --print-iommu-pg-tables
echo SMMU Page table dump text files generated

cd ..
)

dir %INDumpPath% /D /-C >%OUTDumpPath%\binarylength.txt

if exist %OUTDumpPath%\DumpTimeStamp.txt del %OUTDumpPath%\DumpTimeStamp.txt
if exist %OUTDumpPath%\DynamicLoadObjInfo.txt del %OUTDumpPath%\DynamicLoadObjInfo.txt


echo Trying to Create Crashman Output folder: %OUTDumpPath% 
perl Check_Ram_Size.pl %OUTDumpPath%/binarylength.txt
python Start_Addr1.py  %INDumpPath% %OUTDumpPath%\adspstartaddr.txt %OUTDumpPath%\dumpformant.txt %OUTDumpPath%\binarylength.txt %targetid%



echo Starting T32 for further processing.
echo ************************************
start C:\T32\t32mqdsp6.exe -c %CurrDirectory%\config_sim_usb.t32, "%CurrDirectory%\DSP_load_memorydump_crashman_lite.cmm" %targetid% %UniqueNumber% %INDumpPath% %OUTDumpPath% %CRM_buildpath% %CurrDirectory% %CustomerPath%

:endall


 
