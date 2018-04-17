# fsae-code
Code relevant to engine control for BuffsRacing FDT.

Checklist:
Implement "sortaEquals" function for plausibility
Failure condition for wiring failure
Condition for operating ranges
BrakeThrottleMap::CheckMap
Add "sortaEquals" style plausibility checking (10%) to all applicable plausibility checks
Parameters::CutThrottle needs to be finished (mostly done)
Parameters::CutIgnition needs to be filled in
Implement pulses for shifter. (Clutchless shifting, right?)
Remove clutch interactions after confirming that's what we decided on
Implement communication between shifter class and parameters class
APPSTPSMap::Map (should be easy)
Generate actual TPS map data
Generate actual Brake-Throttle check map data
Implement failure condition when initializing inputs
Shift into first on startup
Implement failure condition when initializing shifter

