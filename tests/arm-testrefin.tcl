#!/usr/bin/expect -f
#
# Copyright 2014, NICTA
#
# This software may be distributed and modified according to the terms of
# the BSD 2-Clause license. Note that NO WARRANTY is provided.
# See "LICENSE_BSD2.txt" for details.
#
# @TAG(NICTA_BSD)
#

source [file join [file dirname [info script]] procs.tcl]

set timeout 600

spawn make arm_testrefin_defconfig
check_exit

source [file join [file dirname [info script]] build.tcl]

source [file join [file dirname [info script]] run-arm.tcl]
wait_for "client: result was 42"
wait_for "client: result was b = {0..99}"