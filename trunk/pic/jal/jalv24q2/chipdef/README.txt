pjal -- chip definition files
=============================

I tried to embed as little knowledge as possible into the backend so
difference PICs could be easily added. This describes what can be found
in these chip definition files.

chipdef.jal
-----------
This contains constants needed by the JAL libraries

Constants and variables needed for the PIC backend
--------------------------------------------------
var volatile byte _ind
var volatile byte _pcl
var volatile byte _status
var volatile byte _fsr
const        byte _irp    
const        byte _rp1    
const        byte _rp0    
const        byte _not_to 
const        byte _not_pd 
const        byte _z      
const        byte _dc     
const        byte _c      
var volatile byte _pclath 
const word   _fuses           default value for the config word
const word   _fuse_base       where in memory the config word is located

var volatile byte _pic_isr_w  this is used to hold W on entry to an ISR
                              and must be available in all banks; it doesn't
                              really matter if it's truly mirrored, but if 
                              common space is available that's best because
                              only one byte will be used instead of one per 
                              bank.

Architecture description
------------------------

pragma data      a list of the data areas
pragma code      maximum code size, in bytes
pragma eeprom    defines where in memory the EEPROM data should be stored
                 and the size
pragma fuse_def  defines available config word options. These become available
                 via the ``pragma target xxx'' pragmas. The format is:

                 pragma fuse_def {target} mask {
                   value '=' bitval
                   ...
                 }

                 Where {target} is the name used by ``pragma target xxx'' and
                 ``value'' is a list of possible values.

                 For example:

                 pragma fuse_def protection 0b10000000000000 {
                   on  = 0b00000000000000
                   off = 0b01000000000000
                 }

                 Defines target ``protection'' which has two possible values,
                 ``on'' and ``off''. This is combined with the config word
                 as follows:

                 _fuses = (fuses & mask) | value

