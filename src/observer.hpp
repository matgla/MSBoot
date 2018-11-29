#include <cstdint>
#include <type_traits>

#include <optional>

#include <gsl/span>


struct GetSoft
{
    constexpr static uint8_t id = 2;
    static GetSoft deserialize(const char* payload)
    {
        return GetSoft{};
    }
};


template <>
struct get_type<MessageId::GetSoft>
{
    using type = GetSoft;
};

template <>
struct get_type<MessageId::Handshake>
{
    using type = Handshake;
};

template <typename T, T... ids>
struct operation;

template <typename T, T id, T... rest>
struct operation<T, id, rest...>
{
    static void perform(auto& observer, MessageId msg_id)
    {
        if (msg_id == id)
        {
            observer(typename get_type<id>::type{});
        }
        else
        {
            operation<T, rest...>::perform(observer, msg_id);
        }
    }
};

template <typename T>
struct operation<T>
{
    static void perform(auto& observer, MessageId msg_id)
    {
    }
};

template <typename... Observers>
struct Observer : Observers...
{
    using Observers::operator()...;
};

template <typename... Observers>
Observer(Observers...)->Observer<Observers...>;

void get_soft()
{
    std::cout << "get_soft()" << std::endl;
}
void handshake()
{
    std::cout << "handshake()" << std::endl;
}

int main()
{
    Observer observer{
        [](const GetSoft& msg) { get_soft(); },
        [](const Handshake& msg) { handshake(); }};

    using Loop = operation<MessageId, MessageId::GetSoft, MessageId::Handshake>;
    Loop::perform(observer, static_cast<MessageId>(1));
    Loop::perform(observer, static_cast<MessageId>(0));
    Loop::perform(observer, static_cast<MessageId>(0));
    // Loop::perform(observer, static_cast<MessageId>(3));
}