#include <config.h>

#include <stdio.h>
#include <stdlib.h>

#include "internal.h"
#include "testutils.h"
#include "command.h"

static void errorHandler(void *userData ATTRIBUTE_UNUSED,
                         virErrorPtr error ATTRIBUTE_UNUSED) {
}

int main(void) {
    int id = 0;
    int ro = 0;
    virConnectPtr conn;
    virDomainPtr dom;
    int status;
    virCommandPtr cmd;

    /* skip test if xend is not running */
    cmd = virCommandNewArgList("/usr/sbin/xend", "status", NULL);
    if (virCommandRun(cmd, &status) != 0 || status != 0) {
        virCommandFree(cmd);
        return EXIT_AM_SKIP;
    }
    virCommandFree(cmd);

    virSetErrorFunc(NULL, errorHandler);

    conn = virConnectOpen(NULL);
    if (conn == NULL) {
        ro = 1;
        conn = virConnectOpenReadOnly(NULL);
    }
    if (conn == NULL) {
        fprintf(stderr, "First virConnectOpen() failed\n");
        exit(EXIT_FAILURE);
    }
    dom = virDomainLookupByID(conn, id);
    if (dom == NULL) {
        fprintf(stderr, "First lookup for domain %d failed\n", id);
        exit(EXIT_FAILURE);
    }
    virDomainFree(dom);
    virConnectClose(conn);
    if (ro == 1)
        conn = virConnectOpenReadOnly(NULL);
    else
        conn = virConnectOpen(NULL);
    if (conn == NULL) {
        fprintf(stderr, "Second virConnectOpen() failed\n");
        exit(EXIT_FAILURE);
    }
    dom = virDomainLookupByID(conn, id);
    if (dom == NULL) {
        fprintf(stderr, "Second lookup for domain %d failed\n", id);
        exit(EXIT_FAILURE);
    }
    virDomainFree(dom);
    virConnectClose(conn);
    printf("OK\n");
    exit(EXIT_SUCCESS);

}
