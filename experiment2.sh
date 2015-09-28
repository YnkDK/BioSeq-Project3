#!/usr/bin/env bash
# What is the score of the alignment of the first 5 sequences in brca1-testseqs.fasta (i.e. brca1_bos_taurus,
# brca1_canis_lupus, brca1_gallus_gallus, brca1_homo_sapiens, and brca1_macaca_mulatta) as computed by your
# program sp_approx?

# Which of the 5 sequences is choosen as the 'center string'?

# When the center string has been fixed, there are fak(4)=24 different orders in which you can choose to add the
# remaining 4 sequences. Compute (and report) the score of the alignment that you produce for each of these orders.
# Comment on the differences (if any) that you observe.

if ! ./make.sh >/dev/null; then
    echo "=============================================="
    echo "================ MAKE FAILED! ================"
    echo "=============================================="
    exit $?
fi
./bin/BioSeq_Project3 perm_exp input/brca1-testseqs_5.fasta