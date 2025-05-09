# 

# Project Readme: Data Structures and Algorithms - Patient Treatment Simulation

## Overview

This project simulates a patient treatment center where patients arrive, get assigned to treatments, and progress through the system based on predefined rules. The simulation tracks patient statuses, resource allocations, and generates statistics about the process.

## Project Description

The system models:

- Patients with different types (Normal and Recovering)
- Three treatment types (Electro-therapy, Ultrasound-therapy, Gym exercises)
- Resource management (devices and rooms with capacities)
- Patient scheduling with early/late arrivals and penalties
- Cancellation and rescheduling probabilities
- Multiple system states (IDLE, WAIT, SERV, FNSH, etc.)

## Input File Format

The input file contains:

1. Number of devices/rooms for each treatment type
2. Gym room capacities
3. Cancellation and rescheduling probabilities
4. Patient data including:
    - Type (N/R)
    - Appointment and arrival times
    - Required treatments with durations

## Output File Format

The output file contains:

1. Per-patient data (PID, type, times, wait/treatment durations, cancellation/rescheduling status)
2. System statistics (averages, percentages, totals)

## 

```
./program_name input_file.txt -s

```

## Key Features

- Priority queues for patient scheduling
- Resource allocation algorithms
- Late arrival penalty calculations
- Probabilistic cancellation/rescheduling
- Comprehensive statistics generation
- Two user interface modes

## Data Structures Used

- Priority queues for patient lists
- Lists for available resources
- Queues for waiting patients
- Structures to track patient states and treatment progress

## Team Members

1. Ahmed Mahmoud Haridy
2. Mohamed Amir Ahmed
3. Ahmed Mohamed Abozied
