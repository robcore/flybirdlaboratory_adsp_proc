$oppath=$ARGV[0];
$GuestOS=$ARGV[1];
$SensorsOS=$ARGV[2];
$num_of_lines=0;
$opfullpath=$oppath."\/DSPAnalysis.txt";
$ulog_input=$oppath."\/NPA Log.ulog";
#open(ULOGIPFILE,"<$ulog_input") or die "$f3_input: $!\n";
open (OUTFILE, ">>$opfullpath") or die " cant open output file: $!\n";
if(open(ULOGIPFILE,"<$ulog_input")){
	print OUTFILE ("\n");
	print OUTFILE ("NPA Resource Meassges:\n");
	print OUTFILE ("--------------------- \n");
$inputline=<ULOGIPFILE>;
while ($inputline ne "") {
if ($inputline =~ /\w+\:\s+npa_resource\s+.+/)
{
#print "$inputline";
print OUTFILE ("$inputline");
}
$inputline=<ULOGIPFILE>;
}
}

if (open(GLIST,"$oppath\\NPA Log $GuestOS\.ulog")){
	$inputline=<GLIST>;
	print OUTFILE ("NPA Msg Related to GuestOS:\n");
	print OUTFILE ("--------------------------- \n");
	while ( $inputline ne "" ) {
    if ($inputline =~ /\w+\:\s+npa_resource\s+.+/)
    {
       #print "$inputline";
       print OUTFILE ("$inputline");
    }	
	$inputline=<GLIST>;
	}
}
else
{
die"out\:No Such file name Crashed_ThreadCallStack\.txt"
}

if (open(GLIST,"$oppath\\NPA Log $SensorsOS\.ulog")){
	$inputline=<GLIST>;
	print OUTFILE ("NPA Msg Related to SensorOS:\n");
	print OUTFILE ("--------------------------- \n");
	while ( $inputline ne "" ) {
    if ($inputline =~ /\w+\:\s+npa_resource\s+.+/)
    {
       #print "$inputline";
       print OUTFILE ("$inputline");
    }	
	$inputline=<GLIST>;
	}
}
else
{
die"out\:No Such file name Crashed_ThreadCallStack\.txt"
}
#0x55287B27248: npa_resource (name: "/dev/null") (handle: 0xF06643B8) (sequence: 0x00000000) (units: n/a) (resource max: 4294967295) (active max: 4294967295) (active state: 0)  (active headroom: 1) (request state: 0) (required state: 0) (resource attributes: 0x00000000) (node_lock: 0xF066D1C0) (event_lock: 0xF0652F20) (transaction: 0x0) ((_internal: 0xF0664F80) (driver_dur: ((min: 0) (min_time: 0x0) (max: 0) (max_time: 0x0) (total time: 0) (count: 0) (avg: 0x0)))) (current client: 0) 