test {

      *Param3 = "-"
       msiObjStat("*name",*stat)
       msiget_objstat_member( *stat, "objType", *Param3 )
       writeLine("stdout", *Param3)
       if ( *Param3 == "1" ) { # 1 => data object, 2 => collection
         msiget_objstat_member( *stat, "objSize", *Param3 )
         writeLine("stdout", *Param3)
       }
}

INPUT *name=$"/tempZone/home/rods/myfile.txt"
OUTPUT ruleExecOut
