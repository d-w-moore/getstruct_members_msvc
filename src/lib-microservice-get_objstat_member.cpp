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

    std::string a {"ERROR:general_fail"};
    rodsObjStat_t* input = static_cast<rodsObjStat_t*>(_param1->inOutStruct);
    int result = 0;
    if (std::strcmp(_param1->type, RodsObjStat_MS_T) != 0)
    {
        return USER_PARAM_TYPE_ERR;
    }
    else {
        const char *field =  parseMspForStr(_param2);
        if (field == nullptr) return USER__NULL_INPUT_ERR;

        static const map_to_handler<rodsObjStat_t> m 
        {
            GET_STRUCT_MEMBER(rodsObjStat_t, objType),
            GET_STRUCT_MEMBER(rodsObjStat_t, objSize),
        };

        try 
        {
            a = m.at(field)(input);
        }
        catch(std::out_of_range) 
        {
            result = -1;
        }
    }
    fillStrInMsParam(_param3,a.c_str());
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

