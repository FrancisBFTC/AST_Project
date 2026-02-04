#include "astlib.h"

int main(int argc, char *argv[])
{
	AST *tree = parse("3 + 4 * (2 + 1)");
	printf("Resultado: %d\n", eval(tree)); // 15	
	return 0;
}
