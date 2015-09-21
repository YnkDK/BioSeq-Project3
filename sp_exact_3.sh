#!/usr/bin/env bash
if ! ./make.sh >/dev/null; then
    echo "=============================================="
    echo "================ MAKE FAILED! ================"
    echo "=============================================="
    exit $?
fi
./bin/BioSeq_Project3