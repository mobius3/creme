#ifndef CREME_EXTRAS_FONT_UNICODE_RANGE_H
#define CREME_EXTRAS_FONT_UNICODE_RANGE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Provides information about a specific unicode block, as specified in
 * ftp://ftp.unicode.org/Public/UNIDATA/Blocks.txt
 */
struct cmx_font_unicode_block {
  uint32_t first;
  uint32_t last;
  uint32_t count;
};

/* All the blocks, minus a few in the bottom */
extern struct cmx_font_unicode_block cmx_font_unicode_block_control;
extern struct cmx_font_unicode_block cmx_font_unicode_block_basic_latin;
extern struct cmx_font_unicode_block cmx_font_unicode_block_latin_1_supplement;
extern struct cmx_font_unicode_block cmx_font_unicode_block_latin_extended_a;
extern struct cmx_font_unicode_block cmx_font_unicode_block_latin_extended_b;
extern struct cmx_font_unicode_block cmx_font_unicode_block_ipa_extensions;
extern struct cmx_font_unicode_block cmx_font_unicode_block_spacing_modifier_letters;
extern struct cmx_font_unicode_block cmx_font_unicode_block_combining_diacritical_marks;
extern struct cmx_font_unicode_block cmx_font_unicode_block_greek_and_coptic;
extern struct cmx_font_unicode_block cmx_font_unicode_block_cyrillic;
extern struct cmx_font_unicode_block cmx_font_unicode_block_cyrillic_supplement;
extern struct cmx_font_unicode_block cmx_font_unicode_block_armenian;
extern struct cmx_font_unicode_block cmx_font_unicode_block_hebrew;
extern struct cmx_font_unicode_block cmx_font_unicode_block_arabic;
extern struct cmx_font_unicode_block cmx_font_unicode_block_syriac;
extern struct cmx_font_unicode_block cmx_font_unicode_block_arabic_supplement;
extern struct cmx_font_unicode_block cmx_font_unicode_block_thaana;
extern struct cmx_font_unicode_block cmx_font_unicode_block_nko;
extern struct cmx_font_unicode_block cmx_font_unicode_block_samaritan;
extern struct cmx_font_unicode_block cmx_font_unicode_block_mandaic;
extern struct cmx_font_unicode_block cmx_font_unicode_block_syriac_supplement;
extern struct cmx_font_unicode_block cmx_font_unicode_block_arabic_extended_a;
extern struct cmx_font_unicode_block cmx_font_unicode_block_devanagari;
extern struct cmx_font_unicode_block cmx_font_unicode_block_bengali;
extern struct cmx_font_unicode_block cmx_font_unicode_block_gurmukhi;
extern struct cmx_font_unicode_block cmx_font_unicode_block_gujarati;
extern struct cmx_font_unicode_block cmx_font_unicode_block_oriya;
extern struct cmx_font_unicode_block cmx_font_unicode_block_tamil;
extern struct cmx_font_unicode_block cmx_font_unicode_block_telugu;
extern struct cmx_font_unicode_block cmx_font_unicode_block_kannada;
extern struct cmx_font_unicode_block cmx_font_unicode_block_malayalam;
extern struct cmx_font_unicode_block cmx_font_unicode_block_sinhala;
extern struct cmx_font_unicode_block cmx_font_unicode_block_thai;
extern struct cmx_font_unicode_block cmx_font_unicode_block_lao;
extern struct cmx_font_unicode_block cmx_font_unicode_block_tibetan;
extern struct cmx_font_unicode_block cmx_font_unicode_block_myanmar;
extern struct cmx_font_unicode_block cmx_font_unicode_block_georgian;
extern struct cmx_font_unicode_block cmx_font_unicode_block_hangul_jamo;
extern struct cmx_font_unicode_block cmx_font_unicode_block_ethiopic;
extern struct cmx_font_unicode_block cmx_font_unicode_block_ethiopic_supplement;
extern struct cmx_font_unicode_block cmx_font_unicode_block_cherokee;
extern struct cmx_font_unicode_block cmx_font_unicode_block_unified_canadian_aboriginal_syllabics;
extern struct cmx_font_unicode_block cmx_font_unicode_block_ogham;
extern struct cmx_font_unicode_block cmx_font_unicode_block_runic;
extern struct cmx_font_unicode_block cmx_font_unicode_block_tagalog;
extern struct cmx_font_unicode_block cmx_font_unicode_block_hanunoo;
extern struct cmx_font_unicode_block cmx_font_unicode_block_buhid;
extern struct cmx_font_unicode_block cmx_font_unicode_block_tagbanwa;
extern struct cmx_font_unicode_block cmx_font_unicode_block_khmer;
extern struct cmx_font_unicode_block cmx_font_unicode_block_mongolian;
extern struct cmx_font_unicode_block cmx_font_unicode_block_unified_canadian_aboriginal_syllabics_extended;
extern struct cmx_font_unicode_block cmx_font_unicode_block_limbu;
extern struct cmx_font_unicode_block cmx_font_unicode_block_tai_le;
extern struct cmx_font_unicode_block cmx_font_unicode_block_new_tai_lue;
extern struct cmx_font_unicode_block cmx_font_unicode_block_khmer_symbols;
extern struct cmx_font_unicode_block cmx_font_unicode_block_buginese;
extern struct cmx_font_unicode_block cmx_font_unicode_block_tai_tham;
extern struct cmx_font_unicode_block cmx_font_unicode_block_combining_diacritical_marks_extended;
extern struct cmx_font_unicode_block cmx_font_unicode_block_balinese;
extern struct cmx_font_unicode_block cmx_font_unicode_block_sundanese;
extern struct cmx_font_unicode_block cmx_font_unicode_block_batak;
extern struct cmx_font_unicode_block cmx_font_unicode_block_lepcha;
extern struct cmx_font_unicode_block cmx_font_unicode_block_ol_chiki;
extern struct cmx_font_unicode_block cmx_font_unicode_block_cyrillic_extended_c;
extern struct cmx_font_unicode_block cmx_font_unicode_block_georgian_extended;
extern struct cmx_font_unicode_block cmx_font_unicode_block_sundanese_supplement;
extern struct cmx_font_unicode_block cmx_font_unicode_block_vedic_extensions;
extern struct cmx_font_unicode_block cmx_font_unicode_block_phonetic_extensions;
extern struct cmx_font_unicode_block cmx_font_unicode_block_phonetic_extensions_supplement;
extern struct cmx_font_unicode_block cmx_font_unicode_block_combining_diacritical_marks_supplement;
extern struct cmx_font_unicode_block cmx_font_unicode_block_latin_extended_additional;
extern struct cmx_font_unicode_block cmx_font_unicode_block_greek_extended;
extern struct cmx_font_unicode_block cmx_font_unicode_block_general_punctuation;
extern struct cmx_font_unicode_block cmx_font_unicode_block_superscripts_and_subscripts;
extern struct cmx_font_unicode_block cmx_font_unicode_block_currency_symbols;
extern struct cmx_font_unicode_block cmx_font_unicode_block_combining_diacritical_marks_for_symbols;
extern struct cmx_font_unicode_block cmx_font_unicode_block_letterlike_symbols;
extern struct cmx_font_unicode_block cmx_font_unicode_block_number_forms;
extern struct cmx_font_unicode_block cmx_font_unicode_block_arrows;
extern struct cmx_font_unicode_block cmx_font_unicode_block_mathematical_operators;
extern struct cmx_font_unicode_block cmx_font_unicode_block_miscellaneous_technical;
extern struct cmx_font_unicode_block cmx_font_unicode_block_control_pictures;
extern struct cmx_font_unicode_block cmx_font_unicode_block_optical_character_recognition;
extern struct cmx_font_unicode_block cmx_font_unicode_block_enclosed_alphanumerics;
extern struct cmx_font_unicode_block cmx_font_unicode_block_box_drawing;
extern struct cmx_font_unicode_block cmx_font_unicode_block_block_elements;
extern struct cmx_font_unicode_block cmx_font_unicode_block_geometric_shapes;
extern struct cmx_font_unicode_block cmx_font_unicode_block_miscellaneous_symbols;
extern struct cmx_font_unicode_block cmx_font_unicode_block_dingbats;
extern struct cmx_font_unicode_block cmx_font_unicode_block_miscellaneous_mathematical_symbols_a;
extern struct cmx_font_unicode_block cmx_font_unicode_block_supplemental_arrows_a;
extern struct cmx_font_unicode_block cmx_font_unicode_block_braille_patterns;
extern struct cmx_font_unicode_block cmx_font_unicode_block_supplemental_arrows_b;
extern struct cmx_font_unicode_block cmx_font_unicode_block_miscellaneous_mathematical_symbols_b;
extern struct cmx_font_unicode_block cmx_font_unicode_block_supplemental_mathematical_operators;
extern struct cmx_font_unicode_block cmx_font_unicode_block_miscellaneous_symbols_and_arrows;
extern struct cmx_font_unicode_block cmx_font_unicode_block_glagolitic;
extern struct cmx_font_unicode_block cmx_font_unicode_block_latin_extended_c;
extern struct cmx_font_unicode_block cmx_font_unicode_block_coptic;
extern struct cmx_font_unicode_block cmx_font_unicode_block_georgian_supplement;
extern struct cmx_font_unicode_block cmx_font_unicode_block_tifinagh;
extern struct cmx_font_unicode_block cmx_font_unicode_block_ethiopic_extended;
extern struct cmx_font_unicode_block cmx_font_unicode_block_cyrillic_extended_a;
extern struct cmx_font_unicode_block cmx_font_unicode_block_supplemental_punctuation;
extern struct cmx_font_unicode_block cmx_font_unicode_block_cjk_radicals_supplement;
extern struct cmx_font_unicode_block cmx_font_unicode_block_kangxi_radicals;
extern struct cmx_font_unicode_block cmx_font_unicode_block_ideographic_description_characters;
extern struct cmx_font_unicode_block cmx_font_unicode_block_cjk_symbols_and_punctuation;
extern struct cmx_font_unicode_block cmx_font_unicode_block_hiragana;
extern struct cmx_font_unicode_block cmx_font_unicode_block_katakana;
extern struct cmx_font_unicode_block cmx_font_unicode_block_bopomofo;
extern struct cmx_font_unicode_block cmx_font_unicode_block_hangul_compatibility_jamo;
extern struct cmx_font_unicode_block cmx_font_unicode_block_kanbun;
extern struct cmx_font_unicode_block cmx_font_unicode_block_bopomofo_extended;
extern struct cmx_font_unicode_block cmx_font_unicode_block_cjk_strokes;
extern struct cmx_font_unicode_block cmx_font_unicode_block_katakana_phonetic_extensions;
extern struct cmx_font_unicode_block cmx_font_unicode_block_enclosed_cjk_letters_and_months;
extern struct cmx_font_unicode_block cmx_font_unicode_block_cjk_compatibility;
extern struct cmx_font_unicode_block cmx_font_unicode_block_cjk_unified_ideographs_extension_a;
extern struct cmx_font_unicode_block cmx_font_unicode_block_yijing_hexagram_symbols;
extern struct cmx_font_unicode_block cmx_font_unicode_block_cjk_unified_ideographs;
extern struct cmx_font_unicode_block cmx_font_unicode_block_yi_syllables;
extern struct cmx_font_unicode_block cmx_font_unicode_block_yi_radicals;
extern struct cmx_font_unicode_block cmx_font_unicode_block_lisu;
extern struct cmx_font_unicode_block cmx_font_unicode_block_vai;
extern struct cmx_font_unicode_block cmx_font_unicode_block_cyrillic_extended_b;
extern struct cmx_font_unicode_block cmx_font_unicode_block_bamum;
extern struct cmx_font_unicode_block cmx_font_unicode_block_modifier_tone_letters;
extern struct cmx_font_unicode_block cmx_font_unicode_block_latin_extended_d;
extern struct cmx_font_unicode_block cmx_font_unicode_block_syloti_nagri;
extern struct cmx_font_unicode_block cmx_font_unicode_block_common_indic_number_forms;
extern struct cmx_font_unicode_block cmx_font_unicode_block_phags_pa;
extern struct cmx_font_unicode_block cmx_font_unicode_block_saurashtra;
extern struct cmx_font_unicode_block cmx_font_unicode_block_devanagari_extended;
extern struct cmx_font_unicode_block cmx_font_unicode_block_kayah_li;
extern struct cmx_font_unicode_block cmx_font_unicode_block_rejang;
extern struct cmx_font_unicode_block cmx_font_unicode_block_hangul_jamo_extended_a;
extern struct cmx_font_unicode_block cmx_font_unicode_block_javanese;
extern struct cmx_font_unicode_block cmx_font_unicode_block_myanmar_extended_b;
extern struct cmx_font_unicode_block cmx_font_unicode_block_cham;
extern struct cmx_font_unicode_block cmx_font_unicode_block_myanmar_extended_a;
extern struct cmx_font_unicode_block cmx_font_unicode_block_tai_viet;
extern struct cmx_font_unicode_block cmx_font_unicode_block_meetei_mayek_extensions;
extern struct cmx_font_unicode_block cmx_font_unicode_block_ethiopic_extended_a;
extern struct cmx_font_unicode_block cmx_font_unicode_block_latin_extended_e;
extern struct cmx_font_unicode_block cmx_font_unicode_block_cherokee_supplement;
extern struct cmx_font_unicode_block cmx_font_unicode_block_meetei_mayek;
extern struct cmx_font_unicode_block cmx_font_unicode_block_hangul_syllables;
extern struct cmx_font_unicode_block cmx_font_unicode_block_hangul_jamo_extended_b;
extern struct cmx_font_unicode_block cmx_font_unicode_block_high_surrogates;
extern struct cmx_font_unicode_block cmx_font_unicode_block_high_private_use_surrogates;
extern struct cmx_font_unicode_block cmx_font_unicode_block_low_surrogates;
extern struct cmx_font_unicode_block cmx_font_unicode_block_private_use_area;
extern struct cmx_font_unicode_block cmx_font_unicode_block_cjk_compatibility_ideographs;
extern struct cmx_font_unicode_block cmx_font_unicode_block_alphabetic_presentation_forms;
extern struct cmx_font_unicode_block cmx_font_unicode_block_arabic_presentation_forms_a;
extern struct cmx_font_unicode_block cmx_font_unicode_block_variation_selectors;
extern struct cmx_font_unicode_block cmx_font_unicode_block_vertical_forms;
extern struct cmx_font_unicode_block cmx_font_unicode_block_combining_half_marks;
extern struct cmx_font_unicode_block cmx_font_unicode_block_cjk_compatibility_forms;
extern struct cmx_font_unicode_block cmx_font_unicode_block_small_form_variants;
extern struct cmx_font_unicode_block cmx_font_unicode_block_arabic_presentation_forms_b;
extern struct cmx_font_unicode_block cmx_font_unicode_block_halfwidth_and_fullwidth_forms;
extern struct cmx_font_unicode_block cmx_font_unicode_block_specials;
extern struct cmx_font_unicode_block cmx_font_unicode_block_linear_b_syllabary;
extern struct cmx_font_unicode_block cmx_font_unicode_block_linear_b_ideograms;
extern struct cmx_font_unicode_block cmx_font_unicode_block_aegean_numbers;
extern struct cmx_font_unicode_block cmx_font_unicode_block_ancient_greek_numbers;
extern struct cmx_font_unicode_block cmx_font_unicode_block_ancient_symbols;
extern struct cmx_font_unicode_block cmx_font_unicode_block_phaistos_disc;
extern struct cmx_font_unicode_block cmx_font_unicode_block_lycian;
extern struct cmx_font_unicode_block cmx_font_unicode_block_carian;
extern struct cmx_font_unicode_block cmx_font_unicode_block_coptic_epact_numbers;
extern struct cmx_font_unicode_block cmx_font_unicode_block_old_italic;
extern struct cmx_font_unicode_block cmx_font_unicode_block_gothic;
extern struct cmx_font_unicode_block cmx_font_unicode_block_old_permic;
extern struct cmx_font_unicode_block cmx_font_unicode_block_ugaritic;
extern struct cmx_font_unicode_block cmx_font_unicode_block_old_persian;
extern struct cmx_font_unicode_block cmx_font_unicode_block_deseret;
extern struct cmx_font_unicode_block cmx_font_unicode_block_shavian;
extern struct cmx_font_unicode_block cmx_font_unicode_block_osmanya;
extern struct cmx_font_unicode_block cmx_font_unicode_block_osage;
extern struct cmx_font_unicode_block cmx_font_unicode_block_elbasan;
extern struct cmx_font_unicode_block cmx_font_unicode_block_caucasian_albanian;
extern struct cmx_font_unicode_block cmx_font_unicode_block_linear_a;
extern struct cmx_font_unicode_block cmx_font_unicode_block_cypriot_syllabary;
extern struct cmx_font_unicode_block cmx_font_unicode_block_imperial_aramaic;
extern struct cmx_font_unicode_block cmx_font_unicode_block_palmyrene;
extern struct cmx_font_unicode_block cmx_font_unicode_block_nabataean;
extern struct cmx_font_unicode_block cmx_font_unicode_block_hatran;
extern struct cmx_font_unicode_block cmx_font_unicode_block_phoenician;
extern struct cmx_font_unicode_block cmx_font_unicode_block_lydian;
extern struct cmx_font_unicode_block cmx_font_unicode_block_meroitic_hieroglyphs;
extern struct cmx_font_unicode_block cmx_font_unicode_block_meroitic_cursive;
extern struct cmx_font_unicode_block cmx_font_unicode_block_kharoshthi;
extern struct cmx_font_unicode_block cmx_font_unicode_block_old_south_arabian;
extern struct cmx_font_unicode_block cmx_font_unicode_block_old_north_arabian;
extern struct cmx_font_unicode_block cmx_font_unicode_block_manichaean;
extern struct cmx_font_unicode_block cmx_font_unicode_block_avestan;
extern struct cmx_font_unicode_block cmx_font_unicode_block_inscriptional_parthian;
extern struct cmx_font_unicode_block cmx_font_unicode_block_inscriptional_pahlavi;
extern struct cmx_font_unicode_block cmx_font_unicode_block_psalter_pahlavi;
extern struct cmx_font_unicode_block cmx_font_unicode_block_old_turkic;
extern struct cmx_font_unicode_block cmx_font_unicode_block_old_hungarian;
extern struct cmx_font_unicode_block cmx_font_unicode_block_hanifi_rohingya;
extern struct cmx_font_unicode_block cmx_font_unicode_block_rumi_numeral_symbols;
extern struct cmx_font_unicode_block cmx_font_unicode_block_old_sogdian;
extern struct cmx_font_unicode_block cmx_font_unicode_block_sogdian;
extern struct cmx_font_unicode_block cmx_font_unicode_block_elymaic;
extern struct cmx_font_unicode_block cmx_font_unicode_block_brahmi;
extern struct cmx_font_unicode_block cmx_font_unicode_block_kaithi;
extern struct cmx_font_unicode_block cmx_font_unicode_block_sora_sompeng;
extern struct cmx_font_unicode_block cmx_font_unicode_block_chakma;
extern struct cmx_font_unicode_block cmx_font_unicode_block_mahajani;
extern struct cmx_font_unicode_block cmx_font_unicode_block_sharada;
extern struct cmx_font_unicode_block cmx_font_unicode_block_sinhala_archaic_numbers;
extern struct cmx_font_unicode_block cmx_font_unicode_block_khojki;
extern struct cmx_font_unicode_block cmx_font_unicode_block_multani;
extern struct cmx_font_unicode_block cmx_font_unicode_block_khudawadi;
extern struct cmx_font_unicode_block cmx_font_unicode_block_grantha;
extern struct cmx_font_unicode_block cmx_font_unicode_block_newa;
extern struct cmx_font_unicode_block cmx_font_unicode_block_tirhuta;
extern struct cmx_font_unicode_block cmx_font_unicode_block_siddham;
extern struct cmx_font_unicode_block cmx_font_unicode_block_modi;
extern struct cmx_font_unicode_block cmx_font_unicode_block_mongolian_supplement;
extern struct cmx_font_unicode_block cmx_font_unicode_block_takri;
extern struct cmx_font_unicode_block cmx_font_unicode_block_ahom;
extern struct cmx_font_unicode_block cmx_font_unicode_block_dogra;
extern struct cmx_font_unicode_block cmx_font_unicode_block_warang_citi;
extern struct cmx_font_unicode_block cmx_font_unicode_block_nandinagari;
extern struct cmx_font_unicode_block cmx_font_unicode_block_zanabazar_square;
extern struct cmx_font_unicode_block cmx_font_unicode_block_soyombo;
extern struct cmx_font_unicode_block cmx_font_unicode_block_pau_cin_hau;
extern struct cmx_font_unicode_block cmx_font_unicode_block_bhaiksuki;
extern struct cmx_font_unicode_block cmx_font_unicode_block_marchen;
extern struct cmx_font_unicode_block cmx_font_unicode_block_masaram_gondi;
extern struct cmx_font_unicode_block cmx_font_unicode_block_gunjala_gondi;
extern struct cmx_font_unicode_block cmx_font_unicode_block_makasar;
extern struct cmx_font_unicode_block cmx_font_unicode_block_tamil_supplement;
extern struct cmx_font_unicode_block cmx_font_unicode_block_cuneiform;
extern struct cmx_font_unicode_block cmx_font_unicode_block_cuneiform_numbers_and_punctuation;
extern struct cmx_font_unicode_block cmx_font_unicode_block_early_dynastic_cuneiform;
extern struct cmx_font_unicode_block cmx_font_unicode_block_egyptian_hieroglyphs;
extern struct cmx_font_unicode_block cmx_font_unicode_block_egyptian_hieroglyph_format_controls;
extern struct cmx_font_unicode_block cmx_font_unicode_block_anatolian_hieroglyphs;
extern struct cmx_font_unicode_block cmx_font_unicode_block_bamum_supplement;
extern struct cmx_font_unicode_block cmx_font_unicode_block_mro;
extern struct cmx_font_unicode_block cmx_font_unicode_block_bassa_vah;
extern struct cmx_font_unicode_block cmx_font_unicode_block_pahawh_hmong;
extern struct cmx_font_unicode_block cmx_font_unicode_block_medefaidrin;
extern struct cmx_font_unicode_block cmx_font_unicode_block_miao;
extern struct cmx_font_unicode_block cmx_font_unicode_block_ideographic_symbols_and_punctuation;
extern struct cmx_font_unicode_block cmx_font_unicode_block_tangut;
extern struct cmx_font_unicode_block cmx_font_unicode_block_tangut_components;
extern struct cmx_font_unicode_block cmx_font_unicode_block_kana_supplement;
extern struct cmx_font_unicode_block cmx_font_unicode_block_kana_extended_a;
extern struct cmx_font_unicode_block cmx_font_unicode_block_small_kana_extension;
extern struct cmx_font_unicode_block cmx_font_unicode_block_nushu;
extern struct cmx_font_unicode_block cmx_font_unicode_block_duployan;
extern struct cmx_font_unicode_block cmx_font_unicode_block_shorthand_format_controls;
extern struct cmx_font_unicode_block cmx_font_unicode_block_byzantine_musical_symbols;
extern struct cmx_font_unicode_block cmx_font_unicode_block_musical_symbols;
extern struct cmx_font_unicode_block cmx_font_unicode_block_ancient_greek_musical_notation;
extern struct cmx_font_unicode_block cmx_font_unicode_block_mayan_numerals;
extern struct cmx_font_unicode_block cmx_font_unicode_block_tai_xuan_jing_symbols;
extern struct cmx_font_unicode_block cmx_font_unicode_block_counting_rod_numerals;
extern struct cmx_font_unicode_block cmx_font_unicode_block_mathematical_alphanumeric_symbols;
extern struct cmx_font_unicode_block cmx_font_unicode_block_sutton_signwriting;
extern struct cmx_font_unicode_block cmx_font_unicode_block_glagolitic_supplement;
extern struct cmx_font_unicode_block cmx_font_unicode_block_nyiakeng_puachue_hmong;
extern struct cmx_font_unicode_block cmx_font_unicode_block_wancho;
extern struct cmx_font_unicode_block cmx_font_unicode_block_mende_kikakui;
extern struct cmx_font_unicode_block cmx_font_unicode_block_adlam;
extern struct cmx_font_unicode_block cmx_font_unicode_block_indic_siyaq_numbers;
extern struct cmx_font_unicode_block cmx_font_unicode_block_ottoman_siyaq_numbers;
extern struct cmx_font_unicode_block cmx_font_unicode_block_arabic_mathematical_alphabetic_symbols;
extern struct cmx_font_unicode_block cmx_font_unicode_block_mahjong_tiles;
extern struct cmx_font_unicode_block cmx_font_unicode_block_domino_tiles;
extern struct cmx_font_unicode_block cmx_font_unicode_block_playing_cards;
extern struct cmx_font_unicode_block cmx_font_unicode_block_enclosed_alphanumeric_supplement;
extern struct cmx_font_unicode_block cmx_font_unicode_block_enclosed_ideographic_supplement;
extern struct cmx_font_unicode_block cmx_font_unicode_block_miscellaneous_symbols_and_pictographs;
extern struct cmx_font_unicode_block cmx_font_unicode_block_emoticons;
extern struct cmx_font_unicode_block cmx_font_unicode_block_ornamental_dingbats;
extern struct cmx_font_unicode_block cmx_font_unicode_block_transport_and_map_symbols;
extern struct cmx_font_unicode_block cmx_font_unicode_block_alchemical_symbols;
extern struct cmx_font_unicode_block cmx_font_unicode_block_geometric_shapes_extended;
extern struct cmx_font_unicode_block cmx_font_unicode_block_supplemental_arrows_c;
extern struct cmx_font_unicode_block cmx_font_unicode_block_supplemental_symbols_and_pictographs;
extern struct cmx_font_unicode_block cmx_font_unicode_block_chess_symbols;
extern struct cmx_font_unicode_block cmx_font_unicode_block_symbols_and_pictographs_extended_a;
extern struct cmx_font_unicode_block cmx_font_unicode_block_cjk_unified_ideographs_extension_b;
extern struct cmx_font_unicode_block cmx_font_unicode_block_cjk_unified_ideographs_extension_c;
extern struct cmx_font_unicode_block cmx_font_unicode_block_cjk_unified_ideographs_extension_d;
extern struct cmx_font_unicode_block cmx_font_unicode_block_cjk_unified_ideographs_extension_e;
extern struct cmx_font_unicode_block cmx_font_unicode_block_cjk_unified_ideographs_extension_f;
extern struct cmx_font_unicode_block cmx_font_unicode_block_cjk_compatibility_ideographs_supplement;
extern struct cmx_font_unicode_block cmx_font_unicode_block_tags;
extern struct cmx_font_unicode_block cmx_font_unicode_block_variation_selectors_supplement;

#ifdef __cplusplus
}
#endif

#endif /* CREME_EXTRAS_FONT_UNICODE_RANGE_H */
