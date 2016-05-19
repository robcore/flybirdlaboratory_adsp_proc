	$inputfileName=$ARGV[0];
	$outputpath=$ARGV[1];
	open(LPMFILE, ">$outputpath\\LPMPath\.txt") or die "not able to open file \"LPMPath.txt\" in write mode";#Writing to a file "LPMPath.txt" which is output.
    if(($inputfileName =~ /(.+)\\.+\.\w+/) || ($inputfileName =~ /(.+)\/.+\.\w+/))
	{
	  $Path=$1;
	  print LPMFILE ("$Path");
	}