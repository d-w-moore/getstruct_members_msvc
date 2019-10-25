test
{
    *Param3 = "-"
    msiObjStat("*name",*stat)
    msiget_objstat_member( *stat, "objType", *Param3 )
    writeLine("stdout", "objType is *Param3 (1 = data object, 2 = collection)")
    if ( *Param3 == "1" )
    {
        *retn = errorcode( msiget_objstat_member( *stat, "objSize", *Param3 ) )
        writeLine("stdout", "size is: *Param3")
    }
}

INPUT *name=$"/tempZone/home/rods/myfile.txt"
OUTPUT ruleExecOut
