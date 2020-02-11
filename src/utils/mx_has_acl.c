#include "uls.h"

bool mx_has_acl(char *dirname) {
    acl_t acl = acl_get_file(dirname, ACL_TYPE_EXTENDED);
    bool has_acl = acl ? true : false;

    acl_free(acl);
    return has_acl;
}
