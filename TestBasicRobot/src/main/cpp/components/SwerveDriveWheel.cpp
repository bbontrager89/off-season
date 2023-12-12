#include <frc/controller/PIDController.h>
#include <rev/CANSparkMax.h>
#include <rev/CANSparkMaxLowLevel.h>
#include <math/Calculator.h>

class SwerveDriveWheel
{
    // Declare member variables
    frc::PIDController *directionController;       // PID Controller for direction control
    rev::CANSparkMax *directionMotor;             // Motor controlling the wheel's direction
    rev::CANSparkMax *speedMotor;                 // Motor controlling the wheel's speed
    rev::SparkMaxRelativeEncoder *directionEncoder; // Encoder for measuring the wheel's direction

public:
    // Constructor to initialize the SwerveDriveWheel object
    SwerveDriveWheel(double P, double I, double D, rev::SparkMaxRelativeEncoder &directionEncoder, rev::CANSparkMax &directionMotor, rev::CANSparkMax &speedMotor)
    {
        // Assigning the passed-in parameters to the corresponding member variables
        this->directionEncoder = &directionEncoder;
        this->directionMotor = &directionMotor;
        this->speedMotor = &speedMotor;

        // Creating a new PID controller with the given PID constants
        directionController = new frc::PIDController(P, I, D);
    }

    // Function to set the direction of the wheel
    void setDirection(double setPoint)
    {
        directionController->Reset(); // Reset the PID controller

        // Get the current angle from the encoder
        double currentAngle = directionEncoder->GetPosition();

        // Calculate the setpoint angle and its flipped counterpart
        double setpointAngle = Calculator::closestAngle(currentAngle, setPoint);
        double setpointAngleFlipped = Calculator::closestAngle(currentAngle, setPoint + 180.0);

        // Determine the closest setpoint angle and set it to the PID controller
        if (std::abs(setpointAngle) <= std::abs(setpointAngleFlipped))
        {
            directionController->SetSetpoint(currentAngle + setpointAngle);
        }
        else
        {
            directionController->SetSetpoint(currentAngle + setpointAngleFlipped);
        }
    }

    // Function to set the speed of the wheel
    void setSpeed(double speed)
    {
        speedMotor->Set(speed); // Set the speed of the wheel using the speed motor
    }
};