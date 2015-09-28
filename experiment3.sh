#!/usr/bin/env bash
# Make an experiment comparing the scores of the alignments computed by sp_exact_3 and sp_approx that validates that
# the approximation ratio of sp_approx is 2(k-1)/k for k sequences. i.e 4/3 for three sequences.

# You should use the testdata in testseqs.zip that contains 20 fasta files (testseqs_10_3.fasta, testseqs_20_3.fasta,
# ..., testseqs_200_3.fasta) each containing 3 sequences of lengths 10, 20, ..., 200.

# For each triplet of sequences (i.e. each fasta file), you should compute the optimal score of an MSA using sp_exact_3
# and the score of the alignment produced by sp_approx. Make a graph in which you plot the ratio of the computed scores
# for each sequence length. Comment on what you observe.

if ! ./make.sh >/dev/null; then
    echo "=============================================="
    echo "================ MAKE FAILED! ================"
    echo "=============================================="
    exit $?
fi
# Create dir if not present
mkdir -p output
# Set header
echo -e "n\tapprox\texact" > output/testseqs.out

# Loop through all testseqs given in the zip-file
for f in input/testseqs_*_3.fasta; do
    # Record the output
    ./bin/BioSeq_Project3 both ${f} >> output/testseqs.out
done
echo "Plotting graph"
Rscript plot_ratio.R
evince output/testseqs.pdf