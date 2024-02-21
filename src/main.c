#include <stdio.h>
#include "esclient.h"

int main() {

	printf("initializing...\n");
	esclient_init("an url");

	printf("hello %s \n", base_url());

	esclient_close();

	return 0;
}
