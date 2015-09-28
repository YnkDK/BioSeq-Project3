require(ggplot2)
# Read the statistics for computing S
data <- read.table("output/testseqs.out", sep = "\t", header = TRUE)

data$ratio <- data$approx / data$exact

# Prepare the output - Use the standard A4 size (in inches)
pdf(file = "output/testseqs.pdf", width = 11.69, height = 8.27)
# Plot the ratio for all n, with a red line defining what the bound should be below
ggplot(data, aes(n, ratio)) + 
  geom_point() +
  ylab("Ratio") +
  geom_hline(yintercept=4/3, color="red") +
  theme(text = element_text(size=20),
        axis.text.x = element_text(vjust=1)) 
# Close PDF file
garbage <- dev.off()