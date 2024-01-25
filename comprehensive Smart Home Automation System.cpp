#include <iostream>
#include <vector>
#include <map>
#include <ctime>

class Device {
public:
    std::string name;
    bool status;

    Device(const std::string& n) : name(n), status(false) {}

    void toggle() {
        status = !status;
        std::cout << name << " is " << (status ? "on" : "off") << std::endl;
    }
};

class User {
public:
    std::string username;
    std::string password;

    User(const std::string& u, const std::string& p) : username(u), password(p) {}
};

class SmartHomeSystem {
private:
    std::map<std::string, Device> devices;
    std::vector<User> users;
    User* currentUser;

    std::map<std::string, std::vector<std::string>> automationRules;
    std::vector<std::string> activityLog;

public:
    void addUser(const std::string& username, const std::string& password) {
        users.push_back(User(username, password));
    }

    bool login(const std::string& username, const std::string& password) {
        for (User& user : users) {
            if (user.username == username && user.password == password) {
                currentUser = &user;
                return true;
            }
        }
        return false;
    }

    void addDevice(const std::string& name) {
        devices.emplace(name, Device(name));
    }

    void controlDevice(const std::string& deviceName) {
        auto it = devices.find(deviceName);
        if (it != devices.end()) {
            it->second.toggle();
            logActivity("Device control", deviceName + " toggled.");
            checkAutomationRules(deviceName);
        } else {
            std::cout << "Device not found." << std::endl;
        }
    }

    void listDevices() const {
        for (const auto& device : devices) {
            std::cout << device.first << ": " << (device.second.status ? "on" : "off") << std::endl;
        }
    }

    void addAutomationRule(const std::string& deviceName, const std::string& rule) {
        automationRules[deviceName].push_back(rule);
    }

    void listAutomationRules() const {
        for (const auto& rule : automationRules) {
            std::cout << rule.first << ": ";
            for (const auto& condition : rule.second) {
                std::cout << condition << ", ";
            }
            std::cout << std::endl;
        }
    }

    void logActivity(const std::string& category, const std::string& message) {
        char buffer[80];
        time_t rawtime;
        struct tm* timeinfo;

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer, sizeof(buffer), "[%Y-%m-%d %H:%M:%S]", timeinfo);

        activityLog.push_back(std::string(buffer) + " [" + category + "] " + message);
    }

    void viewActivityLog() const {
        for (const auto& entry : activityLog) {
            std::cout << entry << std::endl;
        }
    }

private:
    void checkAutomationRules(const std::string& deviceName) {
        auto ruleIt = automationRules.find(deviceName);
        if (ruleIt != automationRules.end()) {
            for (const auto& rule : ruleIt->second) {
                std::cout << "Checking rule: " << rule << std::endl;
                // Implement rule checking logic here based on actual conditions and sensor data.
                // For simplicity, we'll just print a message.
                std::cout << "Rule condition met! Taking action..." << std::endl;
                // Implement actions based on the rule.
            }
        }
    }
};

int main() {
    SmartHomeSystem smartHome;

    // Add users
    smartHome.addUser("user1", "password1");
    smartHome.addUser("user2", "password2");

    // Login
    if (smartHome.login("user1", "password1")) {
        std::cout << "Login successful." << std::endl;
    } else {
        std::cout << "Login failed." << std::endl;
        return 1;
    }

    // Add devices
    smartHome.addDevice("Light");
    smartHome.addDevice("Fan");
    smartHome.addDevice("Thermostat");

    // Add automation rules
    smartHome.addAutomationRule("Light", "Turn on when motion detected");
    smartHome.addAutomationRule("Fan", "Turn off when temperature exceeds 30 degrees");

    // Control devices
    smartHome.listDevices();
    smartHome.controlDevice("Light");
    smartHome.controlDevice("Fan");

    // View automation rules
    smartHome.listAutomationRules();

    // View activity log
    smartHome.viewActivityLog();

    return 0;
}

