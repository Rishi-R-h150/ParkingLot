#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Forward declaration
class FeeStrategy;

// Vehicle part
class Vehicle {
private:
    string vehicleType;
    int vehicleId;
    FeeStrategy* feeStrategy;
    
public:
    Vehicle(string type, int id, FeeStrategy* strategy) {
        this->vehicleType = type;
        this->vehicleId = id;
        this->feeStrategy = strategy;
    }
    
    string getVehicleType() {
        return vehicleType;
    }
    
    int getVehicleId() {
        return vehicleId;
    }
    
    FeeStrategy* getFeeStrategy() {
        return feeStrategy;
    }
};

// Fee Strategy part
class FeeStrategy {
public:
    virtual int computeFee(Vehicle* vehicle) = 0;
    virtual ~FeeStrategy() {}
};

class FeeForMembers : public FeeStrategy {
public:
    int computeFee(Vehicle* vehicle) override {
        string type = vehicle->getVehicleType();
        
        if(type == "car") {
            return 100;
        }
        else if(type == "truck") {
            return 1000;
        }
        else if(type == "bike") {
            return 50;
        }
        return 0;
    }
};

class FeeForNormies : public FeeStrategy {
public:
    int computeFee(Vehicle* vehicle) override {
        string type = vehicle->getVehicleType();
        
        if(type == "car") {
            return 150;
        }
        else if(type == "truck") {
            return 1500;
        }
        else if(type == "bike") {
            return 100;
        }
        return 0;
    }
};

// Specific Vehicle types
class Bike : public Vehicle {
public:
    Bike(int id, FeeStrategy* feeStrategy) : Vehicle("bike", id, feeStrategy) {}
};

class Car : public Vehicle {
public:
    Car(int id, FeeStrategy* feeStrategy) : Vehicle("car", id, feeStrategy) {}
};

class Truck : public Vehicle {
public:
    Truck(int id, FeeStrategy* feeStrategy) : Vehicle("truck", id, feeStrategy) {}
};

// Payment Part
class PaymentStrategy {
public:
    virtual void initiatePayment(int amount) = 0;
    virtual ~PaymentStrategy() {}
};

class UPI : public PaymentStrategy {
public:
    void initiatePayment(int amount) override {
        cout << "Payment of Rs. " << amount << " done via UPI" << endl;
    }
};

class CreditCard : public PaymentStrategy {
public:
    void initiatePayment(int amount) override {
        cout << "Payment of Rs. " << amount << " done via Credit Card" << endl;
    }
};

class DebitCard : public PaymentStrategy {
public:
    void initiatePayment(int amount) override {
        cout << "Payment of Rs. " << amount << " done via Debit Card" << endl;
    }
};

class PaymentProcessor {
private:
    PaymentStrategy* paymentStrategy;
    
public:
    bool isPaid = false;
    
    PaymentProcessor(PaymentStrategy* strategy) {
        this->paymentStrategy = strategy;
    }
    
    ~PaymentProcessor() {
        delete paymentStrategy;
    }
    
    bool makePayment(int chargedAmount, int paidAmount) {
        if(chargedAmount > paidAmount) {
            isPaid = false;
            cout << "Insufficient payment. Required: " << chargedAmount << ", Paid: " << paidAmount << endl;
        }
        else {
            isPaid = true;
            paymentStrategy->initiatePayment(paidAmount);
            cout << "Change returned: " << (paidAmount - chargedAmount) << endl;
        }
        return isPaid;
    }
};

// Parking slot and Parking lot component
class ParkingSlot {
public:
    string forVehicleType;
    bool isOccupied = false;
    Vehicle* vehicle = nullptr;
    
    ParkingSlot(string forVehicleType) {
        this->forVehicleType = forVehicleType;
    }
    
    void parkVehicle(Vehicle* vehicle) {
        this->vehicle = vehicle;
        this->isOccupied = true;
    }
    
    void unPark() {
        vehicle = nullptr;
        isOccupied = false;
    }
};

class ParkingLot {
private:
    vector<ParkingSlot*> spots;
    
public:
    ParkingLot(int numCarSpots, int numBikeSpots, int numTruckSpots) {
        // Add car spots
        for(int i = 0; i < numCarSpots; i++) {
            spots.push_back(new ParkingSlot("car"));
        }
        
        // Add bike spots
        for(int i = 0; i < numBikeSpots; i++) {
            spots.push_back(new ParkingSlot("bike"));
        }
        
        // Add truck spots
        for(int i = 0; i < numTruckSpots; i++) {
            spots.push_back(new ParkingSlot("truck"));
        }
    }
    
    ~ParkingLot() {
        for(auto spot : spots) {
            delete spot;
        }
    }
    
    bool park(Vehicle* vehicle) {
        string vehicleType = vehicle->getVehicleType();
        
        // Check availability
        for(int i = 0; i < spots.size(); i++) {
            if(spots[i]->isOccupied || spots[i]->forVehicleType != vehicleType) {
                continue;
            }
            else {
                spots[i]->parkVehicle(vehicle);
                cout << "Vehicle with ID " << vehicle->getVehicleId() << " parked successfully at spot " << i << endl;
                return true;
            }
        }
        
        cout << "No available parking spot for vehicle type: " << vehicleType << endl;
        return false;
    }
    
    bool unPark(int vehicleId, PaymentStrategy* paymentStrategy, int paidAmount) {
        for(int i = 0; i < spots.size(); i++) {
            if(spots[i]->isOccupied && spots[i]->vehicle && spots[i]->vehicle->getVehicleId() == vehicleId) {
                Vehicle* vehicle = spots[i]->vehicle;
                int fee = vehicle->getFeeStrategy()->computeFee(vehicle);
                
                PaymentProcessor processor(paymentStrategy);
                bool paymentSuccess = processor.makePayment(fee, paidAmount);
                
                if(paymentSuccess) {
                    spots[i]->unPark();
                    cout << "Vehicle with ID " << vehicleId << " has been unparked from spot " << i << endl;
                    return true;
                } else {
                    cout << "Payment failed, vehicle not unparked." << endl;
                    return false;
                }
            }
        }
        
        cout << "Vehicle with ID " << vehicleId << " not found in the parking lot." << endl;
        return false;
    }
    
    void displayStatus() {
        cout << "\n--- Parking Lot Status ---" << endl;
        int carSpots = 0, bikeSpots = 0, truckSpots = 0;
        int occupiedCarSpots = 0, occupiedBikeSpots = 0, occupiedTruckSpots = 0;
        
        for(auto spot : spots) {
            if(spot->forVehicleType == "car") {
                carSpots++;
                if(spot->isOccupied) occupiedCarSpots++;
            } else if(spot->forVehicleType == "bike") {
                bikeSpots++;
                if(spot->isOccupied) occupiedBikeSpots++;
            } else if(spot->forVehicleType == "truck") {
                truckSpots++;
                if(spot->isOccupied) occupiedTruckSpots++;
            }
        }
        
        cout << "Car spots: " << occupiedCarSpots << "/" << carSpots << " occupied" << endl;
        cout << "Bike spots: " << occupiedBikeSpots << "/" << bikeSpots << " occupied" << endl;
        cout << "Truck spots: " << occupiedTruckSpots << "/" << truckSpots << " occupied" << endl;
        cout << "------------------------\n" << endl;
    }
};

int main() {
    // Create fee strategies
    FeeStrategy* memberStrategy = new FeeForMembers();
    FeeStrategy* normalStrategy = new FeeForNormies();
    
    // Create a parking lot with 3 car spots, 2 bike spots, and 1 truck spot
    ParkingLot parkingLot(3, 2, 1);
    
    // Display initial status
    parkingLot.displayStatus();
    
    // Create vehicles
    Vehicle* car1 = new Car(101, memberStrategy);
    Vehicle* car2 = new Car(102, normalStrategy);
    Vehicle* bike1 = new Bike(201, memberStrategy);
    Vehicle* truck1 = new Truck(301, normalStrategy);
    
    // Park vehicles
    parkingLot.park(car1);
    parkingLot.park(car2);
    parkingLot.park(bike1);
    parkingLot.park(truck1);
    
    // Display status after parking
    parkingLot.displayStatus();
    
    // Unpark a vehicle with successful payment
    cout << "Unparking car with ID 101:" << endl;
    parkingLot.unPark(101, new CreditCard(), 200);
    
    // Display status after unparking
    parkingLot.displayStatus();
    
    // Unpark with insufficient payment
    cout << "Unparking truck with ID 301 (insufficient payment):" << endl;
    parkingLot.unPark(301, new UPI(), 1000);
    
    // Unpark with sufficient payment
    cout << "Unparking truck with ID 301 (sufficient payment):" << endl;
    parkingLot.unPark(301, new DebitCard(), 2000);
    
    // Display final status
    parkingLot.displayStatus();
    
    // Clean up
    delete car1;
    delete car2;
    delete bike1;
    delete truck1;
    delete memberStrategy;
    delete normalStrategy;
    
    return 0;
}