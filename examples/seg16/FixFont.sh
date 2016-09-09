#!/bin/bash
#Purpose: rearrange a font table for a different pinout.
#
#License: GPL3
#
#Function: Read from stdin and send to stdout shift around some bits on it's way
# something like ;
#	sed 's/\\/\\\\/g' asciifont-pinout11.h|./FixFont.sh >asciifont-pinout12.h
#
#2016-08-27  Peter Sjoberg <peters-src AT techwiz DOT ca>
#	Created
#
#

echo "Reading stdin, sending to stdout" 1>&2

#   a1 a2
# f h j k b
#   g1 g2
# e n m l c
#   d1 d2 
#        dp

#11
#   a  b 
# h k l m c
#   i  j 
# g p o n d
#   e  f
#        dp

#12
#   a  b 
# h i j k c
#   p  l 
# g o m n d
#   f  e  
#        dp

#11  12
# e=>f    5=> 6
# f=>e    6=> 5
# i=>p    9=>16
# j=>l   10=>12
# k=>i   11=>09
# l=>j   12=>10
# m=>k   13=>11
# n=>n   14=>14
# o=>m   15=>13
# p=>o   16=>15

while IFS='' read line;do
    #    abcdefghijklmnop
    #    1234567890123456
    #             1111111
    #  0b0000001110001100, // K	  # old
    #  0b0000001100101001, // K   # new
    #
    #  0b0011000000001000, // 1   # old
    #  0b0011000000100000, // 1   # new
    #  0b0011000000000100
    #
    if ! echo "$line"|grep -q "^  0b";then
	echo "$line"
	continue
    fi
    Leadin="$(echo "$line"|cut -b1-4)"
    Bin="$(echo "$line"|cut -b5-20)"
    Char="$(echo "$line"|cut -b26-)"
    
    NBin=""
    NBin="$NBin$(echo $Bin|cut -b1)"	# 1
    NBin="$NBin$(echo $Bin|cut -b2)"	# 2
    NBin="$NBin$(echo $Bin|cut -b3)"	# 3
    NBin="$NBin$(echo $Bin|cut -b4)"	# 4
    NBin="$NBin$(echo $Bin|cut -b5)"	# 5
    NBin="$NBin$(echo $Bin|cut -b6)"	# 6
    NBin="$NBin$(echo $Bin|cut -b7)"	# 7
    NBin="$NBin$(echo $Bin|cut -b8)"	# 8
    NBin="$NBin$(echo $Bin|cut -b11)"	# 9
    NBin="$NBin$(echo $Bin|cut -b12)"	# 10
    NBin="$NBin$(echo $Bin|cut -b13)"	# 11
    NBin="$NBin$(echo $Bin|cut -b10)"	# 12
    NBin="$NBin$(echo $Bin|cut -b15)"	# 13
    NBin="$NBin$(echo $Bin|cut -b14)"	# 14
    NBin="$NBin$(echo $Bin|cut -b16)"	# 15
    NBin="$NBin$(echo $Bin|cut -b9)"	# 16
#    echo "$Leadin$NBin$Tail"
    IFS="$(echo -ne " \t\n")" printf "  0b$NBin, // %-5s # $Bin\n" "$Char "
done
