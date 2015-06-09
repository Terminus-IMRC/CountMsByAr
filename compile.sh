#!/usr/bin/env bash

# Do not run me; just source me

set -x

rm -rf bin
mkdir -p bin

for cmd_X in 4 5; do
	test $cmd_X -eq 4 && FILENAME=/home/pi/public_html/ms/ms4.bin
	test $cmd_X -eq 5 && FILENAME=/home/pi/public_html/ms/ms5saf.bin
	for l in VERT HORIZ; do
		for c in `seq 0 $((cmd_X - 1))`; do
			gcc -O2 -pipe main.c -Wall -Wextra $CFLAGS $LDLIBS -lms -DM_X=$cmd_X -DM_FILENAME=\"$FILENAME\" "-DM_LINEC=MS_LINE_$l($c, &st)" -o bin/$cmd_X-$l-$c
		done
	done
	for l in DIAG; do
		for c in 0 1; do
			gcc -O2 -pipe main.c -Wall -Wextra $CFLAGS $LDLIBS -lms -DM_X=$cmd_X -DM_FILENAME=\"$FILENAME\" "-DM_LINEC=MS_LINE_$l($c, &st)" -o bin/$cmd_X-$l-$c
		done
	done
done

set +x
