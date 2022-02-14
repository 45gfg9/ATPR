#!/bin/sh

# control in|out <type> <recipient> <request> <value> <index>
/Users/45gfg9/Documents/Project/v-usb/examples/usbtool/usbtool -PATPR -d42,22,160,187,0,0xfe control out 2 0 0x99 0x88 0x77

# /Users/45gfg9/Documents/Project/v-usb/examples/usbtool/usbtool  -PATPR -n5 control in 2 0 0x99 0x88 0x77
