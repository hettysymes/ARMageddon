/**
 * Tests the FSM under all states
 */

#include <unordered_map>

#include "base_testbench.h"

#define REQUEST_B 0b001
#define REQUEST_C 0b010
#define REQUEST_D 0b100

#define STATE_A 0b000
#define STATE_B 0b001
#define STATE_C 0b010
#define STATE_D 0b100

class ArbiterTestbench : public BaseTestbench
{
    void initializeInputs() override
    {
        top->clk = 1;
        top->resetn = 1;

        // State A 
        top->r = 0b000;

        // output logic [2:0] g;
    }
};

TEST_F(ArbiterTestbench, NoRequest)
{
    // No request
    top->r = 0b000;
    runSimulation(1);
    EXPECT_EQ(top->g, 0b000);
}

TEST_F(ArbiterTestbench, StateMoving)
{
    // LSB has lower priority (B, C, D (lower priority))
    // input: output
    std::unordered_map<int, int> tests = {
        {0b000, STATE_A},
        {REQUEST_B, STATE_B},
        {REQUEST_C, STATE_C},
        {REQUEST_B | REQUEST_C, STATE_B},
        {REQUEST_D, STATE_D},
        {REQUEST_B | REQUEST_D, STATE_B},
        {REQUEST_C | REQUEST_D, STATE_C},
        {REQUEST_B | REQUEST_C | REQUEST_D, STATE_B}
    };

    for (auto x: tests)
    {
        top->r = x.first;
        runSimulation();
        EXPECT_EQ(top->g, x.second);

        // Stay in state
        runSimulation();
        EXPECT_EQ(top->g, x.second);

        // Go back to state A
        top->r = 0b000;
        runSimulation();
        EXPECT_EQ(top->g, 0b000);
    }
}

TEST_F(ArbiterTestbench, StayInState)
{
    top->r = REQUEST_B;
    runSimulation();
    EXPECT_EQ(top->g, STATE_B);

    // Stay in state
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; i < 2; i++)
        {
            top->r = REQUEST_B | (REQUEST_C & i) | (REQUEST_D & j);
            runSimulation();
            EXPECT_EQ(top->g, STATE_B);
        }
    }

    // Move states 
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; i < 2; i++)
        {
            top->r = 0b000;
            runSimulation();
            EXPECT_EQ(top->g, STATE_A);

            top->r = REQUEST_B;
            runSimulation();
            EXPECT_EQ(top->g, STATE_B);
    
            top->r = (REQUEST_C & i) | (REQUEST_D & j);
            runSimulation();
            EXPECT_EQ(top->g, STATE_A);
        }
    }
}

TEST_F(ArbiterTestbench, ResetState)
{
    // Active LOW
    top->resetn = 0;
    top->r = REQUEST_C;
    runSimulation();
    EXPECT_EQ(top->g, STATE_A);
}

int main(int argc, char **argv)
{
    Verilated::commandArgs(argc, argv);
    testing::InitGoogleTest(&argc, argv);
    Verilated::mkdir("logs");
    auto res = RUN_ALL_TESTS();

    return res;
}