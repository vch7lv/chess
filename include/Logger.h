#pragma once
#include <string>
#include <memory>

class Logger
{
    protected:
        Logger() = default;
        virtual ~Logger() = default;
        
    public:
        virtual void log(const std::string& message) = 0;

        Logger(const Logger&) = delete;
        Logger& operator = (const Logger&) = delete;

        static std::shared_ptr<Logger> getInstance();
        virtual void destroy() = 0;
};

template<typename T>
struct LoggingDeletor
{
    void operator () (T* ptr) const {
        auto logger = Logger::getInstance();
        std::string TypeName = typeid(T).name();
        logger->log(TypeName + " object is deleted");
        delete ptr;
    }
};



