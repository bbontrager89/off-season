#ifndef SWERVEDRIVEWHEEL_H
#define SWERVEDRIVEWHEEL_H

#include <frc/controller/PIDController.h>
#include <rev/CANSparkMax.h>
#include <math/Calculator.h>

class SwerveDriveWheel
{
private:
    frc::PIDController *directionController;       // PID Controller for direction control
    rev::CANSparkMax *directionMotor;              // Motor controlling the wheel's direction
    rev::CANSparkMax *speedMotor;                  // Motor controlling the wheel's speed
    rev::SparkMaxRelativeEncoder directionEncoder; // Encoder for measuring the wheel's direction

public:
    SwerveDriveWheel(double P, double I, double D, rev::CANSparkMax *directionMotor, rev::CANSparkMax *speedMotor);
    void setDirection(double setPoint);
    void setSpeed(double speed);
    ~SwerveDriveWheel(); // Destructor to clean up memory

    // Add other member functions or variables as needed
};

#endif // SWERVEDRIVEWHEEL_H