#include "core/kernel.hpp"

#include <iostream>

class PrintingModule : public msboot::core::ModuleBase
{
public:
    PrintingModule() : ModuleBase("PrintingModule")
    {

    }

    ~PrintingModule()
    {
        on_stop();
    }

    void on_load() override
    {
        std::cerr << "on loaded" << std::endl;
    }

    void on_start() override
    {
        std::cerr << "starting" << std::endl;
    }

    void on_stop() override
    {
        std::cerr << "stopping" << std::endl;
    }
};

int main()
{
    msboot::core::Kernel kernel;
    {
        PrintingModule printer;
        kernel.register_module(printer);
        kernel.start();
    }

}
