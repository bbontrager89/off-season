/**
 * Calculator
 */
#include "math/Calculator.h"
#include <cmath>
#include <Constants.h>
// Calculates the closest angle, for example, it rotates -90 degrees from angle 0 to get to angle 270 vs rotating 270 degrees from angle 0 to get to 270
double Calculator::closestAngle(double angleA, double angleB)
{
    // Nested function to calculate modulo considering negatives
    auto calculateModulo = [](double dividend, double divisor)
    {
        return dividend - divisor * std::floor(dividend / divisor);
    };

    // Get direction
    double angleDifference = calculateModulo(angleB, 360.0) - calculateModulo(angleA, 360.0);

    // Convert from -360 to 360 to -180 to 180
    if (std::abs(angleDifference) > 180.0)
    {
        angleDifference = -(std::signbit(angleDifference) ? 1.0 : -1.0) * 360.0 + angleDifference;
    }
    return angleDifference;
}

double calculateDeadzone(double value)
{
    if (std::abs(value) < OperatorConstants::kControllerDeadzoneThreshold)
    {
        return 0.0;
    }
    return value;
}
