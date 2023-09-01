/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>

class Periodic {
public:
    explicit Periodic(
        const std::chrono::milliseconds &period,
        const std::function<void ()> &func
    )
        : m_period(period)
        , m_func(func)
        , m_inFlight(true)
    {
        std::cout << "Constructing periodic" << std::endl;
        m_thread = std::thread([this] {
            while (m_inFlight) {
                std::this_thread::sleep_for(m_period);
                if (m_inFlight) {
                    m_func();
                }
            }
        });
    }

    ~Periodic() {
        std::cout << "Destructed periodic" << std::endl;
        m_inFlight = false;
        m_thread.join();
        std::cout << "Destructed periodic" << std::endl;
    }

private:
    std::chrono::milliseconds m_period;
    std::function<void ()> m_func;
    std::atomic<bool> m_inFlight;
    std::thread m_thread;
};

void
test ()
{
  std::cout << "Testing thread id: " << std::this_thread::get_id() << std::endl;
}

int
main ()
{

  std::cout << "Starting: " << std::this_thread::get_id() << std::endl;
  Periodic T( std::chrono::seconds(1), test );
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::cout << "Finished: " << std::this_thread::get_id() << std::endl;

  return 0;
}
