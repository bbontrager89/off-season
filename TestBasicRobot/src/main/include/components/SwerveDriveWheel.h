#pragma once

#include <frc/controller/PIDController.h>
#include <rev/CANSparkMax.h>
#include <rev/CANSparkMaxLowLevel.h>
#include <math/Calculator.h>

class SwerveDriveWheel
{
public:
    SwerveDriveWheel(double P, double I, double D, rev::SparkMaxRelativeEncoder &directionEncoder, rev::CANSparkMax &directionMotor, rev::CANSparkMax &speedMotor);

    void setDirection(double setPoint);
    void setSpeed(double speed);

private:
    frc::PIDController *directionController;
    rev::CANSparkMax *directionMotor;
    rev::CANSparkMax *speedMotor;
    rev::SparkMaxRelativeEncoder *directionEncoder;
};