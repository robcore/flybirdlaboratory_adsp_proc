import os
import re
import sys
import shutil
import math
alist=[]
Palist=[]
mpdImageEnd=[]
mpdImagePAEnd=[]
TotalMpdImageSizeMB=0
uimagestartbase=1
uimagePAStart=[]
uimagePAEnd=[]
iii=666
i=0
j=0
kk=0
k=0
j1=0
gcccompile=0
llvmcompile=0
LastSectionEndAddress=0
TotalMpdImageSize=0
imagefile=sys.argv[1]
chipset=sys.argv[2]
tool_version=int(sys.argv[3])
#print 'Tools version in show memory'
#print tool_version
tool_version=tool_version*1
if tool_version <= 6:
 #print 'This is 5'
 #print tool_version
 os.system ("hexagon-objdump %s -h -w > section_info.txt" % imagefile)
 gcccompile=1	  
if tool_version >= 7:
 #print 'This is 7'
 #print tool_version
 os.system ("hexagon-llvm-objdump %s -h > section_info.txt" % imagefile)
 llvmcompile=1

if gcccompile == 1: 	  
 myfile = open('section_info.txt', 'r')
 for line in myfile:
        words1=re.split('\s+', line)
        if words1[1].isdigit():
             iii=1
        if words1[0].isdigit():
             iii=0
        if any ([iii == 1, iii == 0]): 			 
             x=re.search('\.start.+', words1[iii+1])
             y=re.search('\.start', words1[iii+1])
             if x or y:
                StartIndex=int(words1[iii+3], 16)
                alist.insert(i, StartIndex)
                PAStartIndex=int(words1[iii+4], 16)
                Palist.insert(i, PAStartIndex)
                i=i+1
             MiddleIndexBase=int(words1[iii+3], 16)
             MiddleIndexPABase=int(words1[iii+4], 16)
             if MiddleIndexPABase != 0:
                LastSectionSize=int(words1[iii+2], 16)
                LastSectionEndAddress=MiddleIndexBase+LastSectionSize;
                LastSectionEndPAAddress=MiddleIndexPABase+LastSectionSize;
                island=re.search('.+\.island',words1[iii+1])
                if island:
                    if uimagestartbase == 1: 				    
                       IslandFirstSectionbase=int(words1[iii+4], 16)
                       uimagestartbase=0
                    else:
                       IslandEndSectionbase=int(words1[iii+4], 16)   
                       IslandSectionSize=int(words1[iii+2], 16)
                       IslandEndSectionbase=IslandEndSectionbase+IslandSectionSize					   
             else:
                mpdImageEnd.insert(j, LastSectionEndAddress)
                mpdImagePAEnd.insert(j, LastSectionEndPAAddress)
                if uimagestartbase == 0:
                   uimagePAStart.insert(j1, IslandFirstSectionbase)
                   uimagePAEnd.insert(k, IslandEndSectionbase)	
                   uimagestartbase=1				
                   k=k+1
                   j1=j1+1
                j=j+1
                				
 alist_len=len(alist)
 mpdImageEnd_len=len(mpdImageEnd)
 if k >= 2:
   AlignedImageEndPA=float(uimagePAEnd[k-1]/(256.0*1024.0))
 else:
   AlignedImageEndPA=float(mpdImagePAEnd[j-1]/(256.0*1024.0))
 AlignedImageEndPA=math.ceil(AlignedImageEndPA)
 AlignedImageEnd=AlignedImageEndPA*256*1024
 AlignedImageSize=AlignedImageEnd-Palist[0]
 for kk in range(0, mpdImageEnd_len):
    TotalMpdImageSize+=mpdImageEnd[kk]-alist[kk]
 TotalMpdImageSizeMB=float(TotalMpdImageSize/(1024.0*1024.0))

 infile = open("./build/chipset/%s/qdsp6.xml" % chipset, 'r')
 lines = infile.readlines()			
 line_number = 0
 while line_number < len(lines):
    to_line = lines[line_number]
    x=re.search('\<physical_pool name\=\"DEFAULT\_PHYSPOOL\"\>', to_line)
    if x:
         to_line = lines[line_number+2]
         x=re.search('\<region base\=\"\w+\" size\=\"(\w+)\" \/\>', to_line)
         Image_Size=x.group(1)
         Image_SizeDec=int(Image_Size, 16)
         Image_SizeMB=float(Image_SizeDec/(1024.0*1024.0)) 
    y=re.search('\<trace_size value \= \"(\w+)\" \/\>', to_line)
    if y:
          Trace_Size=y.group(1)
          Trace_Size=int(Trace_Size)
          Trace_Size=3*Trace_Size
          Trace_Num=Trace_Size/1024 
          if Trace_Num <= 4:
                tracesizebytes=4*1024
          elif Trace_Num > 4 and Trace_Num <= 16:
                tracesizebytes=16*1024		 
          elif Trace_Num > 16 and Trace_Num <= 64:
                tracesizebytes=64*1024
          elif Trace_Num > 64 and Trace_Num <= 256:
                tracesizebytes=256*1024					
    line_number += 1
 AlignedImageSize=AlignedImageSize+tracesizebytes
 AlignedImageSizeMB=float(AlignedImageSize/(1024.0*1024.0))
 if alist_len >= 2:
      if k >= 2:
         GuestOSFreeSpace=Palist[j-1]-uimagePAEnd[0]
         GuestOSFreeSpace=GuestOSFreeSpace/1024.0
         SensorPDFreeSpace=AlignedImageEnd-uimagePAEnd[k-1]
         SensorPDFreeSpace=SensorPDFreeSpace/1024.0	 
      else:	  
         GuestOSFreeSpace=Palist[j-1]-mpdImagePAEnd[0]
         GuestOSFreeSpace=GuestOSFreeSpace/1024.0
         SensorPDFreeSpace=AlignedImageEnd-mpdImagePAEnd[j-1]
         SensorPDFreeSpace=SensorPDFreeSpace/1024.0
 else:
      if j1 != 0:
         GuestOSFreeSpace=AlignedImageEnd-uimagePAEnd[k-1]
         GuestOSFreeSpace=GuestOSFreeSpace/1024.0  	  
      else:
         GuestOSFreeSpace=AlignedImageEnd-mpdImagePAEnd[j-1]
         GuestOSFreeSpace=GuestOSFreeSpace/1024.0   
 if Image_SizeMB >= AlignedImageSizeMB:     
        print ('*****************LPASS Memory FootPrint************************')
        print "Total Image size declared in MB			:%.4f" % Image_SizeMB
        print "Total Image Size Consumed in MB			:%.4f" % AlignedImageSizeMB
        if alist_len >= 2:	
            print "Free Space in GuestOS in KB(1MB Align Btw GuestPD & SensorPD):%.4f" % GuestOSFreeSpace
            print "Free Space in SensorsPD in KB(Image end align to 256KB)	     :%.4f" % SensorPDFreeSpace
            print ('Free Space in PHYPOOL in KB:')		
            print ('   DEFAULT_PHYSPOOL - (Static(Text+Data) Memory size + Heap Memory size + GuestOSFreeSpace + SensorsPDFreeSpace + QURTTraceBuffer)')
        else:
            print "Free Space in GuestPD in KB(Image end align to 256KB)	:%.4f" % GuestOSFreeSpace
            print ('Free Space in PHYSPOOL in KB:')
            print ('   DEFAULT_PHYSPOOL - (Static(Text+Data) Memory size + Heap Memory size + GuestOSFreeSpace + QURTTraceBuffer)')
        print "   =%.4f-%.4f" % (Image_SizeMB,AlignedImageSizeMB)
        ImageDiff=float(Image_SizeMB-AlignedImageSizeMB)
        ImageDiff=float(ImageDiff*1024.00)
        if alist_len >= 2:
            print "   =%.4f " % ImageDiff
        else:
            print "   =%.4f " % ImageDiff
        if j1 >= 2:
           GuestOSUImageSize=uimagePAEnd[0]-uimagePAStart[0]		
           GuestOSUImageSize=GuestOSUImageSize/1024.0
           print "UImage size in GuestOS in KB			:%.4f" % GuestOSUImageSize		
           SensorsPDUImageSize=uimagePAEnd[1]-uimagePAStart[1]		
           SensorsPDUImageSize=SensorsPDUImageSize/1024.0
           print "UImage size in SensorsPD in KB			:%.4f" % SensorsPDUImageSize
        else:
           GuestOSUImageSize=uimagePAEnd[0]-uimagePAStart[0]		
           GuestOSUImageSize=GuestOSUImageSize/1024.0
           print "UImage size in GuestOS in KB			:%.4f" % GuestOSUImageSize	            		
 else:
        print ('**********************************************************************')
        print ('Error: Image Size greater than DEFAULT_PHYSPOOL defined in qdsp6.xml\n')
        print ('**********************************************************************')
        print "Total Image size declared in MB			:%.4f" % Image_SizeMB
        print "Total Image Size Consumed in MB			:%.4f" % AlignedImageSizeMB
        if alist_len >= 2:	
            print ('Required Extra Memory size in KB:')			
            print ('   (Static(Text+Data) Memory size + Heap Memory size + GuestOSFreeSpace + SensorsPDFreeSpace + QURTTraceBuffer) - DEFAULT_PHYSPOOL')
        else:
            print ('Required Extra Memory size in KB:')	
            print ('   (Static(Text+Data) Memory size + Heap Memory size + GuestOSFreeSpace + SensorsPDFreeSpace + QURTTraceBuffer) - DEFAULT_PHYSPOOL')		
        print "   =%.4f-%.4f" % (AlignedImageSizeMB,Image_SizeMB)
        ImageDiff=AlignedImageSizeMB-Image_SizeMB
        ImageDiff=ImageDiff*1024.0
        print "   =%.4f" % ImageDiff	
        shutil.rmtree('obj')
        delFile="dsp.elf"
        if os.path.isfile(delFile):		
           os.remove(delFile)
        #os.remove("/obj")

if llvmcompile == 1:
 z=0
 myfile = open('section_info.txt', 'r')
 for line in myfile:
        words1=re.split('\s+', line)
        if words1[1].isdigit():
             iii=0		
        if words1[0].isdigit():
             iii=0
        if any ([iii == 1, iii == 0]): 			 
             x=re.search('\.start.+', words1[iii+2])
             y=re.search('\.start', words1[iii+2])
             if x or y:
                StartIndex=int(words1[iii+3], 16)
                alist.insert(i, StartIndex)
                PAStartIndex=int(words1[iii+4], 16)
                Palist.insert(i, PAStartIndex)
                i=i+1
                z=1;
             if z:
              MiddleIndexPABase=int(words1[iii+4], 16)
              if MiddleIndexPABase != 0:
                LastSectionSize=int(words1[iii+3], 16)
                LastSectionEndPAAddress=MiddleIndexPABase+LastSectionSize;
                island=re.search('.+\.island',words1[iii+1])
                if island:
                    if uimagestartbase == 1: 				    
                       IslandFirstSectionbase=int(words1[iii+4], 16)
                       uimagestartbase=0
                    else:
                       IslandEndSectionbase=int(words1[iii+4], 16)   
                       IslandSectionSize=int(words1[iii+2], 16)
                       IslandEndSectionbase=IslandEndSectionbase+IslandSectionSize					   
              else:
                mpdImagePAEnd.insert(j, LastSectionEndPAAddress)
                #print LastSectionEndPAAddress
                if uimagestartbase == 0:
                   uimagePAStart.insert(j1, IslandFirstSectionbase)
                   uimagePAEnd.insert(k, IslandEndSectionbase)	
                   uimagestartbase=1				
                   k=k+1
                   j1=j1+1
                if z:
                   j=j+1
                   z=0
                   #print j
                				
 alist_len=len(alist)
 mpdImageEnd_len=len(mpdImagePAEnd)
 AlignedImageEndPA=float(mpdImagePAEnd[j-1]/(256.0*1024.0))
 AlignedImageEndPA=math.ceil(AlignedImageEndPA)
 AlignedImageEnd=AlignedImageEndPA*256*1024
 AlignedImageSize=AlignedImageEnd-Palist[0]

 infile = open("./build/chipset/%s/qdsp6.xml" % chipset, 'r')
 lines = infile.readlines()			
 line_number = 0
 while line_number < len(lines):
    to_line = lines[line_number]
    x=re.search('\<physical_pool name\=\"DEFAULT\_PHYSPOOL\"\>', to_line)
    if x:
         to_line = lines[line_number+2]
         x=re.search('\<region base\=\"\w+\" size\=\"(\w+)\" \/\>', to_line)
         Image_Size=x.group(1)
         Image_SizeDec=int(Image_Size, 16)
         Image_SizeMB=float(Image_SizeDec/(1024.0*1024.0)) 
    y=re.search('\<trace_size value \= \"(\w+)\" \/\>', to_line)
    if y:
          Trace_Size=y.group(1)
          Trace_Size=int(Trace_Size)
          Trace_Size=3*Trace_Size
          Trace_Num=Trace_Size/1024 
          if Trace_Num <= 4:
                tracesizebytes=4*1024
          elif Trace_Num > 4 and Trace_Num <= 16:
                tracesizebytes=16*1024		 
          elif Trace_Num > 16 and Trace_Num <= 64:
                tracesizebytes=64*1024
          elif Trace_Num > 64 and Trace_Num <= 256:
                tracesizebytes=256*1024					
    line_number += 1
 AlignedImageSize=AlignedImageSize+tracesizebytes
 AlignedImageSizeMB=float(AlignedImageSize/(1024.0*1024.0))
 if alist_len >= 2:
      if k >= 2:
         GuestOSFreeSpace=Palist[j-1]-uimagePAEnd[0]
         GuestOSFreeSpace=GuestOSFreeSpace/1024.0
         SensorPDFreeSpace=AlignedImageEnd-uimagePAEnd[k-1]
         SensorPDFreeSpace=SensorPDFreeSpace/1024.0	 
      else:	  
         GuestOSFreeSpace=Palist[j-1]-mpdImagePAEnd[0]
         GuestOSFreeSpace=GuestOSFreeSpace/1024.0
         SensorPDFreeSpace=AlignedImageEnd-mpdImagePAEnd[j-1]
         SensorPDFreeSpace=SensorPDFreeSpace/1024.0
 else:
      if j1 != 0:
         GuestOSFreeSpace=AlignedImageEnd-uimagePAEnd[k-1]
         GuestOSFreeSpace=GuestOSFreeSpace/1024.0  	  
      else:
         GuestOSFreeSpace=AlignedImageEnd-mpdImagePAEnd[j-1]
         GuestOSFreeSpace=GuestOSFreeSpace/1024.0   
 if Image_SizeMB >= AlignedImageSizeMB:     
        print ('*****************LPASS Memory FootPrint************************')
        print "Total Image size declared in MB			:%.4f" % Image_SizeMB
        print "Total Image Size Consumed in MB			:%.4f" % AlignedImageSizeMB
        if alist_len >= 2:	
            print "Free Space in GuestOS in KB(1MB Align Btw GuestPD & SensorPD):%.4f" % GuestOSFreeSpace
            print "Free Space in SensorsPD in KB(Image end align to 256KB)	     :%.4f" % SensorPDFreeSpace
            print ('Free Space in PHYPOOL in KB:')		
            print ('   DEFAULT_PHYSPOOL - (Static(Text+Data) Memory size + Heap Memory size + GuestOSFreeSpace + SensorsPDFreeSpace + QURTTraceBuffer)')
        else:
            print "Free Space in GuestPD in KB(Image end align to 256KB)	:%.4f" % GuestOSFreeSpace
            print ('Free Space in PHYSPOOL in KB:')
            print ('   DEFAULT_PHYSPOOL - (Static(Text+Data) Memory size + Heap Memory size + GuestOSFreeSpace + QURTTraceBuffer)')
        print "   =%.4f-%.4f" % (Image_SizeMB,AlignedImageSizeMB)
        ImageDiff=float(Image_SizeMB-AlignedImageSizeMB)
        ImageDiff=float(ImageDiff*1024.00)
        if alist_len >= 2:
            print "   =%.4f " % ImageDiff
        else:
            print "   =%.4f " % ImageDiff
 else:
        print ('**********************************************************************')
        print ('Error: Image Size greater than DEFAULT_PHYSPOOL defined in qdsp6.xml\n')
        print ('**********************************************************************')
        print "Total Image size declared in MB			:%.4f" % Image_SizeMB
        print "Total Image Size Consumed in MB			:%.4f" % AlignedImageSizeMB
        if alist_len >= 2:	
            print ('Required Extra Memory size in KB:')			
            print ('   (Static(Text+Data) Memory size + Heap Memory size + GuestOSFreeSpace + SensorsPDFreeSpace + QURTTraceBuffer) - DEFAULT_PHYSPOOL')
        else:
            print ('Required Extra Memory size in KB:')	
            print ('   (Static(Text+Data) Memory size + Heap Memory size + GuestOSFreeSpace + SensorsPDFreeSpace + QURTTraceBuffer) - DEFAULT_PHYSPOOL')		
        print "   =%.4f-%.4f" % (AlignedImageSizeMB,Image_SizeMB)
        ImageDiff=AlignedImageSizeMB-Image_SizeMB
        ImageDiff=ImageDiff*1024.0
        print "   =%.4f" % ImageDiff	
        shutil.rmtree('obj')
        delFile="dsp.elf"
		# don't remove dsp.elf for 8996 until the LLVM tool chain fixes MPD address issue
        if os.environ.get('CHIPSET', None) != 'msm8996' and os.path.isfile(delFile):
           os.remove(delFile)
        #os.remove("/obj")
		
