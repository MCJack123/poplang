//
//  main.c
//  poplang
//
//  Created by JackMacWindows on 4/21/20.
//  Copyright © 2020 MCJack123. All rights reserved.
//

#include "parse.h"
#include "exec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char * argv[]) {
	if (argc < 2) {
		fprintf(stderr, "Usage: %s <file>\n       %s -c <input> <output>\n       %s -e\n", argv[0], argv[0], argv[0]);
		return 1;
	}
	if (strcmp(argv[1], "-c") == 0 && argc >= 4) {
		FILE * fp = fopen(argv[2], "r");
		if (fp == NULL) {
			fprintf(stderr, "Could not open file %s\n", argv[2]);
			return 3;
		}
		char * buf = NULL;
		size_t size = 0;
		while (!feof(fp)) {
			buf = realloc(buf, size+512);
			size += fread(buf, 1, 512, fp);
			if (size % 512 > 0) break;
		}
		fclose(fp);
		size_t outsize = poplang_get_program_size(buf, size);
		char * out = (char*)malloc(outsize);
		poplang_parse_program(buf, size, out, outsize);
		free(buf);
		fp = fopen(argv[3], "wb");
		if (fp == NULL) {
			fprintf(stderr, "Could not open file %s\n", argv[3]);
			return 3;
		}
		fwrite(out, outsize, 1, fp);
		fclose(fp);
		free(out);
	} else if (strcmp(argv[1], "-e") == 0) {
		fprintf(stderr, "Not implemented\n");
		return 2;
	} else {
		FILE * fp = fopen(argv[1], "rb");
		if (fp == NULL) {
			fprintf(stderr, "Could not open file %s\n", argv[1]);
			return 3;
		}
		char * buf = NULL;
		size_t size = 0;
		while (!feof(fp)) {
			buf = realloc(buf, size+512);
			size += fread(buf, 1, 512, fp);
			if (size % 512 > 0) break;
		}
		fclose(fp);
		poplang_initialize(buf, size);
		poplang_execute();
		poplang_deinitialize();
		free(buf);
	}
	return 0;
}
