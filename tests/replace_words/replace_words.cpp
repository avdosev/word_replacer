#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <word_replacers/list_replacer.h>
#include <word_replacers/dictionary_replacer.h>
#include <replace_words.h>


TEST_SUITE("replace words") {
    TEST_CASE("replace words with word to char replacer") {
        ReplacerWordToChar replacer({
            "char", "puk", "data", "work", "kek", "recognition", "1111", "$$$$$"
            }, '$');
        using namespace std::string_view_literals;
        auto line     = "chars char puk guk  gpuk  \n  datadata}data work kkkekk kek recognition"sv;
        auto line_out = "chars $$$$ $$$ guk  gpuk  \n  datadata}$$$$ $$$$ kkkekk $$$ $$$$$$$$$$$"sv;

        CHECK_EQ(replace_words(line, replacer), line_out);

        line     = "1111 909099 102029 skpa jaiosd oasij fjidos dksdio dsi"sv;
        line_out = "$$$$ 909099 102029 skpa jaiosd oasij fjidos dksdio dsi"sv;

        CHECK_EQ(replace_words(line, replacer), line_out);

        line     = "$$$$$"sv;
        line_out = line;
        CHECK_EQ(replace_words(line, replacer), line_out);
    }

    TEST_CASE("replace words with word to word replacer") {
        ReplacerWordToWord replacer({
            {"test", "gest"},
            {"g", "ggg"},
            {"work", "w"},
            {"w", "work"},
            {"work1", "w1"},
            {"1111", "5555"}
        });
        using namespace std::string_view_literals;

        auto line     = "test ggg g group | \rwork www w wokr2 work1 11111 1 111 1111"sv;
        auto line_out = "gest ggg ggg group | \rw www work wokr2 w1 11111 1 111 5555"sv;

        CHECK_EQ(replace_words(line, replacer), line_out);

        line     = "1111"sv;
        line_out = "5555"sv;

        CHECK_EQ(replace_words(line, replacer), line_out);

        line     = ""sv;
        line_out = line;

        CHECK_EQ(replace_words(line, replacer), line_out);
    }

    TEST_CASE("replace words with moc") {
        struct MockWordReplacer : WordReplacer {
            std::vector<std::string> removed_words, checked_words;

            bool need_replace(std::string_view word) override {
                checked_words.emplace_back(word);
                return false;
            }

            std::string replace_word(std::string_view word) override {
                removed_words.emplace_back(word);
                return "!!!!!!";
            }

            void clear() {
                removed_words.clear();
                checked_words.clear();
            }
        };

        MockWordReplacer replacer;

        using namespace std::string_view_literals;

        auto line = "chars char puk guk  gpuk  \n  datadata}data work kkkekk kek recognition"sv;
        CHECK(replace_words(line, replacer).find('!') == std::string::npos);
        CHECK_EQ(replacer.checked_words.size(), 11);
        CHECK_EQ(replacer.removed_words.size(), 0);
        replacer.clear();

        line = "1111"sv;
        CHECK(replace_words(line, replacer).find('!') == std::string::npos);
        CHECK_EQ(replacer.checked_words.size(), 1);
        CHECK_EQ(replacer.removed_words.size(), 0);
        replacer.clear();

        line = ""sv;
        CHECK_EQ(replace_words(line, replacer).length(), 0);
        CHECK_EQ(replacer.checked_words.size(), 0);
        CHECK_EQ(replacer.removed_words.size(), 0);
    }
}

//#include <word_replacers/list_replacer.h>
