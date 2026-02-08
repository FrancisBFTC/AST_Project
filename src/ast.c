#include "astlib.h"

int main(int argc, char *argv[])
{
	bool state = false;
	AST *tree = parse("(281 - 394 + 53 + (9 - 7 * 3) - 1) / 2");
	printf("Resultado: %d\n", eval(tree, &state)); // -36	
	return 0;
}
