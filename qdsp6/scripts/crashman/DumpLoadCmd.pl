#!perl.exe 

#$f3_input = $ARGV[0];
$oppath=$ARGV[0];
print"\n$oppath\n";
$uniqurnum=$ARGV[1];
$target=$ARGV[2];
$ramdump=$ARGV[3];
$crmbuild=$ARGV[4];
$customerelf=$ARGV[5];
$opfullpath=$oppath."\\$uniqurnum\_DumpCmd/.txt";

open (OUTFILE, ">$oppath\\DumpLoadCmd\_$uniqurnum\.bat") or die " cant open output file: $!\n";
print OUTFILE ("start cmd.exe \/K \"pushd $crmbuild\\adsp\_proc\\qdsp6\\scripts\\Crashman \& adspcrashman.bat $target $ramdump C\:\\Temp\\$uniqurnum $crmbuild $customerelf\"");
#print OUTFILE ("start cmd.exe \/K \"pushd \\\\harv\-pramodp\\Builds\\Crashman\_UpLatest\_8994\\adsp\_proc\\qdsp6\\scripts\\Crashman \& adspcrashman.bat $target $ramdump C\:\\Temp\\$uniqurnum $crmbuild $customerelf\"");
#print OUTFILE ("pushd \\\\harv\-pramodp\\Builds\\Crashman\_UpLatest\\adsp\_proc\\qdsp6\\scripts\\crashman");
#print OUTFILE ("\n");
#print OUTFILE ("perl CheckCrashmanVersion.pl");
#print OUTFILE ("\n");
#print OUTFILE ("popd");
#print OUTFILE ("\n");
#print OUTFILE ("start cmd.exe \/K \"pushd C\:\\Crashman_AutoTriage \& C\: \& adspcrashman.bat $target $ramdump C\:\\Temp\\$uniqurnum $crmbuild $customerelf\"");
##print OUTFILE ("cd c\:\\Crashman");
##print OUTFILE ("\n");
#print OUTFILE ("adspcrashman.bat $target $ramdump C\:\\Temp\\$uniqurnum $crmbuild $customerelf");
close(OUTFILE);