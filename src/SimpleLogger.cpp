#include "Logger.h"
#include <iostream>

struct SimpleLogger final : public Logger {
    public:
        void log (const std::string& message) override;

    private:
        SimpleLogger() = default;
        virtual ~SimpleLogger() = default;

    private:
        static std::shared_ptr<Logger> singleton;

    friend std::shared_ptr<Logger> Logger::getInstance();
};

std::shared_ptr<Logger> SimpleLogger::singleton = nullptr;

std::shared_ptr<Logger> Logger::getInstance() {
    if (SimpleLogger::singleton == nullptr) {
        auto deleter = std::default_delete<Logger>();
        SimpleLogger::singleton = std::shared_ptr<Logger>(new SimpleLogger(), deleter);
    }
    return SimpleLogger::singleton;
}

void SimpleLogger::log(const std::string& message) {
    std::cout << message << std::endl;
}