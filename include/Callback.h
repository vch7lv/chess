#pragma once
#include <memory>
#include <functional>
#include <tuple>

struct CallbackBase
{
    public:
        virtual void invoke() = 0;
        virtual ~CallbackBase() = default;
};

namespace detail
{
    template <int... Is>
    struct index {};

    template <int N, int... Is>
    struct gen_seq : gen_seq<N-1,N-1, Is...> {};

    template <int... Is>
    struct gen_seq<0, Is...> : index<Is...> {};
};

template <typename... Ts>
struct Callback final : public CallbackBase
{
    private:
        std::function<void(Ts...)> f;
        std::tuple<Ts...> args;
    public:
        template <typename F, typename... Args>
        Callback(F&& f, Args&& ... args) :
            f(std::forward<F>(f)), args(std::forward<Args>(args) ...) {}

        virtual ~Callback() = default;

        template <typename... Args, int... Is>
        void func(std::tuple<Args...>& tup, detail::index<Is...>)
        {
            f(std::get<Is>(tup)...);
        }

        template <typename... Args>
        void func(std::tuple<Args...>& tup)
        {
            func(tup, detail::gen_seq<sizeof...(Args)>{});
        }

        virtual void invoke() override
        {
            func(args);
        }
    
};

template <typename F, typename... Args>
std::unique_ptr<CallbackBase> createCallback(F&& f, Args&&... args)
{
    return std::unique_ptr<CallbackBase>(new Callback<Args...>(std::forward<F>(f), std::forward<Args>(args)...));
}
