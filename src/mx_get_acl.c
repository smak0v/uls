#include "uls.h"

char *mx_get_acl(char *dirname) {
    acl_t acl = acl_get_file(dirname, ACL_TYPE_EXTENDED);
    char *acl_text = NULL;

    if (acl) {
        acl_text = acl_to_text(acl, NULL);
        acl_free(acl);
    }
    return acl_text;
}
