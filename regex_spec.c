#include <cspec.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_MATCH_RESULT 2

void before(regex_t* preg, const char* const regex, int cflags)
{
    int ret = regcomp(preg, regex, cflags);
    if (0 != ret) {
        abort();
    }
}
void after(regex_t* preg)
{
    regfree(preg);
}

DESCRIBE(regcomp, "int regcomp(regex_t *preg, const char *regex, int cflags)") {
    IT("returns zero for a successful compilation") {
        int ret;
        regex_t reg;
        char regex[1024];

        strncpy(regex, "^regex", sizeof(regex));
        ret = regcomp(&reg, regex, REG_EXTENDED);
        SHOULD_EQUAL(0, ret);

        after(&reg);
    } END_IT;
} END_DESCRIBE;

DESCRIBE(regexec, "int regexec(const regex_t *preg, const char *string, size_t nmatch, regmatch_t pmatch[], int eflags)") {
    IT("returns zero for a successful match (eflags is REG_EXTENDED)") {
        int ret;
        regex_t reg;
        regmatch_t result[N_MATCH_RESULT];

        before(&reg, "^regex", REG_EXTENDED);

        ret = regexec(&reg, "regexp", N_MATCH_RESULT, result, 0);
        SHOULD_EQUAL(0, ret);
        SHOULD_EQUAL(0, result[0].rm_so);
        SHOULD_EQUAL(5, result[0].rm_eo);
        SHOULD_EQUAL(-1, result[1].rm_so);
        SHOULD_EQUAL(-1, result[1].rm_eo);
        
        after(&reg);
    } END_IT;

    IT("returns REG_NOMATCH for a match failure (eflags is REG_EXTENDED)") {
        int ret;
        regex_t reg;
        regmatch_t result[N_MATCH_RESULT];

        before(&reg, "^regex", REG_EXTENDED);

        ret = regexec(&reg, "regular expression", N_MATCH_RESULT, result, 0);
        SHOULD_EQUAL(REG_NOMATCH, ret);
        
        after(&reg);
    } END_IT;

    IT("returns zero for a successful match (cflags is REG_EXTENDED|REG_NOSUB)") {
        int ret;
        regex_t reg;

        before(&reg, "^regex", (REG_EXTENDED | REG_NOSUB));

        ret = regexec(&reg, "regexp", 0, NULL, 0);
        SHOULD_EQUAL(0, ret);
        
        after(&reg);
    } END_IT;

    IT("returns REG_NOMATCH for a match failure (cflags is REG_EXTENDED)") {
        int ret;
        regex_t reg;

        before(&reg, "^regex", (REG_EXTENDED | REG_NOSUB));

        ret = regexec(&reg, "regular expression", 0, NULL, 0);
        SHOULD_EQUAL(REG_NOMATCH, ret);
        
        after(&reg);
    } END_IT;
} END_DESCRIBE;
