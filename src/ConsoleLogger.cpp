#include "Logger.h"
#include <iostream>

struct ConsoleLogger final : public Logger {
    public:
        virtual void log (const std::string& message) override;
        virtual void destroy() override;

    private:
        ConsoleLogger() = default;
        virtual ~ConsoleLogger() = default;

        static std::shared_ptr<Logger> singleton;

    friend std::shared_ptr<Logger> Logger::getInstance();
};

std::shared_ptr<Logger> ConsoleLogger::singleton = nullptr;

std::shared_ptr<Logger> Logger::getInstance() {
    if (ConsoleLogger::singleton == nullptr) {
        auto deleter = [](Logger* p) {
            p->destroy();
        };
        ConsoleLogger::singleton = std::shared_ptr<Logger>(new ConsoleLogger(), deleter);
    }
    return ConsoleLogger::singleton;
}

void ConsoleLogger::destroy() {
    delete this;
}

void ConsoleLogger::log(const std::string& message) {
    std::cout << message << std::endl;
}