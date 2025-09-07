# Parking Lot Management System (C++ Console App)

A **console-based parking lot management system** implemented in C++ using **object-oriented design** and **strategy design patterns** , **singleton design pattern** , **factory design pattern** for flexible fee and payment handling.

---

## Features

- **Support for multiple vehicle types**: Cars, Bikes, and Trucks.  
- **Flexible Fee Calculation** using Strategy Pattern:
  - `FeeForMembers` – discounted fees for members.  
  - `FeeForNormies` – standard fees for non-members.  
- **Flexible Payment Methods** using Strategy Pattern:
  - UPI  
  - Credit Card  
  - Debit Card  
- Manage **Parking Slots** for each vehicle type.  
- Park and unpark vehicles with automatic **fee collection**.  
- Track **occupied and available slots** in real time.  
- Handle **insufficient payments** with clear messages and returned change.

---

## Class Overview

### Core Classes

- **Vehicle** – Base class for all vehicles (Car, Bike, Truck) with a `FeeStrategy`.  
- **FeeStrategy** – Abstract class for calculating parking fees.  
  - `FeeForMembers` – Fee calculation for members.  
  - `FeeForNormies` – Fee calculation for normal users.  
- **PaymentStrategy** – Abstract class for payment processing.  
  - `UPI`, `CreditCard`, `DebitCard` – Concrete payment methods.  
- **PaymentProcessor** – Handles payment validation and execution.  
- **ParkingSlot** – Represents a parking slot for a specific vehicle type.  
- **ParkingLot** – Manages all parking slots, vehicle parking/unparking, and displays status.  

---

## Installation & Compilation

1. Clone the repository:

```bash
git clone <repo-url>
cd parking-lot-system
