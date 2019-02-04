# Amino Acids translation

# Constants needed for translation
# DO NOT EDIT!
START_CODON = "AUG"
STOP_CODONS = ["UAA","UAG","UGA"]
RNA_TO_AAs = { 'ACU' => 'Thr', 'ACC' => 'Thr', 'ACA' => 'Thr', 'ACG' => 'Thr',
  'GCU' => 'Ala', 'GCC' => 'Ala', 'GCA' => 'Ala', 'GCG' => 'Ala',
  'UAU' => 'Tyr', 'UAC' => 'Tyr', 'CAU' => 'His', 'CAC' => 'His',
  'CAA' => 'Gln', 'CAG' => 'Gln', 'AAU' => 'Asn', 'AAC' => 'Asn',
  'AAA' => 'Lys', 'AAG' => 'Lys', 'GAU' => 'Asp', 'GAC' => 'Asp',
  'GAA' => 'Glu', 'GAG' => 'Glu', 'UGU' => 'Cys', 'UGC' => 'Cys',
  'UGG' => 'Trp', 'CGU' => 'Arg', 'CGC' => 'Arg', 'CGA' => 'Arg',
  'CGG' => 'Arg', 'AGU' => 'Ser', 'AGC' => 'Ser', 'AGA' => 'Arg',
  'AGG' => 'Arg', 'GGU' => 'Gly', 'GGC' => 'Gly', 'GGA' => 'Gly',
  'GGG' => 'Gly', 'AUG' => 'Met', 'UUU' => 'Phe', 'UUC' => 'Phe',
  'UUA' => 'Leu', 'UUG' => 'Leu', 'CUC' => 'Leu', 'CUG' => 'Leu',
  'AUU' => 'Ile', 'AUC' => 'Ile', 'AUA' => 'Ile', 'GUU' => 'Val',
  'GUC' => 'Val', 'GUA' => 'Val', 'GUG' => 'Val', 'UCU' => 'Ser',
  'UCC' => 'Ser', 'UCA' => 'Ser', 'UCG' => 'Ser', 'CCU' => 'Pro',
  'CCC' => 'Pro', 'CCA' => 'Pro', 'CCG' => 'Pro', }

  # Given: a string containing DNA characters
  # Return: a string of capitalized DNA letters only
  #
  # DNA Nucleotides can be A,T,G, or C 
  #
def parse_dna(str)
    dna = String::new  
    str.upcase.each_char do |chr|
        if chr.match("A") || chr.match("C") || chr.match("T") || chr.match("G")
            dna = dna + chr
        end
    end
    dna  
end

# Given: a string of DNA characters
# Return: a string of RNA
#
# DNA Nucleotides can be A,T,G, or C 
# RNA Nucleotides can be A,U,G, or C 
# Transcription replaces T with U.
#
def transcribe(dna)
    dna.gsub!("T","U")
    dna             
end

# Given: a string of RNA characters
# Return: an array of codons
#
# Codons are groups of three nucleotides at a time.
# Nucleotides can be A,U,G, or C
# Any leftover nucleotides that don't fit into  codon are ignored
# Ignore all other characters
#  (e.g. UUUU parses to ['UUU'])
#
# Hint: String's each_char may be a helpful method
# Hint: using split is NOT recommended
# Hint: complex regular expressions are also not a good idea
#
def parse_codons(str)
    arr = Array.new
    codon = String::new
    len = str.length - (str.length % 3)
    str[0..len].each_char do |chr|
        codon.concat(chr)
        if codon.length == 3
            arr = arr.push(codon.dup)
            codon.clear
        end
    end
    arr
end

# Given:  an array of capitalized codons
# Return: a string of space-delimited Amino acids
#
# Translation doesn't start until the START_CODON is reached
# Translation stops when one of the STOP_CODONs is reached
# Translation stops when one of the STOP_CODONs is reached,
#   but only after translation started
# We are not handling any start-stop-start scenarios.
#
def translate(codons)
    st = String::new
    if codons.size == 0
        return st
    end
    i = codons.index(START_CODON)
    stop = 0
    codons[i..codons.size].each do |x|
        STOP_CODONS.each do |y|
            if x.match(y)
                stop = 1
            end
        end
        break if stop == 1
        st.concat(RNA_TO_AAs[x] + " ")
    end
    st                
end
