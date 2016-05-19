#===============================================================================
#
# Copyright (c) 2014 Qualcomm Technologies, Inc. All Rights Reserved.
# Qualcomm Technologies Proprietary and Confidential.
#
#===============================================================================

"""
Created on Nov 19, 2014

@author: aehrlich

This module provides various helper functions which don't have a parent category
"""


def nice_binary_to_string(bin_data, sep=':', length=30):
    return_data = []
    for i in xrange(0, len(bin_data), length):
        return_data.append(sep.join(hex(ord(b))[2:].rjust(2, '0') for b in bin_data[i:i+length]))

    return '\n'.join(return_data)

def nice_string_to_binary(data, sep=':'):
    return ''.join([chr(int(c, 16)) for c in sep.join(data.strip().split('\n')).split(sep)])

def nice_string_to_list(data, n=2):
    return [data[i:i+n] for i in xrange(0, len(data), n)]

def nice_string_to_multiline(data, length=30):
    return '\n'.join([data[i:i+length] for i in xrange(0, len(data), length)])

def nice_c_hex(data):
    retdata =  nice_binary_to_string(data, ':', 9)
    newdata = []
    for l in retdata.split('\n'):
        l_n = ['0x' + c for c in l.split(':')]
        newdata.append(', '.join(l_n))
    return '   ' + ',\n   '.join(newdata) + ','

def nice_hex_reversed(data):
    data = reversed(nice_binary_to_string(data, ':', len(data)).split(':'))
    return nice_string_to_binary(':'.join(data))

