#include "CoulombSimulation.h"
#include "SlopeFieldRunner.h"
#include "PhasePlot.h"
#include<random>

int main(int argc, char** argv) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);

    PhasePlot simulation(argc, argv);
    simulation.start();

    return 0;
}
