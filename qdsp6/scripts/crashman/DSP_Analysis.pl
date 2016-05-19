	$inputfileName=$ARGV[0];
	$targetName=$ARGV[1];
	open(LOGFILE, ">$inputfileName\\InternalLog\.txt") or die "not able to open file \"InternalLog.txt\" in write mode";#Writing to a file "InternalLog.txt" which is output.
	open(DUMPFILE, ">$inputfileName\\DSPAnalysis\.txt") or die "not able to open file \"DSPAnalysis.txt\" in write mode";#Writing to a file "DSPAnalysis.txt" which is output.
	#$TCBPointer="F05E5080";
	$noissueFlag = 0;
	#$TCBPointer=hex(F05E5080);
	#print"\n$TCBPointer\n";

	if (open(TCBLIST,"$inputfileName\\GetCrashedTCB.txt")){
	$inputline=<TCBLIST>;
	$inputline=<TCBLIST>;
	while ( $inputline ne "" ) {
	if($inputline =~ /0x(\w+)/)
	{
	$TCBPointer=$1;
	}
	$inputline=<TCBLIST>;
	}
	}
	else
	{
	##die"out\:No Such file name GetCrashedTCB\.txt"
	print LOGFILE ("No Such file name GetCrashedTCB\.txt\n");
	}
	#print"\n$TCBPointer\n";
	##die"out";

	
	if (open(CLIST,"$inputfileName\\CheckDumpStatus.txt")){
	$inputline=<CLIST>;
	print DUMPFILE ("TimeStamp Validation:\n");
	print DUMPFILE ("---------------------\n");
	#while ( $inputline ne "" ) {
	if ($inputline =~ /1/)
	{
	print DUMPFILE ("Time Stamp in Dumps and elf file are Matched-Level1 of validating Dumps passed\n\n");
	}
	else
	{
	print DUMPFILE ("Time Stamp in Dumps and elf file are not Matching - Level1 of validating Dumps Failed\n\n");
	}
	#}
	}
	else
	{
	#die"out\:No Such file name CheckDumpStatus\.txt"	
	print LOGFILE ("No Such file name CheckDumpStatus\.txt\n");
	}
	##die"out";
#print DUMPFILE ("\nTime Stamp in Dumps and elf \n");	
if ($targetName !~ /8994/ || $targetName !~ /8992/ || $targetName !~ /8952/)
{
 	if (open(CALIST,"$inputfileName\\flush\_cache\.txt")){
	$inputline=<CALIST>;
	while ( $inputline ne "" ) {
	if($inputline =~ /.+\*(\w+).+/)
	{
	$cacheflushvalue = $1;
	$cacheflushvalue=hex($cacheflushvalue);
	#print"\n$cacheflushvalue\n";
	goto done;
	}
	$inputline=<CALIST>;
	}
done:	
	}	
	else
	{
	print LOGFILE ("No Such file name flush_cache\.txt\n");
	}
	
if($cacheflushvalue == 1)
{
print DUMPFILE ("CACHE Flush Status:\n");
print DUMPFILE ("--------------------\n");
print DUMPFILE ("The DUMPS provided are Cache Flushed\n\n");
}
else
{
print DUMPFILE ("CACHE Flush Status:\n");
print DUMPFILE ("--------------------\n");
print DUMPFILE ("The DUMPS provided are not Cache Flushed\n\n");
}
}
	if (open(CHLIST,"$inputfileName\\ChickenBits_Value.txt")){
	$inputline=<CHLIST>;
	$inputline=<CHLIST>;
	if($inputline =~ /.+=\s+(\w+)/)
	{
	$ChickenValue=$1;	
	print DUMPFILE ("The Chichken bits set to : $ChickenValue\n");
	print DUMPFILE ("--------------------------\n\n");
	}
	}
	else
	{
	#die"out\:No Such file name ChickenBits_Value\.txt"	
	print LOGFILE ("No Such file name ChickenBits_Value\.txt\n");
	}

	if (open(TLIST,"$inputfileName\\DSP_QT.txt")){
	$inputline=<TLIST>;
	while ( $inputline ne "" ) {

	@values = split('\s+', $inputline);
	$len=@value;
	if($values[0] eq $TCBPointer)
	{
	if($len >= 9)
	{
	print DUMPFILE ("The crashed SW Thraed is : $values[7]$values[8]\n");
	print DUMPFILE ("--------------------------\n\n");
    if($values[4] == 0)
	{
	print DUMPFILE ("The name of the PD that got crashed : GuestOS\n");
	print DUMPFILE ("-----------------------------------\n\n");	
	}
	else
	{
	print DUMPFILE ("The name of the PD that got crashed : Sensors\n");
	print DUMPFILE ("-----------------------------------\n\n");	
	}
	}
	else
	{
	$crashedThread=$values[$len-1];
	if(($crashedThread =~ /RUNNING/) || ($crashedThread =~ /WAITING/) || ($crashedThread =~ /SUSPENDED/))
	{
	print DUMPFILE ("The crashed SW Thraed is showing no name, Expecting some corruption in memory\n");
	print DUMPFILE ("-----------------------------------------\n\n");
	if($values[4] == 0)
	{
	print DUMPFILE ("The name of the PD that got crashed : GuestOS\n");
	print DUMPFILE ("-----------------------------------\n\n");	
	}
	else
	{
	print DUMPFILE ("The name of the PD that got crashed : Sensors\n");
	print DUMPFILE ("-----------------------------------\n\n");	
	}
	goto label345;
	}
	print DUMPFILE ("The crashed SW Thraed is : $crashedThread\n");
	print DUMPFILE ("--------------------------\n\n");
	if($values[4] == 0)
	{
	print DUMPFILE ("The name of the PD that got crashed : GuestOS\n");
	print DUMPFILE ("-----------------------------------\n\n");	
	}
	else
	{
	print DUMPFILE ("The name of the PD that got crashed : Sensors\n");
	print DUMPFILE ("-----------------------------------\n\n");	
	}
	}
	}
	$inputline=<TLIST>;
	}
	}
	else
	{
	##die"out\:No Such file name DSP_QT\.txt"		
	print LOGFILE ("No Such file name DSP_QT\.txt\n");
	}
	label345:
	
		if (open(TCBSLIST,"$inputfileName\\GetCrashedTCB.txt")){
$inputline=<TCBSLIST>;
$FatalErr=$inputline;
}
else
{
##die"out\:No Such file name GetCrashedTCB\.txt"
print LOGFILE ("No Such file name GetCrashedTCB\.txt\n");
}

close TCBSLIST;
	
if($FatalErr != 2)
{	
	if (open(ELIST,"$inputfileName\\Error_info.txt")){
	$inputline=<ELIST>;
	$inputline=<ELIST>;
	print DUMPFILE ("The Cause for the ADSP crash is:\n");
	print DUMPFILE ("--------------------------------\n");
	#print"\n$inputline\n";
	while ( $inputline ne "" ) {
	if(($inputline =~ /^\w+/) || ($inputline =~ /^\s+\-.+/))
	{
	if($inputline =~ /^pls\. provide the TCB address.+/)
	{
	print DUMPFILE ("No Crash in ADSP\n");
	}
	else
	{
	print DUMPFILE ("$inputline");
	}
	}
	$inputline=<ELIST>;
	}
	print DUMPFILE ("\n");
	}
	else
	{
	#die"out\:No Such file name Error_info\.txt"	
	print LOGFILE ("No Such file name Error_info\.txt\n");
	}
}
else
{
if (open(ALIST,"$inputfileName\\Area_IO.txt")){
	$inputline=<ALIST>;
	$inputline=<ALIST>;
	print DUMPFILE ("The Cause for the ADSP crash is:\n");
	print DUMPFILE ("--------------------------------\n");
	#print"\n$inputline\n";
	while ( $inputline ne "" ) {
	if($inputline =~ /^\-\-\-\-.+/)
	{
	$inputline=<ALIST>;
	print DUMPFILE ("$inputline\n");
	goto label567;
	}
	$inputline=<ALIST>;
	}
	}
	else
	{
	#die"out\:No Such file name Area_IO\.txt"
	print LOGFILE ("No Such file name Area_IO\.txt\n");	
	}
	
}
label567:	
	if (open(TCBSLIST,"$inputfileName\\GetCrashedTCB.txt")){
$inputline=<TCBSLIST>;
$FatalErr=$inputline;
}
else
{
#die"out\:No Such file name GetCrashedTCB\.txt"
print LOGFILE ("No Such file name GetCrashedTCB\.txt\n");	
}

if($FatalErr == 2)
{
print DUMPFILE ("The info in core dump is:\n");
print DUMPFILE ("------------------------------\n");
if (open(SWLIST,"$inputfileName\\SWFatal_Error.txt")){
$inputline=<SWLIST>;
while ( $inputline ne "" ) {
if($inputline =~ /.+coredump.err.message\s+=\s+\"(.+)\"/)
{
$err_msg=$1;
print DUMPFILE ("The error message is:\n");
print DUMPFILE ("$err_msg\n");
}
if($inputline =~ /.+coredump.err.filename\s+=\s+\"(.+)\"/)
{
$err_file=$1;
print DUMPFILE ("The error message in file:\n");
print DUMPFILE ("$err_file\n");
}
if($inputline =~ /.+coredump.err.param\s+=\s+\((.+)\)/)
{
$err_param=$1;
print DUMPFILE ("The params to err message:\n");
print DUMPFILE ("$err_param\n");
}
$inputline=<SWLIST>;
}
}
else
{
#die"out\:No Such file name GetCrashedTCB\.txt"	
print LOGFILE ("No Such file name GetCrashedTCB\.txt\n");	
}

}


	
	if (open(CSLIST,"$inputfileName\\Crashed_ThreadCallStack_Locals.txt")){
	$inputline=<CSLIST>;
	print DUMPFILE ("\nThe Call stack of the crashed thread is:\n");
	print DUMPFILE ("------------------------------------------\n");
	while ( $inputline ne "" ) {
	#if(($inputline !~ /(.+)end of frame(.+)/) || ($inputline !~ /\s+\*\*\*\*end of frame/))
	#if(($inputline !~ /\s+\*\n/) || ($inputline !~ /\s+\*/)) 
	#chomp($inputline);
	#print"\n$inputline\n";
	if(($inputline =~ /^\-\w+\*(.+)/) || ($inputline =~ /^\s+\*\s+\*(.+)/) || ($inputline =~ /^\s+\*\*(.+)/))
	{
	#print"\n$inputline\n";
	print DUMPFILE ("$inputline");
	}
	#else
	#{
	#goto label123;
	#}
	$inputline=<CSLIST>;
	}
	}
	else
	{
	#die"out\:No Such file name Crashed_ThreadCallStack_Locals\.txt"		
	print LOGFILE ("No Such file name Crashed_ThreadCallStack_Locals\.txt\n");	
	}
	label123:
	#print"\nDone\n";


	if (open(RLIST,"$inputfileName\\Crashed_Thread_RegSet.txt")){
	$inputline=<RLIST>;
	while ( $inputline ne "" ) {
	if($inputline =~ /STID\s+\w+\s+ELR\s+(\w+).+/)
	{
	$ELR=$1;
	print DUMPFILE ("\nThe PC at which the ADSP crashed: 0x$ELR\n");
	print DUMPFILE ("----------------------------------\n");
	}
	$inputline=<RLIST>;
	}	
	}
	else
	{
	#die"out\:No Such file name Crashed_Thread_RegSet\.txt"	
	print LOGFILE ("No Such file name Crashed_Thread_RegSet\.txt\n");	
	}


if (open(CLIST,"$inputfileName\\Crashed_ThreadLastExe_Code.txt")){
$inputline=<CLIST>;
print DUMPFILE ("\nThe disassenmbled code where the crashed happened:\n");
print DUMPFILE ("---------------------------------------------------\n");
while ( $inputline ne "" ) {
if ($inputline =~ /\s+P\:$ELR(.+)/)
{
print DUMPFILE ("\n$inputline\n");
}
$inputline=<CLIST>;
}
}
else
{
#die"out\:No Such file name Crashed_ThreadLastExe_Code\.txt"
print LOGFILE ("No Such file name Crashed_ThreadLastExe_Code\.txt\n");	
}

if (open(RLIST,"$inputfileName\\Crashed_Thread_RegSet.txt")){
$inputline=<RLIST>;
$inputline=<RLIST>;
print DUMPFILE ("\nRegister set of the Crashed Thread:\n");
print DUMPFILE ("-------------------------------------\n");
while ( $inputline ne "" ) {
if($inputline =~ /\w+.+/)
{
print DUMPFILE ("$inputline");
}
$inputline=<RLIST>;
}
}
else
{
#die"out\:No Such file name Crashed_Thread_RegSet\.txt"
print LOGFILE ("No Such file name Crashed_Thread_RegSet\.txt\n");	
}


if (open(SLIST,"$inputfileName\\DSP_stack_check.txt")){
print DUMPFILE ("StackAnalysis:\n");
print DUMPFILE ("--------------\n");
$inputline=<SLIST>;
while ( $inputline ne "" ) {
if($inputline =~ /^No Issues/)
{
$noissueFlag=1;
print DUMPFILE ("No Stack Overflow Detected");
goto nostackof;
}
$inputline=<SLIST>;
print DUMPFILE ("Stack Overflow Detected");
nostackof:
}
}
else
{
#die"out\:No Such file name DSP_stack_check\.txt"
print LOGFILE ("No Such file name DSP_stack_check\.txt\n");
}



if (open(HLIST,"$inputfileName\\Heap_Analysis_GuestOS.txt")){
print DUMPFILE ("\n\nHeapAnalysis of GuestOS:\n");
print DUMPFILE ("----------------------------\n");
$inputline=<HLIST>;
while ( $inputline ne "" ) {
if($inputline =~ /^Heap Corruption Detected!!/)
{
$heapstatsFlag=1;
print DUMPFILE ("Heap Corruption Detected\n");
$inputline=<HLIST>;
print DUMPFILE ("$inputline");
$inputline=<HLIST>;
print DUMPFILE ("$inputline");
$inputline=<HLIST>;
print DUMPFILE ("$inputline");
}
$inputline=<HLIST>;
}
}
else
{
#die"out\:No Such file name Heap_Analysis_GuestOS\.txt"
print LOGFILE ("No Such file name Heap_Analysis_GuestOS\.txt\n");
}
#if ($targetName !~ /8994/)
#{
if($heapstatsFlag != 1)
{
print DUMPFILE ("No Heap Corruption Detected in guest OS\n");
}
#}

$ErrFlag =1;	
if (open(MCLIST,"$inputfileName\\Def_Heap\\___MemCost.csv")){
$inputline=<MCLIST>;
while ( $inputline ne "" ) {
if($inputline =~ /\s+0x\w+/)
{
@HeapPercent = split(',', $inputline);
if($HeapPercent[6] >= 20)
{

      if($ErrFlag==1)
	  {
	     print DUMPFILE ("\n\nAllocations Greater than 20\% of Default heap by GuestOS :\n");
         print DUMPFILE ("--------------------------------------------------------------\n");
		 print DUMPFILE ("Caller Pointer, Caller Symbol, Num of Allocations, Max Allocated,Min Allocated, Total Allocated, Percent Allocated, Avg Wasted Bytes, Total WstdBytes, Waste Percent\n");
	     $ErrFlag=0;
	  }
print DUMPFILE ("$inputline");
#print"$inputline";
}
}
$inputline=<MCLIST>;
}
}
else
{
print LOGFILE ("No Such file name ___MemCost\.csv\n");
}



$heapstatsFlag =0;
if (($targetName =~ /8x26/) || ($targetName =~ /8974/) || ($targetName =~ /8626/) || ($targetName =~ /8084/) || ($targetName =~ /8994/)|| ($targetName =~ /8992/) || ($targetName =~ /8952/))
{
if (open(HLIST,"$inputfileName\\Heap_Analysis_Sensors.txt")){
print DUMPFILE ("\n\nHeapAnalysis of Sensors PD:\n");
print DUMPFILE ("-------------------------------\n");
$inputline=<HLIST>;
while ( $inputline ne "" ) {
if($inputline =~ /^Heap Corruption Detected!!/)
{
$heapstatsFlag=1;
print DUMPFILE ("Heap Corruption Detected\n");
$inputline=<HLIST>;
print DUMPFILE ("$inputline");
$inputline=<HLIST>;
print DUMPFILE ("$inputline");
$inputline=<HLIST>;
print DUMPFILE ("$inputline");
}
$inputline=<HLIST>;
}
}
else
{
#die"out\:No Such file name Heap_Analysis_Sensors\.txt"
print LOGFILE ("No Such file name Heap_Analysis_Sensors\.txt\n");
}
#if ($targetName !~ /8994/)
#{
if($heapstatsFlag != 1)
{
print DUMPFILE ("No Heap Corruption Detected in Sensors PD\n");
}
#}
$ErrFlag =1;	
if (open(MCLIST,"$inputfileName\\Def_Heap_forSensors_img\\___MemCost.csv")){
$inputline=<MCLIST>;
while ( $inputline ne "" ) {
if($inputline =~ /\s+0x\w+/)
{
@HeapPercent = split(',', $inputline);
if($HeapPercent[6] >= 20)
{

      if($ErrFlag==1)
	  {
	     print DUMPFILE ("\n\nAllocations Greater than 20\% of Default heap by SensorsPD :\n");
         print DUMPFILE ("--------------------------------------------------------------\n");
		 print DUMPFILE ("Caller Pointer, Caller Symbol, Num of Allocations, Max Allocated,Min Allocated, Total Allocated, Percent Allocated, Avg Wasted Bytes, Total WstdBytes, Waste Percent\n");
	     $ErrFlag=0;
	  }
print DUMPFILE ("$inputline");
#print"$inputline";
}
}
$inputline=<MCLIST>;
}
}
else
{
print LOGFILE ("No Such file name ___MemCost\.csv\n");
}

}


if (open(HLIST,"$inputfileName\\Heap_Analysis_QURT.txt")){
print DUMPFILE ("\n\nHeapAnalysis of QURT:\n");
print DUMPFILE ("----------------------------\n");
$inputline=<HLIST>;
while ( $inputline ne "" ) {
if($inputline =~ /^Heap Corruption Detected!!/)
{
$heapstatsFlag=1;
print DUMPFILE ("Heap Corruption Detected\n");
$inputline=<HLIST>;
print DUMPFILE ("$inputline");
$inputline=<HLIST>;
print DUMPFILE ("$inputline");
$inputline=<HLIST>;
print DUMPFILE ("$inputline");
}
$inputline=<HLIST>;
}
}
else
{
#die"out\:No Such file name Heap_Analysis_GuestOS\.txt"
print LOGFILE ("No Such file name Heap_Analysis_QURT\.txt\n");
}
#if ($targetName !~ /8994/)
#{
if($heapstatsFlag != 1)
{
print DUMPFILE ("No Heap Corruption Detected in QURT\n");
}
#}



if (open(HLIST,"$inputfileName\\Heap_Analysis_QURTISLAND.txt")){
print DUMPFILE ("\n\nHeapAnalysis of QURTISLAND:\n");
print DUMPFILE ("----------------------------\n");
$inputline=<HLIST>;
while ( $inputline ne "" ) {
if($inputline =~ /^Heap Corruption Detected!!/)
{
$heapstatsFlag=1;
print DUMPFILE ("Heap Corruption Detected\n");
$inputline=<HLIST>;
print DUMPFILE ("$inputline");
$inputline=<HLIST>;
print DUMPFILE ("$inputline");
$inputline=<HLIST>;
print DUMPFILE ("$inputline");
}
$inputline=<HLIST>;
}
}
else
{
#die"out\:No Such file name Heap_Analysis_GuestOS\.txt"
print LOGFILE ("No Such file name Heap_Analysis_QURTISLAND\.txt\n");
}
#if ($targetName !~ /8994/)
#{
if($heapstatsFlag != 1)
{
print DUMPFILE ("No Heap Corruption Detected in QURTISLAND\n");
}
#}


$dyflag=1;

if (open(DYLIST,"$inputfileName\\DynamicLoadObjInfo.txt")){
$inputline=<DYLIST>;
#$inputline=<DYLIST>;
#$inputline=<DYLIST>;
while ( $inputline ne "" ) {
#print "\n$inputline\n";
if($inputline !~ /^\d+/)
{
if($dyflag==1)
{
print DUMPFILE ("\n");
print DUMPFILE ("The Dynamic Object loaded @ PhyPool is:\n");
print DUMPFILE ("---------------------------------------\n");
$dyflag=0;
}
print DUMPFILE ("$inputline");
#$inputline=<DYLIST>;
#print DUMPFILE ("$inputline");
}
$inputline=<DYLIST>;
#$inputline=<DYLIST>;
#$inputline=<DYLIST>;
}
}
else
{
print LOGFILE ("No Such file name DynamicLoanInfoFin\.txt\n");
}
