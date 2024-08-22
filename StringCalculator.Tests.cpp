#include <gtest/gtest.h>
#include "Soundex.h"
TEST(SoundexTestsuite, BasicSoundexCode) {
    char soundex[5];
   generateSoundex("Example", soundex);
//EXPECT_STREQ(soundex, "E251");

}

TEST(SoundexTestsuite, IgnoresNonAlphabeticCharacters) {
    char soundex[5];
    generateSoundex("A1B2C3", soundex);
 //   ASSERT_EQ(std::string(soundex), "A123");
}
