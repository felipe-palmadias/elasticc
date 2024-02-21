#include "esclient.h"
#include <string.h>
#include <stdlib.h>


char* _esclient_base_url;

void esclient_init(char* base_url) {

	if (_esclient_base_url != NULL) {
		free(_esclient_base_url);
	}

	_esclient_base_url = (char*)malloc((strlen(base_url) + 1) * sizeof(char));

	strcpy(_esclient_base_url, base_url);
}

char* base_url() {
	return _esclient_base_url;
}


void esclient_close() {
	free(_esclient_base_url);
}
