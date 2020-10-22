#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <word_replacers/dictionary_replacer.h>


TEST_SUITE("dictionary replacer") {
    TEST_CASE("need replace for word to word replacer") {
        ReplacerWordToWord replacer({
                {"a", "ddd"},
                {"b", "aaa"},
                {"c", "ccc"},
                {"d", "ddd"},
                {"gag", "rarr"}
        });

        CHECK(replacer.need_replace("a"));
        CHECK(replacer.need_replace("b"));
        CHECK(replacer.need_replace("c"));
        CHECK(replacer.need_replace("d"));
        CHECK(replacer.need_replace("gag"));

        CHECK_FALSE(replacer.need_replace("nsdios"));
        CHECK_FALSE(replacer.need_replace("sdushod"));
        CHECK_FALSE(replacer.need_replace("fusnscdoijaods"));
    }

    TEST_CASE("replace word for word to word replacer") {
        ReplacerWordToWord replacer({
            {"a", "ddd"},
            {"b", "aaa"},
            {"c", "ccc"},
            {"d", "ddd"},
            {"gag", "rarr"}
        });

        CHECK_EQ(replacer.replace_word("a"), "ddd");
        CHECK_EQ(replacer.replace_word("b"), "aaa");
        CHECK_EQ(replacer.replace_word("c"), "ccc");
        CHECK_EQ(replacer.replace_word("d"), "ddd");
        CHECK_EQ(replacer.replace_word("gag"), "rarr");

        // мы хотим чтобы отсутвующее слово не заменялось
        CHECK_EQ(replacer.replace_word("foo"), "foo");
        CHECK_EQ(replacer.replace_word("tst"), "tst");
        CHECK_EQ(replacer.replace_word("rach"), "rach");
        CHECK_EQ(replacer.replace_word("glap"), "glap");
    }
}

