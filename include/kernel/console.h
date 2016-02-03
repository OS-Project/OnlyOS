//
// Created by Thibault PIANA on 10/11/15.
//
#ifdef __cplusplus
extern "C" {
#endif

#ifndef ONLYOS_KERNEL_CONSOLE_H
#define ONLYOS_KERNEL_CONSOLE_H

typedef int (*pfnCmdLine)(int argc, char *argv[]);
typedef struct
{
    // A pointer to a string containing the name of the command.
    const char *pcCmd;
    // A function pointer to the implementation of the command.
    pfnCmdLine pfnCmd;
    // A pointer to a string of brief help text for the command.
    const char *pcHelp;
} tCmdLineEntry;


tCmdLineEntry g_sCmdTable[] =
        {
                { "help",   Cmd_help,      " : Display list of commands" },
                { 0, 0, 0 }
        };
#endif

#ifdef __cplusplus
}
#endif