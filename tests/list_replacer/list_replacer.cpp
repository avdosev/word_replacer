#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <word_replacers/list_replacer.h>

TEST_SUITE("dictionary replacer") {
    TEST_CASE("testing the need replace") {
        ReplacerWordToChar replacer({
            "a",
            "bb",
            "ccc",
            "dddd",
            "eeeee",
            "ffffff",
            "ggggggg"
        }, '*');

        CHECK(replacer.need_replace("a"));
        CHECK(replacer.need_replace("bb"));
        CHECK(replacer.need_replace("ccc"));
        CHECK(replacer.need_replace("dddd"));
        CHECK(replacer.need_replace("eeeee"));
        CHECK(replacer.need_replace("ffffff"));
        CHECK(replacer.need_replace("ggggggg"));

        CHECK_FALSE(replacer.need_replace("aaaaaa"));
        CHECK_FALSE(replacer.need_replace("ggg"));
    }

    TEST_CASE("testing the replace word") {
        for (char ch : "*#390a") {
            ReplacerWordToChar replacer({
                "a",
                "bb",
                "ccc",
                "dddd",
                "eeeee",
                "ffffff",
                "ggggggg"
            }, ch);
#define REP_CHAR(ch, count) std::string(count, ch)
            CHECK_EQ(replacer.replace_word("a"), REP_CHAR(ch, 1));
            CHECK_EQ(replacer.replace_word("bb"), REP_CHAR(ch, 2));
            CHECK_EQ(replacer.replace_word("ccc"), REP_CHAR(ch, 3));
            CHECK_EQ(replacer.replace_word("dddd"), REP_CHAR(ch, 4));
            CHECK_EQ(replacer.replace_word("eeeee"), REP_CHAR(ch, 5));
            CHECK_EQ(replacer.replace_word("ffffff"), REP_CHAR(ch, 6));
            CHECK_EQ(replacer.replace_word("ggggggg"), REP_CHAR(ch, 7));

            CHECK_EQ(replacer.replace_word("foo"), REP_CHAR(ch, 3));
            CHECK_EQ(replacer.replace_word("tst"), REP_CHAR(ch, 3));
            CHECK_EQ(replacer.replace_word("rach"), REP_CHAR(ch, 4));
            CHECK_EQ(replacer.replace_word("glap"), REP_CHAR(ch, 4));
#undef REP_CHAR
        }
    }
}

//#include <word_replacers/list_replacer.h>
