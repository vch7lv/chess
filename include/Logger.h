#include <iostream>
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

    friend std::default_delete<Logger>;
};