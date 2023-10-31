#include <string>
#include <algorithm>
#include "Body.h"
#include "BodyController.h"
#include <iostream>

const std::string ERROR_MSG_INCORRECT_BODY = "Incorrect body is entered";
const std::string MSG_NOT_BODIES = "Quantity of bodies is 0";
const std::string MSG_MAX_MASS_BODY = "BODY WITH MAX MASS:";
const std::string MSG_MIN_WEIGHT_BODY = "BODY WITH MIN WEIGHT IN WATER:";
const int DENSITY_WATER = 1000;
const int G = 10;

void PrintInfoAbouBodies(const std::vector<BodyPtr>& bodies)
{
    for (auto& body : bodies)
    {
        std::cout << body->ToString() << std::endl;
    }
};

void FindHeavyBody(const std::vector<BodyPtr>& bodies)
{
    auto comp = [](const BodyPtr& a, const BodyPtr& b)
    {
        return a->GetMass() < b->GetMass();
    };

    if (bodies.size() == 0)
    {
        std::cout << MSG_NOT_BODIES << std::endl;
    }
    else
    {
        std::cout << std::endl << MSG_MAX_MASS_BODY << std::endl;
        auto maxMassBody = *std::max_element(bodies.begin(), bodies.end(), comp);
        std::cout << maxMassBody->ToString() << std::endl;
    }
};

void FindBodyWithMinWeightInWater(const std::vector<BodyPtr>& bodies)
{
    auto comp = [](const BodyPtr& a, const BodyPtr& b)
    {
        double weightA = a->GetMass() * G - a->GetVolume() * DENSITY_WATER * G;
        double weightB = b->GetMass() * G - b->GetVolume() * DENSITY_WATER * G;
        return weightA < weightB;
    };

    if (bodies.size() == 0)
    {
        std::cout << MSG_NOT_BODIES << std::endl;
    }
    else
    {
        std::cout << std::endl << MSG_MIN_WEIGHT_BODY << std::endl;
        BodyPtr minWieghtbody = *std::min_element(bodies.begin(), bodies.end(), comp);
        std::cout << minWieghtbody->ToString() << std::endl;
    }
};

int main()
{
    std::vector<BodyPtr> bodies;
    CBodyController bc(bodies, std::cin, std::cout);

    while (!std::cin.eof() && !std::cin.fail())
    {
        if (!bc.CreateBodies())
        {
            std::cout << ERROR_MSG_INCORRECT_BODY << std::endl;
        }
    }

    PrintInfoAbouBodies(bodies);
    FindHeavyBody(bodies);
    FindBodyWithMinWeightInWater(bodies);

    return 0;
}