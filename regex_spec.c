#include <cspec.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>

DESCRIBE(regcomp, "int regcomp(regex_t *preg, const char *regex, int cflags)") {
    IT("returns zero in normal case") {
        int ret;
        regex_t reg;
        char regex[1024];

        strncpy(regex, "^regex", sizeof(regex));
        ret = regcomp(&reg, regex, REG_EXTENDED);
        SHOULD_EQUAL(0, ret);
    } END_IT;
} END_DESCRIBE;
