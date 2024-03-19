# Pre-Requisites
- Wifi Radio
	- Must accept connections from clients
	- Must be configured with the FRC Radio Config Utility
		- SSID = Team Number
		- Code is deployable to the roborio 

# Installation Process

## Install Limelight to Power Distribution System
Reference: [Limelight Wiring Guide](https://docs.limelightvision.io/docs/docs-limelight/getting-started/wiring)
### Install Limelight to PDP 
1. Use a power slot between 4-11 to power the limelight. With the power off, plug 20 gauge wires into the limelight and then plug the limelight into one of the open low-amp fuse slots
2. Test power to limelight by turning on the power circuit. The limelight should emit a bright green light and strobe softly until it turns off. 

### Install Limelight to PDH 
1. Use power slot 23 to power the limelight (assuming network switch is powered via slot 22; wifi radio is powered via slot 21; roborio is powered via slot 20). With the power to the PDH off, plug 20 gauge wires into the limelight and then plug the limelight into slot 23. 
2. Test power to the limelight by turning on the power circuit. The limelight should emit a bright green light and strobe softly until it turns off. 
## Limelight Local Setup
1. With the power to the limelight off, plug ethernet cable into Limelight, and connect the cable to laptop. 
2. Turn on the power to the limelight by powering the PDH/PDP. Ensure the limelight has turned on. 
3. Verify the limelight is connected to the laptop by running `ipconfig /all` in a Powershell window. (if you're using linux use `ifconfig` instead). Observe the IPv4 address (should be APIPA "169.X.X.X") to use in the following step
4. Run Limelight Finder and click "Find Limelights". Find the IP address listed in step 3, then double click on the selected limelight to open up the limelight web portal. 
5. In the web portal, under settings, find "Team Number" and set the team number equal to the team number. Click on "Set Team Number" (? verify) and power cycle the limelight.
6. Rerun limelight finder and reopen the web portal for the limelight. 
7. In the limelight's web portal, under settings, set the IP address configuration to "Static". Then, fill out the information as follows using the Team Number as AB.CD (first digit = A, second = B, etc.)
	1. In the IP Address field: Enter `10.AB.CD.5`
	2. In the Subnet Mask field: Select `255.255.255.0`
	3. In the Gateway field: Enter `10.AB.CD.1`
8. Click on "Set IP address" (? verify) and power cycle the limelight. After the power cycle is completed, turn off power to the limelight and unplug the ethernet cable from the laptop.

## Set up RoboRio Network
1. Install the network switch to the power circuit (using the PDP low amp slot or PDH slot 22). 
2. With the power off, plug an ethernet cable into Ethernet 1, and then plug that cable into the RoboRio's Ethernet port. 
3. Plug another ethernet cable into Ethernet 2, then plug that cable into the WiFi radio.
	1. Note: If you do this incorrectly, the wifi radio will be given an APIPA network address which will ruin any ability to connect normally to the wifi radio as originally configured. If this happens, please see **Recovery > Reset WiFi Radio**
4. Plug another ethernet cable into Ethernet 3, then plug that cable into the Limelight. 
5. Turn power onto the system so that all devices receive power. This should power the RoboRio, the Network Switch, the Wifi Radio, and the LimeLight synchronously. 

# Validation 
1. Limelight is found with LimeLight Viewer with the IP address set in **Limelight Local Setup**
2. Double Clicking on the Limelight IP address in LimeLight Viewer should bring up the Limelight's web portal running on port 5XXX (*TBD*) 
3. Under Settings, limelight should be set to static IP address following the same setup steps in **Limelight Local Setup**

# Recovery
If something does not validate properly figure out the issue. 

## Issue 1

## Issue 2

## Issue 3

Issue:

Resolution Steps:
1. w
2. w
3. w
