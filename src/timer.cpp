#include <oak/timer.hpp>
#include <cstdio>
#include <glad/glad.h>
namespace oak {
    Timer::Timer(std::string& name) : mStart(Clock::now()), mName(name) {}

    Timer::~Timer() {
        TimePoint end = Clock::now();
        Duration dur = end - mStart;
        printf("Timer %s: %ld us\n", mName.c_str(), std::chrono::duration_cast<std::chrono::microseconds>(dur).count());
    }


    GPUTimer::GPUTimer() : mStartID(0), mEndID(0) {
        glGenQueries(1, &mStartID);
        glGenQueries(1, &mEndID);
    }

    void GPUTimer::start() {
        glQueryCounter(mStartID, GL_TIMESTAMP);
        
    }

    void GPUTimer::end() {
        glQueryCounter(mEndID, GL_TIMESTAMP);
    }

    bool GPUTimer::isAvailable() {
        i32 status = 0;
        glGetQueryObjectiv(mEndID, GL_QUERY_RESULT_AVAILABLE, &status);
        return status == GL_TRUE;
    }

    u64 GPUTimer::durationNS() {
        if (!isAvailable()) return 0;
        u64 startTime, endTime;
        glGetQueryObjectui64v(mStartID, GL_QUERY_RESULT, &startTime);
        glGetQueryObjectui64v(mEndID, GL_QUERY_RESULT, &endTime);
        return endTime - startTime;
    }

    GPUTimer::~GPUTimer() {
        glDeleteQueries(1, &mStartID);
        glDeleteQueries(1, &mEndID);
    }
}