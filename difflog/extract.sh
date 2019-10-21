#!/usr/bin/env bash

# Example run: ./extract.sh ObjectPointer.py

grep 'parse_rules' "$@" | \
sed 's/.*\[\"\(.*\).\"\].*/\1/' | \
sed "s/.*\[\'\(.*\).\'\].*/\1/" | \
sed 's/ :- /, /' | \
sed 's/^/)),/' | nl | sed 's/^ *//' | \
sed 's/^/Value(0.5, Token(/' | \
sed 's/^/,/' | nl | sed 's/^ *//' | \
sed 's/^/Rule(/' | sed 's/$/)/' | sed 's/.*/&,/'
