#!perl.exe 

#$f3_input = $ARGV[0];
$oppath=$ARGV[0];
$target_name=$ARGV[1];
$num_of_lines=0;
$opfullpath=$oppath."\/DSPAnalysis.txt";
$f3_input=$oppath."\/f3log.txt";
if(($target_name == "8084")||($target_name == "8974")||($target_name == "8x26")||($target_name == "8626")||($target_name == "8994")||($target_name == "8992")||($target_name == "8996")||($target_name == "8952"))
{
$f3_sensorinput=$oppath."\/SensorF3Logs"."\/f3log.txt";
}

open(F3IPFILE,"<$f3_input") or die "$f3_input: $!\n";
open (OUTFILE, ">>$opfullpath") or die " cant open output file: $!\n";

$entry=1;
$entry1=1;
$inputline=<F3IPFILE>;
while ($inputline ne "") {
if($inputline =~ /\w+.+/)
{
$num_of_lines=$num_of_lines+1;
}
$inputline=<F3IPFILE>;
}
$cnt=0;
close(F3IPFILE);

open(F3IPFILE,"<$f3_input") or die "$f3_input: $!\n";
$inputline=<F3IPFILE>;
while ($inputline ne ""){

	if ($cnt>=($num_of_lines-20))
	{
	if($entry ==1)
	{
	$entry=0;
	print OUTFILE ("\n");
	print OUTFILE ("Last few messages in GuestOS F3 logs:\n");
	print OUTFILE ("-------------------------------------\n");
	}
	if($inputline =~ /\w+.+/)
	{
	print OUTFILE ("$inputline");
	}
	}
	else
	{
	#(grep (/^$unique$/,@first_list_new))
	if (grep (/fail/i,$inputline) || grep (/error/i,$inputline) || grep (/underrun/i,$inputline) || grep (/overflow/i,$inputline) || grep (/UnSupported/i,$inputline)) {
	if($entry1 ==1)
	{
	$entry1=0;
	print OUTFILE ("\nErrors found in GuestOS F3 logs:\n");
    print OUTFILE ("----------------------------------\n");
	}
	print OUTFILE ("$inputline");
	}
	}
	$inputline=<F3IPFILE>;
	$cnt++
	}
	
close(F3IPFILE);
close(OUTFILE);

if(($target_name == "8084")||($target_name == "8974")||($target_name == "8x26")||($target_name == "8626")||($target_name == "8994")||($target_name == "8992")||($target_name == "8996")||($target_name == "8952"))
{
$num_of_lines=0;
open(F3IPFILE,"<$f3_sensorinput") or die "$f3_sensorinput: $!\n";
open (OUTFILE, ">>$opfullpath") or die " cant open output file: $!\n";

$entry=1;
$entry1=1;
$inputline=<F3IPFILE>;
while ($inputline ne "") {
if($inputline =~ /\w+.+/)
{
$num_of_lines=$num_of_lines+1;
}
$inputline=<F3IPFILE>;
}
$cnt=0;
close(F3IPFILE);

open(F3IPFILE,"<$f3_sensorinput") or die "$f3_sensorinput: $!\n";
$inputline=<F3IPFILE>;
while ($inputline ne ""){

	if ($cnt>=($num_of_lines-20))
	{
	if($entry ==1)
	{
	$entry=0;
	print OUTFILE ("\n");
	print OUTFILE ("Last few messages in Sensors F3 logs:\n");
	print OUTFILE ("-------------------------------------\n");
	}
	#print OUTFILE ("$inputline");
	if($inputline =~ /\w+.+/)
	{
	print OUTFILE ("$inputline");
	}	
	}
	else
	{
	#(grep (/^$unique$/,@first_list_new))
	if (grep (/fail/i,$inputline) || grep (/error/i,$inputline) || grep (/underrun/i,$inputline) || grep (/overflow/i,$inputline) || grep (/UnSupported/i,$inputline)) {
	if($entry1 ==1)
	{
	$entry1=0;
	print OUTFILE ("\nErrors found in Sensors F3 logs:\n");
    print OUTFILE ("----------------------------------\n");
	}
	print OUTFILE ("$inputline");
	}
	}
	$inputline=<F3IPFILE>;
	$cnt++
	}
	
close(F3IPFILE);
close(OUTFILE);
}