#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
class User;
class exception_handling
{
public:
    string error;
    exception_handling(string a)
    {
        this->error = a;
    }
    void display()
    {
        cout << error << endl;
    }
};
class Vehicle
{
public:
    string name;
    int id, mileage, no_of_battery, back_up_battery;
    bool status = true;
    float rate, battery_percentage=100;
    string location;
    int chargeperhour;
    User *u;
    Vehicle(){};
    Vehicle(string name, int id, float rate, string location, float chargeperhour)
    {
        this->name = name;
        this->id = id;
        this->rate = rate;
        this->location = location;
        this->chargeperhour = chargeperhour;
    };
    virtual bool availabe() {}
    virtual void charge_the_battery() {}
    virtual void Bill(int h)
    {
        int total;
        total = chargeperhour * h;
        cout << "-----Invoice-----" << endl;
        cout << endl;
        cout << "Your vehicle: " << name << endl;
        cout << "Number of hours vehicle's been rented: " << h << endl;
        cout << "Charge of your rented Vehicle: " << chargeperhour << endl;
        cout << "Calculating your Bill" << endl;
        cout << "----------------------------------------------------" << endl;
        Sleep(2000);
        cout << "Grand Total ="
             << "  " << total << endl;
        cout << "----------------------------------------------------" << endl;
    }
};

class Rent
{
public:
    Vehicle b[100];
    int count = 0;
    void add(Vehicle v)
    {
        b[count] = v;
        count++;
    }
    int rent_vehicle(int id,string location)
    {
        int index;
        try
        {
            index = (find(id,location));
        }
        catch (exception_handling e)
        {
            e.display();
            throw e;
            return -1;
        }
        if (b[index].availabe())
        {
            b[index].status = false;
        }
        else
        {
            cout << "Requested vehicle is  is not available" << endl;
            cout << "Try renting other Vehicles !" << endl;
        }
        return index;
    }

     void return_vehicle(Vehicle *base, string location,int h)
    {
        int index = find(base->id);

        b[index].status = true;
        b[index].u = NULL;
        b[index].location = location;
        b[index].battery_percentage-=(b[index].battery_percentage*h)/b[index].mileage;
        cout<<"Remaining Battery : "<<(int)b[index].battery_percentage<<endl;
        cout << "Your vehicle is successfully returned"
             << " "
             << "at"
             << " " << location <<" Branch "<< endl;
        cout << "Thank you" << endl;
        cout << endl;
    }

    void display()
    {
        for (int i = 0; i < count; i++)
        {
            cout << "Vehicle : " << b[i].name << " "
                 << "is available at "
                 << " Location : " << b[i].location << endl;
            cout << endl;
        }
    }
    void display(string location)
    {
        for (int i = 0; i < count; i++)
        {
            if (b[i].location == location)
                cout << b[i].name << " "
                     << " " << b[i].id << "  is available  " << endl;
        }
    }
    int find(int id)
    {
        for (int i = 0; i < count; i++)
        {
            if (b[i].id == id)
                return i;
        }
        exception_handling e("invalid id");
        throw e;
    }
    int find(int id,string location)
    {
        for (int i = 0; i < count; i++)
        {
            if (b[i].id == id&&b[i].location==location)
                return i;
        }
        exception_handling e("invalid id");
        throw e;
    }
};
Rent p;
class User
{
public:
    string name;
    long contact;
    int id;
    int balance = 500;
    Vehicle *v;
    int hours;
    User(string name, long contact, int id, int balance)
    {
        this->name = name;
        this->contact = contact;
        this->id = id;
        this->balance = balance;
        this->v=NULL;
    }
    User(string name, long contact, int id)
    {
        this->name = name;
        this->contact = contact;
        this->id = id;
        this->v=NULL;
    }
    void rent_vehicle()
    {
        string choose;
        int id, h;
        cout << endl
             << endl;
        cout << "Enter your Nearest Location " << endl;
        cout << "a. Vidyanagar " << endl
             << "b. Shirur Park" << endl
             << "c. Hosur " << endl
             << "d. Unkal" << endl;
        cout << endl;
        cin >> choose;
        p.display(choose);
        cout << "Enter the vehicle ID" << endl;
        cin >> id;
        int index;
        try
        {
            index=p.rent_vehicle(id,choose);
        }
        catch(exception_handling e)
        {
            return;
        }
         p.rent_vehicle(id,choose);
        p.b[index].u = this;
        v = &(p.b[index]);
        cout << "How many hours you wanna rent? " << endl;
        cin >> h;
        if (balance < (h * v->rate))
        {
            v = NULL;
            cout << endl;
            exception_handling e("LOW BALANCE");
            cout << endl;
            throw e;
        }
        
        else
        {
            balance -= h * v->rate;
        }
        hours=h;
        cout << "This  bicylce is rented to you" << endl;
        cout << "username: " << name << endl;
        v->Bill(h);
        cout << endl;
    }

    void return_vehicle()
    {
        if (v == NULL)
        {
            exception_handling e("invalid return ");
            throw e;
            return;
        }
        cout << "Enter the Location you want to return :  " << endl;
        cout << "a. Vidyanagar " << endl
             << "b. Shirur Park" << endl
             << "c. Hosur " << endl
             << "d. Unkal" << endl;
        cout << endl;
        string location;
        cin >> location;
        p.return_vehicle(v, location,hours);
        v = NULL;
    }

    void display()
    {
        cout << name << " " << id << " ";
        if (v != NULL)
            cout << "User Name : " << v->name << " "
                 << " User Id " << v->id << " " << endl;
    }
};

class Ebike : public Vehicle
{
public:
    Ebike(string name, int id, float rate, int no_of_battery, int mileage, string location, float chargeperhour) : Vehicle(name, id, rate, location, chargeperhour)
    {
        this->no_of_battery = no_of_battery;
        this->mileage = mileage;
        p.add(*this);
    }
    bool available()
    {
        if (status == true)
        {
            if (battery_percentage > 0)
                return true;
        }

        return false;
    }
    void display()
    {
        cout << name << " " << id << " " << battery_percentage << " ";
        if (status == true)
            cout << u->name << endl;
    }
    void Bill(int h)
    {
        int total;
        total = chargeperhour * h;
        cout << "-----Invoice-----" << endl;
        cout << endl;
        cout << "Your vehicle: " << name << endl;
        cout << "Number of hours vehicle's been rented: " << h << endl;
        cout << "Charge of your rented Vehicle: " << chargeperhour << endl;
        cout << "Calculating your Bill" << endl;
        cout << "----------------------------------------------------" << endl;
        Sleep(2000);
        cout << "Grand Total ="
             << "  " << total << endl;
        cout << "----------------------------------------------------" << endl;
    }
};

class Ebicycle : public Vehicle
{
    
public:
  Ebicycle(string name, int id, float rate, int no_of_battery, int mileage, string location, float chargeperhour) : Vehicle(name, id, rate, location, chargeperhour)
    {
        this->no_of_battery = no_of_battery;
        this->mileage = mileage;
        p.add(*this);
    }

    bool available(int size)
    {
        if (status == true)
        {
            return true;
        }

        return false;
    }

    void display()
    {
        cout << name << " " << id << " " << endl;
    }


    void charge_the_battery()
    {
        cout << "charging the battery " << endl;
        for (int i = int(battery_percentage); i < 101; i = i * 10)
            cout << "charging " << (int)battery_percentage << endl;

        cout << "battery is fully charged " << endl;
    }
    void Bill(int h)
    {
        int total;
        total = chargeperhour * h;
        cout << "-----Invoice-----" << endl;
        cout << "User's name : " << u->name << endl;
        cout << "User's Phone: " << u->contact << endl;
        cout << endl;
        cout << "Your vehicle: " << name << endl;
        cout << "Number of hours vehicle's been rented: " << h << endl;
        cout << "Charge of your rented Vehicle: " << chargeperhour << endl;
        cout << "Calculating your Bill" << endl;
        cout << "----------------------------------------------------" << endl;
        Sleep(2000);
        cout << "Grand Total =" << total << endl;
        cout << "----------------------------------------------------" << endl;
    }
};

int main()
{
    cout << endl
         << endl;
    cout << "----- Savari E-Vehicle Rental System ------" << endl;
    cout << endl
         << endl;
    User c1("P S Aditya", 9365826, 10);
    User c2("Bodha CoolKarni", 7642464, 11);
    User c3("Shashank Hegday", 9534343, 12);
    Ebike b1(" Hero Electro ", 10, 25, 2, 60, "Vidyanagar", 7);
    Ebike b2(" Honda Zap ", 11, 26, 1, 100, "Shirurpark", 8);
    Ebike b3(" Tvs Electron Pro ", 12, 23, 1, 120, "Hosur", 9);
    Ebicycle e1(" Hero Lectro Renew 26T ", 10, 36, 3, 40, "Unkal", 4);
    Ebicycle e2(" Swagtron EB-6 T Bandit ", 11, 35, 4, 50, "Shirur Park", 3);
    Ebicycle e3(" LightSpeed Glyd ", 15, 40, 5, 60, "Vidyanagar", 5);

    cout << endl;
    cout << " List  of all the vehicles available for renting :-  " << endl;
    cout << endl
         << endl;
    p.display();
    cout << endl;
    try
    {
        c3.rent_vehicle();
    }
    catch (exception_handling e)
    {
        e.display();
    }

    cout << endl;
    // c3.display();
    cout << endl;
    try
    {
        c3.return_vehicle();
    }
    catch(exception_handling e)
    {
        e.display();
    }
    
    
    cout << endl;
    // c3.display();
    cout << endl;
    // p.display();
    cout << endl;
    cout << "Thank You ! " << endl;
    cout << "visit again" << endl;
    cout << endl;
    return 0;
}
