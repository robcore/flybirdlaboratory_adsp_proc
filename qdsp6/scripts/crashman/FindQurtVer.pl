#$inputfile="C\:\\Dropbox\\1260766\\DumpTimeStamp\.txt";
$inputfileName=$ARGV[0];
$inputfile="$inputfileName\\QURTVersion\.txt";
#$inputfile="Area_IO\.txt";
$QrtVersionNum=0;
open(DUMPFILE, ">$inputfileName\\QURTVerFlag\.txt") or die "not able to open file \"GetCrashedTCB.txt\" in write mode";#Writing to a file "system.xls" which is output.
if (open(TRACEFILE,"$inputfile")){
$inputline=<TRACEFILE>;
while ( $inputline ne "" ) {
if($inputline =~ /.+\:\s+\w+\.\w+\.(\w+).+/)
{
$QrtVersionNum=$1;
}
$inputline=<TRACEFILE>;
}
}
if(($QrtVersionNum > 19) || ($QrtVersionNum == 0))
{
#print "$QrtVersionNum";
print DUMPFILE ("3");
}
else
{
print DUMPFILE ("2");
}
close DUMPFILE;


#**QURTK_version = "QURT Kernel ver.: 02.02.19.02.04"