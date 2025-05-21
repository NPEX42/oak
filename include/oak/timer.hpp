#ifndef OAK_TIMER_H
#define OAK_TIMER_H 

#include <chrono>
#include <string>
#include <memory>

#include <oak/types.h>

namespace oak {

    using Clock = std::chrono::system_clock;
    using Duration = Clock::duration;

    using TimePoint = Clock::time_point;

    class Timer {
        public:
            Timer(std::string& name);
            ~Timer();

            static std::unique_ptr<Timer> Create(std::string name) { return std::make_unique<Timer>(name); };
        private:
            TimePoint mStart;
            std::string mName;
    };


    class GPUTimer {
        public:
            GPUTimer();
            ~GPUTimer();

            static std::unique_ptr<GPUTimer> Create() { return std::make_unique<GPUTimer>(); };

            void start();
            void end();

            bool isAvailable();

            u64 durationNS();

        private:
            u32 mStartID, mEndID;
            std::string mName;
    };
}
#endif // OAK_TIMER_H