# Header

**Bold** 

*Italic*

Unordered list:
- One item
- Two items
- Three items

Ordered list: 
1. ordered
2. list
3. format 

## subheader

Thisis a subheader section for notes related to the main header

## here is a nother subsection

This is anotgher section

# Start new header

And wejust keep going 

## Code Examples

```py
def HelloWorld():
    print('Hello World')
```

```cpp
int HelloWorld() {
    std::cout >> "Hello World";
    return 0;
}
```
[GearIntakeRoller.java example (line 33)](https://github.com/Team2168/2017_Main_Robot/blob/develop/src/org/team2168/subsystems/GearIntakeRoller.java)
```java
	private GearIntakeRoller() {
		if(Robot.isPracticeRobot())
		{
			GearIntakeMotor = new Victor(RobotMap.GEAR_INTAKE_MOTOR);
		}
		else
		{
			GearIntakeMotor  = new Spark(RobotMap.GEAR_INTAKE_MOTOR);
		}

		GearIntakeMotorIRSensor = new AnalogInput(RobotMap.GEAR_INTAKE_ROLLER_IR);
		
		//ConsolePrinter.putNumber("GearIntakeMotor1Current", () -> {return Robot.pdp.getChannelCurrent(RobotMap.ge));
		ConsolePrinter.putNumber("Raw Gear IR", () -> {return Robot.gearIntakeRoller.getIRVoltage();}, true, false);
		ConsolePrinter.putBoolean("IsGearPresent", () -> {return Robot.gearIntakeRoller.isGearPresent();}, true, false);


		
	}
```

# References

This section is where I put all my links

[Markdown Cheat Sheet](https://www.markdownguide.org/cheat-sheet/)