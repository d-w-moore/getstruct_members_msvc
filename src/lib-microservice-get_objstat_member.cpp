// =-=-=-=-=-=-=-
// irods includes
#include "irods_error.hpp"
#include "irods_ms_plugin.hpp"

// =-=-=-=-=-=-=-
// stl includes
#include <cstring>
#include <cstdlib>
#include <string>
#include <cstring>
#include <regex.h>


int msiget_objstat_member(
    msParam_t*      _param1,
    msParam_t*      _param2,
    msParam_t*      _param3,
    ruleExecInfo_t* _rei ) {

    std::string a {""};
    rodsObjStat_t* input = static_cast<rodsObjStat_t*>(_param1->inOutStruct);

    if (strcmp(_param1->type, RodsObjStat_MS_T)) {
        return USER_PARAM_TYPE_ERR;
    }
    else {
        const char *field = parseMspForStr (_param2);
        if (field == NULL) return USER__NULL_INPUT_ERR;

        if (!strcmp("objSize",field)) a = std::to_string( input->objSize );
        else if (!strcmp("objType",field)) a = std::to_string( input->objType );
    }
    fillStrInMsParam(_param3,a.c_str());
    return 0;
}

extern "C"
irods::ms_table_entry* plugin_factory() {
    irods::ms_table_entry* msvc = new irods::ms_table_entry(3);
    msvc->add_operation<
        msParam_t*,
        msParam_t*,
        msParam_t*,
        ruleExecInfo_t*>("msiget_objstat_member",
                         std::function<int(
                             msParam_t*,
                             msParam_t*,
                             msParam_t*,
                             ruleExecInfo_t*)>(msiget_objstat_member));
    return msvc;
}

