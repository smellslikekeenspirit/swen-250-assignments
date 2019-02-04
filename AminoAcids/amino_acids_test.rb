require_relative 'amino_acids'
require 'test/unit'

class AminoAcidsTest < Test::Unit::TestCase

  def test_parse_dna_empty
    assert_equal '', parse_dna('')
  end

  def test_parse_dna_clean
    assert_equal 'GATTACA', parse_dna('GATTACA')
  end

  def test_parse_dna_c12n # capitalization
    assert_equal 'GATTACA', parse_dna('GaTtacA')
  end

  def test_parse_dna_garbage
    assert_equal 'CATCAT', parse_dna('C  A Tkljh$@C480AT')
  end

  def test_parse_dna_with_u
    assert_equal 'CATACAT', parse_dna('CATAuUCAT')
  end

  def test_transcribe_already_transcribed
    assert_equal 'GAGA', transcribe('GAGA')
  end

  def test_transcribe_simple
    assert_equal 'GUAC', transcribe('GTAC')
  end

  def test_parse_no_codons
    assert_equal [], parse_codons('')
  end

  def test_parse_one_codon
    assert_equal ['GUA'], parse_codons('GUA')
  end

  def test_parse_two_codons
    assert_equal ['AUG', 'UUU'], parse_codons("AUGUUU")
  end

  def test_translate_empty
    assert_equal '', translate([])
  end

  def test_translate_no_start_stop
    assert_equal 'Met Trp Arg ', translate(['AUG', 'UGG', 'CGC'])
  end

  def test_translate_basic_start_and_stop
    assert_equal 'Met Val His ', translate(['AUG', 'GUA', 'CAU', 'UAA'])
  end

  def test_translate_leading_trailing # ignore leading and trailing codon
    assert_equal 'Met Tyr ', translate(['AUU', 'AUG', 'UAU', 'UAG', 'AUU'])
  end

  def test_translate_stop_start_scenario
    assert_equal 'Met Trp ', translate(['UAA', 'AUG', 'UGG', 'UAA', 'AUU'])
  end

  # Feel free to add more tests, but do not remove or edit these tests.

end
