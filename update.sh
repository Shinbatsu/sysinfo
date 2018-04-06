#!/bin/bash

CURRENT="$1"

if [[ -z "$CURRENT" || ! -e "$CURRENT" ]]; then
    printf "\033[7;49;31mInvalid file!\033[m\n"
    exit 1
fi

SAVE_DIR=".makefile_saves"
mkdir -p "$SAVE_DIR"

SAVE_NAME="$(date +"%Y-%m-%d_%T")"
CUR_FILE="$SAVE_DIR/$SAVE_NAME"

LAST_SAVE=$(find "$SAVE_DIR" -type f | sort -r | head -n1)

if [[ -z "$LAST_SAVE" || ! $(diff "$CURRENT" "$LAST_SAVE") ]]; then
    cp "$CURRENT" "$CUR_FILE"
    printf "\033[7;49;34mSave created at: %s\033[m\n" "$CUR_FILE"
elif [[ "$LAST_SAVE" != "$CUR_FILE" ]]; then
    mv "$LAST_SAVE" "$CUR_FILE"
fi

{
    sed '/^FILES/,/\Z/d' "$CUR_FILE"
    echo "FILES =\\"
    find src -type f \( -name "*.cpp" -o -name "*.c" \) \
        | sed 's|src/||; s|$|\\|'
    sed '$ s/\\$//'

    echo ""
    sed -n '/OBJ_DIR/,$p' "$CUR_FILE"
} > "$CURRENT"

printf "\033[7;49;34mSuccessfully updated the Makefile!\033[m\n"
