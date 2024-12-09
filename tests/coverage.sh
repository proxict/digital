#!/bin/bash

command -v gcovr &>/dev/null || { echo "command 'gcovr' not found" >&2 && exit 1; }

find . -name '*gcda' -exec rm -rf {} \;
./bin/unittests
REPORTS_COUNT="$(find . -name '*gcda' | wc -l)"
[ "${REPORTS_COUNT}" -eq 0 ] && echo "No coverage data files found" >&2 && exit 1

OUTPUT_DIR=coverage

rm -rf "${OUTPUT_DIR}"

mkdir "${OUTPUT_DIR}" && \
(
    cd "${OUTPUT_DIR}" || exit 1
    gcovr \
        --verbose \
        --delete \
        --root "${1}" \
        --exclude='(?!(.*/include/prox/)).*' \
        --xml=coverage.xml \
        --html=index.html \
        --html-details \
        --exclude-throw-branches \
        --print-summary || { echo "Failed to generate coverage" >&2 && exit 1; }
)
