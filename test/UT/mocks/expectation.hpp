#pragma once

template <typename ReturnType, typename... Args>
class Expectation
{
  public:
    Expectation(bool inSequence = false)
        : inSequence_(inSequence)
    {
    }

    Expectation(std::tuple<Args...> expectedArgs, bool inSequence = false)
        : inSequence_(inSequence), expectedArgs_(expectedArgs)
    {
    }

    void setInSequence()
    {
        inSequence_ = true;
    }

    void setExpectedArgs(std::tuple<Args...> expectedArgs)
    {
        expectedArgs_ = expectedArgs;
    }

    const std::tuple<Args...>& getExpectedArgs()
    {
        return expectedArgs_;
    }

    bool inSequence()
    {
        return inSequence_;
    }

    void setFile(const std::string& file)
    {
        file_ = file;
    }

    void setLine(int line)
    {
        line_ = line;
    }

    const std::string& getFile() const
    {
        return file_;
    }

    int getLine() const
    {
        return line_;
    }

    void willReturn(const ReturnType& returns)
    {
        returns_ = returns;
    }

    ReturnType returnValue()
    {
        return returns_;
    }

  private:
    bool inSequence_;
    std::tuple<Args...> expectedArgs_;
    std::string file_;
    int line_;
    ReturnType returns_;
};