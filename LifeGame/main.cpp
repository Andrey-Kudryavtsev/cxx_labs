#include <gtest/gtest.h>
#include <iostream>
#include "LifeGame.h"

using namespace std;

TEST(StepTest, test1)
{
    InputHandler inputHandler;
    EXPECT_EQ(inputHandler.getCommand("step"), Command::STEP);
}

TEST(StepTest, test2)
{
    InputHandler inputHandler;
    EXPECT_EQ(inputHandler.getCommand("step 255"), Command::STEP);
}

TEST(StepTest, test3)
{
    InputHandler inputHandler;
    EXPECT_EQ(inputHandler.getCommand("step GDV"), Command::WRONG_TURN_AMOUNT);
}

TEST(SetTest, test1)
{
    InputHandler inputHandler;
    EXPECT_EQ(inputHandler.getCommand("set G7"), Command::SET);
}

TEST(SetTest, test2)
{
    InputHandler inputHandler;
    EXPECT_EQ(inputHandler.getCommand("set 7G"), Command::WRONG_COORDS);
}

TEST(ClearTest, test1)
{
    InputHandler inputHandler;
    EXPECT_EQ(inputHandler.getCommand("clear H3"), Command::CLEAR);
}

TEST(ClearTest, test2)
{
    InputHandler inputHandler;
    EXPECT_EQ(inputHandler.getCommand("clear R9"), Command::WRONG_COORDS);
}

TEST(ResetTest, test1)
{
    InputHandler inputHandler;
    EXPECT_EQ(inputHandler.getCommand("reset"), Command::RESET);
}

TEST(BackTest, test1)
{
    InputHandler inputHandler;
    EXPECT_EQ(inputHandler.getCommand("back"), Command::BACK);
}

TEST(SaveTest, test1)
{
    InputHandler inputHandler;
    EXPECT_EQ(inputHandler.getCommand("save filename"), Command::SAVE);
}

TEST(SaveTest, test2)
{
    InputHandler inputHandler;
    EXPECT_EQ(inputHandler.getCommand("save"), Command::WRONG_COMMAND);
}

TEST(LoadTest, test1)
{
    InputHandler inputHandler;
    EXPECT_EQ(inputHandler.getCommand("load filename"), Command::LOAD);
}

TEST(LoadTest, test2)
{
    InputHandler inputHandler;
    EXPECT_EQ(inputHandler.getCommand("load"), Command::WRONG_COMMAND);
}

int main() {
    //LifeGame game;
    //game.play();
    testing::InitGoogleTest();;
    return RUN_ALL_TESTS();
}