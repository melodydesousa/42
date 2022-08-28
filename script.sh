#!/bin/bash

valgrind ./so_long  &> VALGRIND_LOG
valgrind ./so_long map/.ber  &>> VALGRIND_LOG
valgrind ./so_long map/map.berbet  &>> VALGRIND_LOG
valgrind ./so_long map/empty.ber   &>> VALGRIND_LOG
valgrind ./so_long map/nocollect.ber  &>> VALGRIND_LOG
valgrind ./so_long map/noexit.ber  &>> VALGRIND_LOG
valgrind ./so_long map/nomap.txt  &>> VALGRIND_LOG
valgrind ./so_long map/noplayer.ber  &>> VALGRIND_LOG
valgrind ./so_long map/nosquare.ber  &>> VALGRIND_LOG
valgrind ./so_long map/nowall1.ber  &>> VALGRIND_LOG
valgrind ./so_long map/nowall2.ber  &>> VALGRIND_LOG
valgrind ./so_long map/nowall3.ber  &>> VALGRIND_LOG
valgrind ./so_long map/nowall4.ber  &>> VALGRIND_LOG
valgrind ./so_long map/oneline.ber  &>> VALGRIND_LOG
valgrind ./so_long map/map.ber  &>> VALGRIND_LOG
valgrind ./so_long map/bigmap.ber  &>> VALGRIND_LOG
valgrind ./so_long map/toomuchplayer.ber  &>> VALGRIND_LOG
valgrind ./so_long map/toomuchexit.ber  &>> VALGRIND_LOG
valgrind ./so_long map/toobigmap.ber  &>> VALGRIND_LOG
clear
grep -A3 'Command:\|HEAP SUMMARY:' VALGRIND_LOG
