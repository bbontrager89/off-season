#pragma once

#include "SwerveDriveWheel.h"

class SwerveDriveCoordinator
{
private:
    SwerveDriveWheel *leftFrontWheel;
    SwerveDriveWheel *leftBackWheel;
    SwerveDriveWheel *rightFrontWheel;
    SwerveDriveWheel *rightBackWheel;

public:
    SwerveDriveCoordinator(SwerveDriveWheel *leftFrontWheel, SwerveDriveWheel *rightFrontWheel, SwerveDriveWheel *leftBackWheel,  SwerveDriveWheel *rightBackWheel);

    void translate(double direction, double power);
    void inplaceTurn(double power);
    void translateTurn(double direction, double translatePower, double turnPower);
    void setSwerveDrive(double direction, double translatePower, double turnPower);
};