#include "builtin.h"

#define main main_echo

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	return (1);
}