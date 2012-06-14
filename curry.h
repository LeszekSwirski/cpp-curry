#ifndef __CURRY_H__
#define __CURRY_H__

#include <functional>

template <typename TFunc>
struct curry_helper;

template<typename TRet, typename Arg1>
struct curry_helper<TRet(Arg1)>
{
    typedef std::function<TRet(Arg1)> type;
};

template <typename TRet, typename Arg1, typename Arg2, typename ...Args>
struct curry_helper<TRet(Arg1, Arg2, Args...)>
{
    typedef typename curry_helper<TRet(Arg2, Args...)>::type return_type;
    typedef std::function<return_type(Arg1)> type;
};

template<typename TFunc>
struct lambda_helper;

template <typename TClass, typename TRet, typename ...Args>
struct lambda_helper<TRet(TClass::*)(Args...) const>
{
    typedef std::function<TRet(Args...)> func_type;
};


template<typename TRet>
typename std::function<TRet()> curry(std::function<TRet()> f)
{
    return f;
}

template<typename TRet, typename Arg1>
typename std::function<TRet(Arg1)> curry(std::function<TRet(Arg1)> f)
{
    return f;
}

template<typename TRet, typename Arg1, typename Arg2, typename ...Args>
typename curry_helper<TRet(Arg1, Arg2, Args...)>::type curry(std::function<TRet(Arg1, Arg2, Args...)> f)
{
    return [f](Arg1&& x){
        return curry<TRet,Arg2,Args...>(std::function<TRet(Arg2,Args...)>(
            [f,x] (Arg2&& x2, Args&&... xs) {
                return f(x,std::forward<Arg2>(x2),std::forward<Args>(xs)...);
            })
        );
    };
}

template<typename TFunc>
auto curry(TFunc&& f) -> decltype(curry(typename lambda_helper<decltype(&TFunc::operator())>::func_type(std::forward<TFunc>(f))))
{
    return curry(typename lambda_helper<decltype(&TFunc::operator())>::func_type(std::forward<TFunc>(f)));
}

#endif//__CURRY_H__
