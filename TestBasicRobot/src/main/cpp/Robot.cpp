// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc/TimedRobot.h>
#include <frc2/command/CommandScheduler.h>
#include <frc/drive/DifferentialDrive.h>
#include <rev/CANSparkMax.h>
#include <rev/CANSparkMaxLowLevel.h>
#include <frc/XboxController.h>
#include <math/Calculator.h>
#include <components/SwerveDriveWheel.h>
#include <components/SwerveDriveCoordinator.h>
#include <frc/DataLogManager.h>

rev::CANSparkMax *wheelMotor;
rev::CANSparkMax *angleMotor;
frc::PIDController *swerveController;
rev::SparkMaxRelativeEncoder *angleMotorEncoder;

SwerveDriveWheel *frontLeftSwerveWheel;
SwerveDriveWheel *frontRightSwerveWheel;
SwerveDriveWheel *backLeftSwerveWheel;
SwerveDriveWheel *backRightSwerveWheel;

SwerveDriveCoordinator *swerveDriveCoordinator;

frc::XboxController *xboxController;

bool is4Motors = false;

void Robot::RobotInit()
{
  frc::DataLogManager::Start();
  wheelMotor = new rev::CANSparkMax(DriveConstants::kDrivingCanID, DriveConstants::kMotorType);
  angleMotor = new rev::CANSparkMax(DriveConstants::kAngleCanId, DriveConstants::kMotorType);
  swerveController = new frc::PIDController(DriveConstants::kWheelP, DriveConstants::kWheelI, DriveConstants::kWheelD);
  rev::SparkMaxRelativeEncoder localEncoderVar = angleMotor->GetEncoder();
  angleMotorEncoder = &localEncoderVar;
  if (is4Motors)
  {
    rev::CANSparkMax *frontLeftWheelMotor = new rev::CANSparkMax(DriveConstants::kFrontLeftDrivingCanId, DriveConstants::kMotorType);
    rev::CANSparkMax *frontRightWheelMotor = new rev::CANSparkMax(DriveConstants::kFrontRightDrivingCanId, DriveConstants::kMotorType);
    rev::CANSparkMax *backLeftWheelMotor = new rev::CANSparkMax(DriveConstants::kRearLeftDrivingCanId, DriveConstants::kMotorType);
    rev::CANSparkMax *backRightWheelMotor = new rev::CANSparkMax(DriveConstants::kRearRightDrivingCanId, DriveConstants::kMotorType);

    rev::CANSparkMax *frontLeftAngleMotor = new rev::CANSparkMax(DriveConstants::kFrontLeftTurningCanId, DriveConstants::kMotorType);
    rev::CANSparkMax *frontRightAngleMotor = new rev::CANSparkMax(DriveConstants::kFrontRightTurningCanId, DriveConstants::kMotorType);
    rev::CANSparkMax *backLeftAngleMotor = new rev::CANSparkMax(DriveConstants::kRearLeftTurningCanId, DriveConstants::kMotorType);
    rev::CANSparkMax *backRightAngleMotor = new rev::CANSparkMax(DriveConstants::kRearRightTurningCanId, DriveConstants::kMotorType);

    rev::SparkMaxRelativeEncoder frontLeftDirectionEncoder = frontLeftAngleMotor->GetEncoder();
    rev::SparkMaxRelativeEncoder frontRightDirectionEncoder = frontRightAngleMotor->GetEncoder();
    rev::SparkMaxRelativeEncoder backLeftDirectionEncoder = backLeftAngleMotor->GetEncoder();
    rev::SparkMaxRelativeEncoder backRightDirectionEncoder = backRightAngleMotor->GetEncoder();

    frontLeftSwerveWheel = new SwerveDriveWheel(DriveConstants::kWheelP, DriveConstants::kWheelI, DriveConstants::kWheelD, &frontLeftDirectionEncoder, frontLeftAngleMotor, frontLeftWheelMotor);
    frontRightSwerveWheel = new SwerveDriveWheel(DriveConstants::kWheelP, DriveConstants::kWheelI, DriveConstants::kWheelD, &frontRightDirectionEncoder, frontRightAngleMotor, frontRightWheelMotor);
    backLeftSwerveWheel = new SwerveDriveWheel(DriveConstants::kWheelP, DriveConstants::kWheelI, DriveConstants::kWheelD, &backLeftDirectionEncoder, backLeftAngleMotor, backLeftWheelMotor);
    backRightSwerveWheel = new SwerveDriveWheel(DriveConstants::kWheelP, DriveConstants::kWheelI, DriveConstants::kWheelD, &backRightDirectionEncoder, backRightAngleMotor, backRightWheelMotor);

    swerveDriveCoordinator = new SwerveDriveCoordinator(frontLeftSwerveWheel, frontRightSwerveWheel, backLeftSwerveWheel, backRightSwerveWheel);
  }
  xboxController = new frc::XboxController(OperatorConstants::kDriverControllerCANId);
}

/**
 * This function is called every 20 ms, no matter the mode. Use
 * this for items like diagnostics that you want to run during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic()
{
  frc2::CommandScheduler::GetInstance().Run();
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

/**
 * This autonomous runs the autonomous command selected by your {@link
 * RobotContainer} class.
 */
void Robot::AutonomousInit()
{
  m_autonomousCommand = m_container.GetAutonomousCommand();

  if (m_autonomousCommand)
  {
    m_autonomousCommand->Schedule();
  }

  // workspace

  // define motor
  //

  // end region workspace
}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit()
{
  // This makes sure that the autonomous stops running when
  // teleop starts running. If you want the autonomous to
  // continue until interrupted by another command, remove
  // this line or comment it out.
  if (m_autonomousCommand)
  {
    m_autonomousCommand->Cancel();
  }
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic()
{
  // true for testing neo motor, false for testing swerve motor
  bool isNeo = false;
  if (isNeo)
  {
    // frc::XboxController::GetLeftY for testing purposes
    double leftY = xboxController->GetLeftY();
    // Set a threshold between -0.10 and 0.10 where the motor speed will ignore input from the controller
    // -0.1 <= x <= 0.1
    if (-OperatorConstants::kControllerDeadzoneThreshold <= leftY && leftY <= OperatorConstants::kControllerDeadzoneThreshold)
    {
      wheelMotor->Set(0.0);
    }
    else
    {
      double wheelSpeed = leftY / 2; // Set the wheel speed to the left Y axis value (should be between -1 - 1)
      wheelMotor->Set(wheelSpeed);
    }
  }
  else if (!is4Motors && !isNeo)
  {

    double leftX = xboxController->GetLeftX();
    double leftY = xboxController->GetLeftY();

    // Set a threshold between -0.10 and 0.10 where the motor speed will ignore input from the controller
    // -0.1 <= x <= 0.1
    if (-OperatorConstants::kControllerDeadzoneThreshold <= leftY && leftY <= OperatorConstants::kControllerDeadzoneThreshold)
    {
      wheelMotor->Set(0.0);
    }
    else
    {
      // Calculate wheel speed based on Y-axis input for forward/backward movement
      double forwardSpeed = leftY / 2;
      double inputAngle = std::atan2(leftY, leftX);

      // Get the current angle from the encoder
      double currentAngle = angleMotorEncoder->GetPosition();

      // Calculate the setpoint angle and its flipped counterpart
      double setpointAngle = Calculator::closestAngle(currentAngle, inputAngle);
      double setpointAngleFlipped = Calculator::closestAngle(currentAngle, inputAngle + 180.0);

      // Determine the closest setpoint angle and set it to the PID controller
      /*if (std::abs(setpointAngle) <= std::abs(setpointAngleFlipped))
      {
        double targetAngle = currentAngle + setpointAngle;
        swerveController->SetSetpoint(targetAngle);

        double requiredSpeed = swerveController->Calculate(currentAngle);

        angleMotor->Set(requiredSpeed);
      }
      else
      {
        double targetAngle = currentAngle + setpointAngleFlipped;
        swerveController->SetSetpoint(targetAngle);

        double requiredSpeed = swerveController->Calculate(currentAngle);

        angleMotor->Set(requiredSpeed);
      }*/
      // sets wheel speed
      wheelMotor->Set(forwardSpeed);
    }
  }
  else if (is4Motors)
  {
    double leftX = xboxController->GetLeftX();
    double leftY = xboxController->GetLeftY();
    double rightX = xboxController->GetRightX();

    // Set a threshold between -0.10 and 0.10 where the motor speed will ignore input from the controller
    // -0.1 <= x <= 0.1
    double angle = std::atan2(leftY, leftX);
    double magnitude = Calculator::calculateDeadzone(std::hypot(leftX, leftY));

    double twist = Calculator::calculateDeadzone(rightX);
    swerveDriveCoordinator->setSwerveDrive(angle, magnitude, twist);
  }
}

/**
 * This function is called periodically during test mode.
 */
void Robot::TestPeriodic() {}

/**
 * This function is called once when the robot is first started up.
 */
void Robot::SimulationInit() {}

/**
 * This function is called periodically whilst in simulation.
 */
void Robot::SimulationPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif
