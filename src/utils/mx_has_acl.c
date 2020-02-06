#include "uls.h"

bool mx_has_acl(char *dirname) {
    return acl_get_file(dirname, ACL_TYPE_EXTENDED) ? true : false; 
}
