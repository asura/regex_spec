#include <stdio.h>
#include <string.h>

#include <cspec.h>
#include <cspec_output_verbose.h>

DEFINE_DESCRIPTION(regcomp);

int main()
{
    int ret = 0;

    ret += CSpec_Run(DESCRIPTION(regcomp), CSpec_NewOutputVerbose());

    return ret;
}
