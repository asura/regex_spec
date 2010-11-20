#include <stdio.h>
#include <string.h>

#include <cspec.h>
#include <cspec_output_verbose.h>

DEFINE_DESCRIPTION(regcomp);
DEFINE_DESCRIPTION(regexec);

int main()
{
    int ret = 0;

    ret += CSpec_Run(DESCRIPTION(regcomp), CSpec_NewOutputVerbose());
    ret += CSpec_Run(DESCRIPTION(regexec), CSpec_NewOutputVerbose());

    return ret;
}
