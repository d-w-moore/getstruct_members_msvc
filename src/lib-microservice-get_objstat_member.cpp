// =-=-=-=-=-=-=-
// irods includes
#include "irods_error.hpp"
#include "irods_ms_plugin.hpp"

// =-=-=-=-=-=-=-
// stl includes
#include <cstring>
#include <cstdlib>
#include <string>
#include <functional>
#include <map>
#include <cstring>
//#include <regex.h>

template<typename T, typename U=std::string>
using map_to_handler = std::map<std::string, 
                                std::function<U(T*)>>;

#define GET_STRUCT_MEMBER(structType, memberName) \
    {   \
        #memberName, \
        [](structType* p){return std::to_string(p->memberName);} \
    }

int msiget_objstat_member(
    msParam_t*      _param1,
    msParam_t*      _param2,
    msParam_t*      _param3,
    ruleExecInfo_t* _rei ) {

    std::string a {""};
    rodsObjStat_t* input = static_cast<rodsObjStat_t*>(_param1->inOutStruct);

    int result = -1; // Unknown iRODS error.

    if (std::strcmp(_param1->type, RodsObjStat_MS_T) != 0)
    {
        return USER_PARAM_TYPE_ERR;
    }
    else {
        const char *field;
        if (_param2 == nullptr ||
            (field = parseMspForStr(_param2)) == nullptr) return USER__NULL_INPUT_ERR;

        static const map_to_handler<rodsObjStat_t> handlers
        {
            GET_STRUCT_MEMBER(rodsObjStat_t, objType),
            GET_STRUCT_MEMBER(rodsObjStat_t, objSize),
        };

        try 
        {
            a = handlers.at(field)(input);
            result = 0;             // Success.
        }
        catch(std::out_of_range) 
        {
            result = SYS_INVALID_INPUT_PARAM;
        }
    }
    if (result == 0) fillStrInMsParam(_param3,a.c_str());
    return result;
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

