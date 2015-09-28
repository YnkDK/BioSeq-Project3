#!/usr/bin/env bash
# What is the score of an optimal aligment of the first 3 sequences in brca1-testseqs.fasta (i.e. brca1_bos_taurus,
# brca1_canis_lupus and brca1_gallus_gallus) as computed by your program sp_exact_3? How does an optimal alignment
# look like?

if ! ./make.sh >/dev/null; then
    echo "=============================================="
    echo "================ MAKE FAILED! ================"
    echo "=============================================="
    exit $?
fi
./bin/BioSeq_Project3 sp_exact_3 input/brca1-testseqs.fasta compute_d print_alignments print_score verify
