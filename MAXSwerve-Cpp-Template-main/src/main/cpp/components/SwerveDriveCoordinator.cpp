#include "components/SwerveDriveCoordinator.h"

#include <components/SwerveDriveWheel.h> // Include the header file where SwerveDriveWheel class is defined

SwerveDriveCoordinator::SwerveDriveCoordinator(SwerveDriveWheel *leftFrontWheel, SwerveDriveWheel *leftBackWheel, SwerveDriveWheel *rightFrontWheel, SwerveDriveWheel *rightBackWheel)
{
    this->leftFrontWheel = leftFrontWheel;
    this->rightFrontWheel = rightFrontWheel;
    this->leftBackWheel = leftBackWheel;
    this->rightBackWheel = rightBackWheel;
}

// Function to translate the robot in a specific direction at a given power
void SwerveDriveCoordinator::translate(double direction, double power)
{
    leftFrontWheel->setDirection(direction);
    leftBackWheel->setDirection(direction);
    rightFrontWheel->setDirection(direction);
    rightBackWheel->setDirection(direction);

    leftFrontWheel->setSpeed(power);
    leftBackWheel->setSpeed(power);
    rightFrontWheel->setSpeed(power);
    rightBackWheel->setSpeed(power);
}

// Function to perform an in-place turn with specified power
void SwerveDriveCoordinator::inplaceTurn(double power)
{
    leftFrontWheel->setDirection(135.0);
    leftBackWheel->setDirection(45.0);
    rightFrontWheel->setDirection(-45.0);
    rightBackWheel->setDirection(-135.0);

    leftFrontWheel->setSpeed(power);
    leftBackWheel->setSpeed(power);
    rightFrontWheel->setSpeed(power);
    rightBackWheel->setSpeed(power);
}

// Function to translate while turning the robot based on direction, translation power, and turn power
void SwerveDriveCoordinator::translateTurn(double direction, double translatePower, double turnPower)
{
    double turnAngle = turnPower * 45.0;

    // If the left front wheel is in the front
    if (Calculator::closestAngle(direction, 135.0) >= 90.0)
    {
        leftFrontWheel->setDirection(direction + turnAngle);
    }
    else
    {
        leftFrontWheel->setDirection(direction - turnAngle);
    }

    // If the left back wheel is in the front
    if (Calculator::closestAngle(direction, 225.0) > 90.0)
    {
        leftBackWheel->setDirection(direction + turnAngle);
    }
    else
    {
        leftBackWheel->setDirection(direction - turnAngle);
    }

    // If the right front wheel is in the front
    if (Calculator::closestAngle(direction, 45.0) > 90.0)
    {
        rightFrontWheel->setDirection(direction + turnAngle);
    }
    else
    {
        rightFrontWheel->setDirection(direction - turnAngle);
    }

    // If the right back wheel is in the front
    if (Calculator::closestAngle(direction, 315.0) >= 90.0)
    {
        rightBackWheel->setDirection(direction + turnAngle);
    }
    else
    {
        rightBackWheel->setDirection(direction - turnAngle);
    }

    leftFrontWheel->setSpeed(translatePower);
    leftBackWheel->setSpeed(translatePower);
    rightFrontWheel->setSpeed(translatePower);
    rightBackWheel->setSpeed(translatePower);
}

// Function to set the swerve drive based on direction, translation power, and turn power
void SwerveDriveCoordinator::setSwerveDrive(double direction, double translatePower, double turnPower)
{
    if ((translatePower == 0.0) && (turnPower != 0.0))
    {
        SwerveDriveCoordinator::inplaceTurn(turnPower);
    }
    else
    {
        SwerveDriveCoordinator::translateTurn(direction, translatePower, turnPower);
    }
}