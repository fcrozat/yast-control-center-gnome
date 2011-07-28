#!/bin/sh
DIRNAME=`dirname $0`
(
for file in control-center.c gnome-control-center.c shell.ui; do
	diff -u "${DIRNAME}/../cut-n-paste/shell/$file" "${DIRNAME}/../$file"
done
) > "${DIRNAME}/gnome-control-center.patch"
