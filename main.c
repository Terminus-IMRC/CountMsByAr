#include "libms.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	ms_state_t st;
	ms_counters_t cnt;
	ms_bin_seq_read_t mbr;
	ms_bin_ret_t ret;
	int *ms;
	int *ar_base;
	int i;

	ms_init(M_X, MS_ORIGIN_ONE, &st);
	ms = ms_alloc(&st);
	ms_bin_seq_read_open(M_FILENAME, MS_BIN_SEQ_READ_FLAG_NONE, &mbr, &st);
	ms_bin_seq_read_set_buffer(0x10000, &mbr, &st);

	ar_base = malloc(ms_X(&st) * sizeof(int));
	if (ar_base == NULL) {
		fprintf(stderr, "error: failed to malloc ar_base\n");
		exit(EXIT_FAILURE);
	}

	ar_base[0] = 1;
	for (i = 1; i < ms_X(&st); i ++)
		ar_base[i] = ar_base[i - 1] * ms_Ceilings(&st);

	ms_counters(&cnt, M_LINEC, &st);
	do {
		ret = ms_bin_seq_read_next(ms, &mbr, &st);
		int j;
		int key = 0;
		for (i = cnt.start, j = 0; i < cnt.end; i += cnt.step, j ++)
			key += (ms[i] - 1) * ar_base[j];
		printf("%d\n", key);
	} while (ret != MS_BIN_RET_EOF);

	free(ar_base);
	ms_bin_seq_read_close(&mbr, &st);
	ms_free(ms, &st);
	ms_finalize(&st);

	return 0;
}
