# STM32 Hydraulic Control Unit

Embedded firmware for a hydraulic actuator control system using STM32 microcontroller.

## Features
- CAN Bus communication for command and telemetry
- ADC + DMA sensor acquisition
- Monitoring of:
  - Bus Voltage
  - Current
  - Hydraulic Pressure
  - Fluid Level
  - MOSFET Temperature
  - Motor Temperature
- Relay-based hydraulic UP/DOWN control
- PWM control for proportional valve
- Button input with debounce logic
- Periodic system status transmission via CAN

## Hardware
- STM32-F1 series
- CAN Transceiver
- Pressure Sensor
- NTC Temperature Sensors
- Current Sensor
- Relay Driver
- PWM Valve Driver

## Communication
- CAN RX ID: `0x100` (Control commands)
- CAN TX ID: `0x101` (System status)

## Tools
- STM32CubeIDE
- STM32 HAL Drivers
- Git / GitHub
