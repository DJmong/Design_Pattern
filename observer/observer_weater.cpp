#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

// Interface define >>>
class observer{
public:
    virtual void update(float temp, float humidity, float pressure) {}
};

class subject{
public:
    virtual void registerObserver(observer *o) {}
    virtual void removeObserver(observer *o) {}
    virtual void notifyObserver() {}
};

class displayElement{
public:
    virtual void display() {}
};

// Interface define <<<

// weather class define
class weatherData : subject{
public:
    void measurementChanged(){
        notifyObserver(); 
    }
    // subject interface implement >>>
    void registerObserver(observer *o) {
        std::vector<observer*> observers = getObservers();
        observers.push_back(o);
        setObservers(observers);
    }
    void removeObserver(observer *o){
        std::vector<observer*> observers = getObservers();
        std::vector<observer*>::iterator it = std::find(observers.begin(), observers.end(), o);
        if(it == observers.end())
            return;
        observers.erase(it);
        setObservers(observers);
    }
    void notifyObserver() {
        std::vector<observer*> observers = getObservers();
        const float temp = getTemperature();
        const float humidity = getHumidity();
        const float pressure = getPressure();
        for(auto it : observers)
            it->update(temp, humidity, pressure);
        // for(auto it : observers);
    }
    // subject interface implement <<<

    // setter / getter
    void setTemp(const float &temp) { m_temp = temp; measurementChanged();}
    void setHumidity(const float &humidity) { m_humidity = humidity; measurementChanged();}
    void setPressure(const float &pressure) { m_pressure = pressure; measurementChanged();}
    void setObservers(const std::vector<observer*> &observers) { m_observers = observers; measurementChanged();}
    float getTemperature() const { return m_temp;}
    float getHumidity() const  { return m_humidity;}
    float getPressure() const  { return m_pressure;}
    std::vector<observer*> getObservers() const { return m_observers;}


private:
    std::vector<observer*> m_observers;
    float m_temp;
    float m_humidity;
    float m_pressure;
};

// display definition
class displayA : observer, displayElement{
public:
    explicit displayA() {
        m_temp = 0;
        m_humidity = 0;
        m_pressure = 0;
    }
    void update(float temp, float humidity, float pressure) {
        m_temp = temp;
        m_humidity = humidity;
        m_pressure = pressure;
        display();
    }
    void display() {
        std::cout << std::setw(10) << "[A] temp : " << std::setw(5) << m_temp << std::endl;
        std::cout << std::setw(10) << "[A] humidity  : " << std::setw(5) << m_humidity << std::endl;
        std::cout << std::setw(10) << "[A] pressure  : " << std::setw(5) << m_pressure << std::endl;
    }

private:
    float m_temp;
    float m_humidity;
    float m_pressure;
};

// display definition
class displayB : observer, displayElement{
public:
    explicit displayB() {
        m_temp = 0;
        m_humidity = 0;
        m_pressure = 0;
    }
    void update(float temp, float humidity, float pressure) {
        m_temp = temp;
        m_humidity = humidity;
        m_pressure = pressure;
        display();
    }
    void display() {
        std::cout << std::setw(10) << "[B] temp : " << std::setw(5) << m_temp << std::endl;
        std::cout << std::setw(10) << "[B] humidity  : " << std::setw(5) << m_humidity << std::endl;
        std::cout << std::setw(10) << "[B] pressure  : " << std::setw(5) << m_pressure << std::endl;
    }

private:
    float m_temp;
    float m_humidity;
    float m_pressure;
};

int main(){
    weatherData data;
    displayA a;
    displayB b;
    data.setTemp(25.0);
    data.setHumidity(15.0);
    data.setPressure(20.0);

    std::cout <<  "===before register===" << std::endl;
    data.measurementChanged();

    std::cout << "===after A register===" << std::endl;
    data.registerObserver((observer*)&a);

    std::cout << "===after B register===" << std::endl;
    data.registerObserver((observer*)&b);

    std::cout << "===after Temp Changed===" << std::endl;
    data.setTemp(20.5);

    std::cout << "===after remove A===" << std::endl;
    data.removeObserver((observer*)&a);

    std::cout << "===after remove B===" << std::endl;
    data.removeObserver((observer*)&b);

}