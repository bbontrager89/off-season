#include "components/SwerveDriveWheel.h"

#include <Constants.h>

// Constructor definition
SwerveDriveWheel::SwerveDriveWheel(double P, double I, double D,
                                   rev::CANSparkMax *directionMotor,
                                   rev::CANSparkMax *speedMotor)
    : directionMotor(directionMotor),
      speedMotor(speedMotor),
      directionEncoder(directionMotor->GetEncoder()) {
  directionController = new frc2::PIDController(P, I, D);
}

// Function to set the direction of the wheel
void SwerveDriveWheel::setDirection(double setPoint) {
  directionController->Reset();  // Reset the PID controller

  // Get the current angle from the encoder
  double currentAngle = directionEncoder.GetPosition();

  // Calculate the setpoint angle and its flipped counterpart
  double setpointAngle = Calculator::closestAngle(currentAngle, setPoint);
  double setpointAngleFlipped =
      Calculator::closestAngle(currentAngle, setPoint + 180.0);

  // Determine the closest setpoint angle and set it to the PID controller
  if (std::abs(setpointAngle) <= std::abs(setpointAngleFlipped)) {
    double targetAngle = currentAngle + setpointAngle;
    directionController->SetSetpoint(targetAngle);

    double requiredSpeed = directionController->Calculate(currentAngle);

    directionMotor->Set(requiredSpeed);
  } else {
    double targetAngle = currentAngle + setpointAngleFlipped;
    directionController->SetSetpoint(targetAngle);

    double requiredSpeed = directionController->Calculate(currentAngle);

    directionMotor->Set(requiredSpeed);
  }
}

// Function to set the speed of the wheel
void SwerveDriveWheel::setSpeed(double speed) {
  double adjustedSpeed = speed;
  if (speed > DriveConstants::kWheelMaxSpeed) {
    adjustedSpeed = DriveConstants::kWheelMaxSpeed;
  }
  if (speed < -DriveConstants::kWheelMaxSpeed) {
    adjustedSpeed = -DriveConstants::kWheelMaxSpeed;
  }
  speedMotor->Set(adjustedSpeed);  // Set the speed of the wheel using the speed
                                   // motor using the max speed
}

// Destructor definition
SwerveDriveWheel::~SwerveDriveWheel() {
  // Clean up memory in the destructor
  delete directionController;
}