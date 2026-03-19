# Heating Valve Controller (ATtiny1624)

<img src="https://github.com/user-attachments/assets/0ac04ef5-8807-42a1-8004-707c2818bc5b" width="50%"/><img src="https://github.com/user-attachments/assets/9d519576-e604-4d47-82fa-b55e61804939" width="50%"/>
<img src="https://github.com/user-attachments/assets/173838d6-8aec-42bc-8077-2eed35edfb0e" width="50%"/><img src="https://github.com/user-attachments/assets/d3420948-c336-44d4-9218-1dda9c8412e3" width="50%"/>

Embedded firmware for an AVR microcontroller–based heating system controller.  
The system regulates room temperature by controlling a motorized valve using a stepper motor, based on:

-    *Room temperature (LM35)*
-    *Hot water temperature (LM35)*   
-    *Valve angle feedback (MagnTek MT6701 magnetic encoder)*  
-   *Bluetooth communication (Huamao Technology HM-10 BLE module)*
    
The controller supports both **automatic operating mode** and **Bluetooth programming mode** with CRC-validated commands.

## Hardware

-   ATtiny1624 microcontroller
    
-   DRV8825 Stepper motor driver
    
-   MT6701 magnetic angle sensor
    
-   2× LM35 temperature sensors
    
-   HM-10 BLE module
    
-   Circulation pump (GPIO controlled relay)
    
-   User button (programming mode trigger)

  
###  Wiring diagram
<p align="center">
<img src="https://github.com/user-attachments/assets/89bff817-1c4d-4e77-ac0f-cdc4fb8be970" width="50%" align="center"/>
</p>

## Operating Modes

###  Programming Mode (Bluetooth)

Activated when button is pressed during power-up.

-   Receives commands in format:
   
   
>  <COMMAND+CRC>

### Example Commands

  - `<DT14505A0B4A63>`  Set configuration parameters

The example string `DT14505A0B4A63` is not a fixed command type, meaning its data fields can change depending on how we want the system to operate.

The only constant part of this command is `DT`.

The structure is as follows:

-   `DT` – command identifier (constant)
    
-   `14` – room temperature setpoint (hex value; `0x14` = 20°C)
    
-   `5` – temperature hysteresis (`5` = ±5°C)
    
-   `05A` – valve **closed** angle (`0x05A` = 90°)
    
-   `0B4` – valve **open** angle (`0x0B4` = 180°)
    
-   `A` – allowable angle deviation (`A` = 10°)
    
-   `63` – CRC
    

The CRC (CDMA-2000) is calculated using the ASCII representation of the command string, not the hexadecimal byte values. Other commands are of a fixed type, therefore their CRC never changes.

  - `<MESA2A>`  Measure valve angle

 - `<REDT10>`  Read temperatures

 - `<PTSTE8>`  Pump toggle

 - `<SAVE02>`  Save to EEPROM

 - `<EXITC6>`  Exit programming mode  

###  Regular Working Mode

In normal mode the system continuously:

-   Reads valve angle (MT6701)
    
-   Reads room & water temperatures (LM35)
    
-   Controls:
    
    -   Stepper motor
        
    -   Pump
        
-   Sends periodic Bluetooth status report (every 5 seconds)
    

----------

##  Control Logic

The control algorithm is implemented in (WORK.c):

> void  Controll();

It evaluates:

-   *Room temperature*
    
-   *Water temperature*
    
-   *Temperature deviation (hysteresis)*
    
-   *Valve position*
    

### Valve States

    CLOSED  
    OPENING  
    OPENED  
    CLOSING

### Behavior Summary

|  Condition          |        Action  |
| --- | --- |
| **Water hot enough**     | Open valve      |
| **Water too cold**       |Close valve     |
| **Room too hot**         |Stop pump       |
| **Room needs heat**      |Turn pump ON    |
| **Target angle reached** |Stop stepper    |

Stepper motor movement is verified using encoder feedback (MT6701 angle).

## EEPROM

Configuration is stored persistently (EEPROM.c):

> void  ReadAll(); 
> 
> void  SaveAll();

Stored parameters include:

-   Room air temperature setpoint `WORK.Room_air_temp_set_point`
    
-   Temperature deviation `WORK.Temp_deviation`
    
-   Open valve angle `WORK.Open_angle_set_point`
    
-   Close valve angle `WORK.Close_angle_set_point`
    
-   Angle deviation `WORK.Angle_deviation` 
    

----------

##  Timers

-   **TCA0** → Stepper pulse generation (µs precision)
    
-   **RTC** → 5-second periodic status reporting

