#! /bin/sh

# Copyright (C) 2024 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only
#
# This is a small script to copy the required files from a sdlgamecontrollerdb tarball
# into 3rdparty/sdlgamecontrollerdb/ . Documentation, tests, demos etc. are not imported.

if [ $# -ne 2 ]; then
    echo "Usage: $0 openxr_tarball_dir/ \$QTDIR/src/3rdparty/sdlgamecontrollerdb/"
    exit 1
fi

SRC_DIR=$1
TARGET_DIR=$2

if [ ! -d "$SRC_DIR" -o ! -r "$SRC_DIR" -o ! -d "$TARGET_DIR" -o ! -w "$TARGET_DIR" ]; then
    echo "Either the sdlgamecontrollerdb source dir or the target dir do not exist,"
    echo "are not directories or have the wrong permissions."
    exit 2
fi

# with 1 argument, copies SRC_DIR/$1 to TARGET_DIR/$1
# with 2 arguments, copies SRC_DIR/$1 to TARGET_DIR/$2
copy_file_or_dir() {
    if [ $# -lt 1 -o $# -gt 2  ]; then
        echo "Wrong number of arguments to copy_file_or_dir"
        exit 3
    fi

    SOURCE_FILE=$1
    if [ -n "$2" ]; then
        DEST_FILE=$2
    else
        DEST_FILE=$1
    fi

    mkdir -p "$TARGET_DIR/$(dirname "$SOURCE_FILE")"
    cp -R "$SRC_DIR/$SOURCE_FILE" "$TARGET_DIR/$DEST_FILE"
}

FILES="
    README.md
    LICENSE
    gamecontrollerdb.txt
"

for i in $FILES; do
    copy_file_or_dir "$i"
done
