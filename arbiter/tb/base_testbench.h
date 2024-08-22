#pragma once

#include "Vdut.h"
#include "verilated.h"
#include "gtest/gtest.h"


#define MAX_SIM_CYCLES  10000


class BaseTestbench : public ::testing::Test
{
protected:
    Vdut* top;
    
    void runSimulation(int num_cycles = 1)
    {
        // Run simuation for many clock cycles
        for (int i = 0; i < num_cycles; ++i)
        {
            // dump variables into VCD file and toggle clock
            for (int clk = 0; clk < 4; ++clk)
            {
                top->eval();
                top->clk = !top->clk;
            }

            ticks++;

            if (Verilated::gotFinish())
            {
                exit(0);
            }
        }
    }

    void SetUp() override
    {
        // Init top verilog instance
        top = new Vdut;
        initializeInputs();
    }

    void TearDown() override
    {
        top->final();

        delete top;
    }

    virtual void initializeInputs() = 0;

private:
    int ticks = 0;
};
