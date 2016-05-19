#!/bin/bash

# execute below commands and match with output specified in test_so_ref.cfg
#./avs/elite/module_interfaces/shared_lib_api/etc/test_so.sh /prj/vocoder/appdsp5/users/rbhatnk/AVS.ADSP.2.6.dynloading2/adsp_proc/avs/install_dir/avs_shared_libs/qdsp6/AAAAAAAA /prj/vocoder/appdsp5/users/rbhatnk/AVS.ADSP.2.6.dynloading2/adsp_proc//avs/elite/module_interfaces/shared_lib_api/etc/test_out.txt /prj/vocoder/appdsp5/users/rbhatnk/AVS.ADSP.2.6.dynloading2/adsp_proc//avs/elite/module_interfaces/shared_lib_api/etc/test_so_ref.txt
if [ $# -ne 4 ]
then 
echo "usage: test_so.sh dir_of_shared_obj dsp_elf_file_with_sym out_file ref_output"
echo " tested on linux "
echo "Eg. test_so.sh /prj/vocoder/appdsp5/users/rbhatnk/AVS.ADSP.2.6.dynloading2/adsp_proc/avs/install_dir/avs_shared_libs/qdsp6/AAAAAAAA /prj/vocoder/appdsp5/users/rbhatnk/AVS.ADSP.2.6.dynloading2/adsp_proc/build/ms/M8994AAAAAAAAQ1234.elf /prj/vocoder/appdsp5/users/rbhatnk/AVS.ADSP.2.6.dynloading2/adsp_proc//avs/elite/module_interfaces/shared_lib_api/etc/test_so.txt /prj/vocoder/appdsp5/users/rbhatnk/AVS.ADSP.2.6.dynloading2/adsp_proc//avs/elite/module_interfaces/shared_lib_api/etc/test_so_ref.txt"
exit
fi

location=$1
dsp_elf_file=$2
out_file=$3
ref_output=$4

#################### Check DSP elf file for symbols
echo 'DSP ELF File' > $out_file
### check for public symbol adsp_avs_build_property
echo check for adsp_avs_build_property  >> $out_file
hexagon-readelf $dsp_elf_file -Ds | grep adsp_avs_build_property | awk -F ' ' '{print $NF}' >> $out_file

#################### HpMp3DecoderModule
so_name='HpMp3DecoderModule.so.1.0'
echo  >> $out_file
echo $so_name >> $out_file
### check for 2 public functions 
echo check for two public functions  >> $out_file
hexagon-readelf $location/$so_name -Ws | grep hp_mp3_dec_capi_v2_get_static_properties | awk -F ' ' '{print $NF}' >> $out_file
hexagon-readelf $location/$so_name -Ws | grep hp_mp3_dec_capi_v2_init | awk -F ' ' '{print $NF}' >> $out_file

#check for shared_lib_build_property
echo check for shared_lib_build_property >> $out_file
hexagon-readelf $location/$so_name -Ws | grep shared_lib_build_property | awk -F ' ' '{print $NF}' >> $out_file

### check for obfuscation
echo check for obfuscation >> $out_file
hexagon-readelf $location/$so_name -Ws | grep subband_synthesis_mp3d | awk -F ' ' '{print $NF}' >> $out_file

###check for dependents
echo check for dependents >> $out_file
hexagon-readelf $location/$so_name -d | grep 'Shared library' | awk -F ' ' '{print $NF}' >> $out_file

#check DSP to .so compatibility
python check_so_dsp_match.py -d $dsp_elf_file -c /dev/null -s $location/$so_name > /dev/null
result=$?
echo Compatibility of DSP and $so_name is: $result >> $out_file
if [ $result -eq 1 ]; then
   echo ' Failed!!! '
   exit 1
fi  

#################### Mp3DecoderModule
so_name='Mp3DecoderModule.so.1.0'
echo  >> $out_file
echo $so_name >> $out_file
### check for 2 public functions 
echo check for two public functions  >> $out_file
hexagon-readelf $location/$so_name -Ws | grep mp3_dec_capi_v2_get_static_properties | awk -F ' ' '{print $NF}' >> $out_file
hexagon-readelf $location/$so_name -Ws | grep mp3_dec_capi_v2_init | awk -F ' ' '{print $NF}'>> $out_file

### check for obfuscation
echo check for obfuscation >> $out_file
hexagon-readelf $location/$so_name -Ws | grep Mp3DecoderLib16BitStreamGetNBitEl | awk -F ' ' '{print $NF}' >> $out_file

###check for dependents
echo check for dependents >> $out_file
hexagon-readelf $location/$so_name -d  | grep 'Shared library' | awk -F ' ' '{print $NF}' >> $out_file

#check DSP to .so compatibility
python check_so_dsp_match.py -d $dsp_elf_file -c /dev/null -s $location/$so_name > /dev/null
result=$?
echo Compatibility of DSP and $so_name is: $result >> $out_file
if [ $result -eq 1 ]; then
   echo ' Failed!!! '
   exit 1
fi     
#################### ComboMp3DecoderModule
so_name='ComboMp3DecoderModule.so.1.0'
echo  >> $out_file
echo $so_name >> $out_file
### check for 2 public functions 
echo check for two public functions  >> $out_file
hexagon-readelf $location/$so_name -Ws | grep combo_mp3_dec_capi_v2_get_static_properties | awk -F ' ' '{print $NF}' >> $out_file
hexagon-readelf $location/$so_name -Ws | grep combo_mp3_dec_capi_v2_init | awk -F ' ' '{print $NF}' >> $out_file

###check for dependents
echo check for dependents >> $out_file
hexagon-readelf $location/$so_name -d | grep 'Shared library' | awk -F ' ' '{print $NF}' >> $out_file

#check DSP to .so compatibility
python check_so_dsp_match.py -d $dsp_elf_file -c /dev/null -s $location/$so_name > /dev/null
result=$?
echo Compatibility of DSP and $so_name is: $result >> $out_file
if [ $result -eq 1 ]; then
   echo ' Failed!!! '
   exit 1
fi     
#################### EtsiEaacCommonModule
so_name='EtsiEaacCommonModule.so.1.0'
echo  >> $out_file
echo $so_name >> $out_file
### check for 2 public functions
echo check for two public function  >> $out_file
hexagon-readelf $location/$so_name -Ws | grep ffr_div32_32 | awk -F ' ' '{print $NF}'>> $out_file
hexagon-readelf $location/$so_name -Ws | grep CopyBitBufAll | awk -F ' ' '{print $NF}' >> $out_file

#check DSP to .so compatibility
python check_so_dsp_match.py -d $dsp_elf_file -c /dev/null -s $location/$so_name > /dev/null
result=$?
echo Compatibility of DSP and $so_name is: $result >> $out_file
if [ $result -eq 1 ]; then
   echo ' Failed!!! '
   exit 1
fi     
#################### EtsiEaacPlusEncoderModule
so_name='EtsiEaacPlusEncoderModule.so.1.0'
echo  >> $out_file
echo $so_name >> $out_file
### check for 2 public functions 
echo check for two public functions  >> $out_file
hexagon-readelf $location/$so_name -Ws | grep etsi_eaacplus_enc_capi_v2_get_static_properties | awk -F ' ' '{print $NF}' >> $out_file
hexagon-readelf $location/$so_name -Ws | grep etsi_eaacplus_enc_capi_v2_init | awk -F ' ' '{print $NF}' >> $out_file

###check for dependents
echo check for dependents >> $out_file
hexagon-readelf $location/$so_name -d | grep 'Shared library' | awk -F ' ' '{print $NF}' >> $out_file

#check DSP to .so compatibility
python check_so_dsp_match.py -d $dsp_elf_file -c /dev/null -s $location/$so_name > /dev/null
result=$?
echo Compatibility of DSP and $so_name is: $result >> $out_file
if [ $result -eq 1 ]; then
   echo ' Failed!!! '
   exit 1
fi  
################################### finally diff with reference
echo 'Diffing'
echo
diff -w $out_file $ref_output
if [ $? -eq 0 ]; then
	echo
	echo 'Passed'
   exit 0
else 
	echo
	echo 'Failed!!!'
   exit 1
fi
echo
