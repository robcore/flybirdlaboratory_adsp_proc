$TimeStamFlag =0;
#$inputfile="C\:\\Dropbox\\1260766\\DumpTimeStamp\.txt";
$inputfileName=$ARGV[0];
$inputfile="$inputfileName\\DumpTimeStamp\.txt";
open(DUMPFILE, ">$inputfileName\\CheckDumpStatus\.txt") or die "not able to open file \"CheckDumpStatus.txt\" in write mode";#Writing to a file "system.xls" which is output.
if (open(TRACEFILE,"$inputfile")){
$inputline=<TRACEFILE>;
while ( $inputline ne "" ) {
if($inputline =~ /^B\:\:(.+)/)
{
$inputline=<TRACEFILE>;
$inputline=<TRACEFILE>;
if($DumpEnggTimeStamp eq $inputline)
{
$TimeStamFlag=1;
}
$DumpEnggTimeStamp=$inputline;
#print"\n$inputline\n";
}
$inputline=<TRACEFILE>;
}
}
else
{
die"out\:No Such file name DumpTimeStamp\.txt"
}

if($TimeStamFlag == 1)
{
print DUMPFILE ("1");
#"\nTime Stamp in Dumps and elf file are Matched-Level1 of validating Dumps passed\n";
}
else
{
print DUMPFILE ("0");
#die"Time Stamp in Dumps and elf file are not Matching - Level1 of validating Dumps Failed\n";
}
close DUMPFILE;