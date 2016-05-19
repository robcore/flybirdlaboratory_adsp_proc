""" compare_lists.py script

Compares two lists and finds intersection between them.

Usage:
compare_lists.py -a list_a_file -b list_b_file
Eg. compare_lists.py -a lista.txt -b listb.txt

"""

import sys
import os
from optparse import OptionParser, OptionGroup

##
## return a intersection b, a not b, b not a
def compare_lists(list_a,list_b):
   a=set(list_a);
   b=set(list_b);
   return list(a.intersection(b)),list(a.difference(b)),list(b.difference(a))
   
def compare_lists_and_print(list_a,list_b, name_a, name_b,csv_file_name):
   if not csv_file_name=='':
    try:
        f=open(csv_file_name,'wb');
    except IOError as e:
       sys.exit('>>> Error: file '+csv_file_name+' could not be opened. Exiting.'+str(e));
      
   a_and_b, a_not_b, b_not_a = compare_lists(list_a,list_b);
   max_len=len(a_and_b);
   if max_len < len(a_not_b):
      max_len=len(a_not_b);
   if max_len < len(b_not_a):
      max_len=len(b_not_a);
   
   s='in '+str(name_a)+' and in '+str(name_b)+',   in '+str(name_a)+' not in '+str(name_b)+',   in '+str(name_b)+' not in '+str(name_a);
   if csv_file_name=='':
      print s
   else:
      f.writelines(s+'\n');
   
   for i in range(max_len):
      s='';
      if i<len(a_and_b):
         s+=str(a_and_b[i])
      s+=','
      if i<len(a_not_b):
         s+=str(a_not_b[i])     
      s+=','
      if i<len(b_not_a):
         s+=str(b_not_a[i])
      s+=','
      if csv_file_name=='':
         print s
      else:
         f.writelines(s+'\n');
   if not csv_file_name=='':
      f.close();
   return a_and_b, a_not_b, b_not_a
   
if __name__ == '__main__':
   #===========================================================================
   usage = r'Compares two lists and finds intersection & differences between them.'
   parser = OptionParser(description=usage)
   required_group = OptionGroup(parser, "Required Arguments")
   required_group.add_option("-a","--file_a", default='', help="first file containing one element per line") 
   required_group.add_option("-b","--file_b", default='', help="second file containing one element per line") 

   opt_group = OptionGroup(parser, "Optional Arguments")
   opt_group.add_option("-c", "--csv", default='', help="CSV file name for comparing symbols")

   parser.add_option_group(required_group)
   parser.add_option_group(opt_group)

   (options, args) = parser.parse_args()

   a_file_name=options.file_a;
   b_file_name=options.file_b;
   csv=options.csv;

   if a_file_name == '' or b_file_name == '':
      sys.exit(">>> Error: Insufficient Arguments, use -h option to see required arguments")
   
   list_a=[];
   with open(a_file_name,'rb') as f:
      for i in f:
         i=i.strip();
         if len(i)>0:
            list_a.append(i);
   
   #print list_a
   list_b=[];
   with open(b_file_name,'rb') as f:
      for i in f:
         i=i.strip();
         if len(i)>0:
            list_b.append(i);

   compare_lists_and_print(list_a,list_b, 'A', 'B',csv)
         
   print 'Done'
   print 
