
#include <cstdio>
#include <cassert>
#include <iostream>
#include <cstdlib>

class RLTestStatusDumper
{
private:
    bool* testStatus_;
    const char* testName_;
    
    void reportTestFailure()
    {
        printf("\033[1;31mTest failed!\033[0m\n");
    }

    void reportTestSuccess()
    {
        printf("\033[0;32mTest passed!\033[0m\n");
    }
    
    void printGreetings()
    {
        printf("=============================================\n"
               "Running test: %s\n", testName_);
    }
    
    void reportStatus()
    {
        if (*testStatus_)
            reportTestSuccess();
        else
        {
            reportTestFailure();
            printf("Please see the reason upper\n");
        }
        
        printf("=============================================\n");
    }

public:
    RLTestStatusDumper(bool* testStatus, const char* testName):
        testStatus_(testStatus),
        testName_(testName)
    {
        assert(testStatus);
        printGreetings();
    }

    ~RLTestStatusDumper()
    {
        reportStatus();
    }
};

#define DEFINE_TEST(NAME)                                           \
bool RLTest_##NAME()                                                \
{                                                                   \
    bool testStatus = true;                                         \
    RLTestStatusDumper dumper(&testStatus, #NAME);                                                               

#define ASSERT_TRUE(COND)                                           \
if (!COND)                                                          \
{                                                                   \
    printf("Test failure: "#COND" is not true");                    \
    testStatus = false;                                             \
    return 0;                                                       \
}

#define CRASH_TEST(REASON)                                          \
printf("Test failure: %s\n", REASON);                               \
testStatus = false;                                                 \
return 0;                                              

#define ASSERT_EQUAL(VAR1, VAR2)                                    \
if (VAR1 != VAR2)                                                   \
{                                                                   \
    printf("Variables should be equal,"                             \
           "but they are not\n"                                     \
           #VAR1": ");                                              \
    std::cout << VAR1 << "\n";                                      \
    printf(#VAR2": ");                                              \
    std::cout << VAR2 << "\n";                                      \
    testStatus = false;                                             \
    return 0;                                                       \
}

#define ASSERT_CLOSE(VAR1, VAR2)                                    \
if (fabs(VAR1 - VAR2) > 1e-5)                                       \
{                                                                   \
    printf("Variables should be close,"                             \
           "but they are not\n"                                     \
           #VAR1": ");                                              \
    std::cout << VAR1 << "\n";                                      \
    printf(#VAR2": ");                                              \
    std::cout << VAR2 << "\n";                                      \
    testStatus = false;                                             \
    return 0;                                                       \
}

#define CODE_CAUSES_ASSERTION(CODE)                                 \
auto previousHandler = std::signal(SIGABRT, abortIndicatorHandler); \
if (previousHandler == SIG_ERR)                                     \
{                                                                   \
    printf("Handler of abort remained standart\n");                 \
}                                                                   \
                                                                    \
__TEST_ABORT_FLAG__ = false;                                        \
{  CODE  }                                                          \
                                                                    \
returnedHandler = std::signal(SIGABRT, previousHandler);            \
if (returnedHandler == SIG_ERR)                                     \
{                                                                   \
    printf("Unable to return old handler\n");                       \
    abort();                                                        \
}                                                                   \
                                                                    \
if (!__TEST_ABORT_FLAG__)                                           \
{                                                                   \
    testStatus = false;                                             \
    printf("Test failure: error is not handled\n");                 \
    return 0;                                                       \
}                                                                   

#define RUN_TEST(NAME) RLTest_##NAME()

