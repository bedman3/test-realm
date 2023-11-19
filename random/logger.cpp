#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <sstream>
#include <thread>
#include <queue>
#include <cmath>


namespace Logger {
    enum class Level {
        TRACE,
        DEBUG,
        INFO,
        WARNING,
        SEVERE
    };

    class Logger {
        std::ofstream ofs_;
        void log(const char * log) { ofs_ << log << std::endl; }
        void logTime() {
            auto now = std::chrono::system_clock::now();
            time_t nowTt = std::chrono::system_clock::to_time_t(now);
            tm local_tm = *localtime(&nowTt);

            ofs_ << "[";
            ofs_ << local_tm.tm_year + 1900 << "/";
            ofs_ << std::setw(2) << std::setfill('0') << local_tm.tm_mon << "/";
            ofs_ << std::setw(2) << std::setfill('0') << local_tm.tm_mday << "-";
            ofs_ << std::setw(2) << std::setfill('0') << local_tm.tm_hour << ":";
            ofs_ << std::setw(2) << std::setfill('0') << local_tm.tm_min << ":";
            ofs_ << std::setw(2) << std::setfill('0') << local_tm.tm_sec << ".";
            ofs_ << std::setw(9) << std::setfill('0') << std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count() % (long long)10e9;
            ofs_ << "]";
        }
    public:
        Logger(const std::string& filepath ) : ofs_(filepath, std::ofstream::out) {}
        Logger(const Logger&) = delete;
        Logger(Logger&& logger) = delete;

        static void checkTime() {
            auto now = std::chrono::system_clock::now();
            time_t nowTt = std::chrono::system_clock::to_time_t(now);
            tm local_tm = *localtime(&nowTt);

            local_tm.tm_year + 1900;
            std::setw(2);
            std::setfill('0');
            std::setw(2);
            std::setfill('0');
            
            std::setw(2);
            std::setfill('0');
            std::setw(2);
            std::setfill('0');
            std::setw(2);
            std::setfill('0');
            std::setw(9);
            std::setfill('0');
            std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count() % (long long)10e9;
        }
        void trace(const char * log) { logTime(); ofs_ << "[-T-] "; this->log(log); }
        void debug(const char * log) { logTime(); ofs_ << "[-D-] "; this->log(log); }
        void info(const char * log) { logTime(); ofs_ << "[-I-] "; this->log(log); }
        void warn(const char * log) { logTime(); ofs_ << "[-W-] "; this->log(log); }
        void severe(const char * log) { logTime(); ofs_ << "[-S-] "; this->log(log); }  
    };

    template <class T>
    class CircularBuffer {
        T* buf_;
        int writePtr_;
        int readPtr_;
        int capacity_;
    public:
        void initialize() {
            writePtr_ = readPtr_ = 0;
        }
        CircularBuffer(unsigned int capacity) : buf_(new T[capacity]), capacity_(capacity) {
            initialize();
        }
        
        bool isFull() {
            return (readPtr_ + 1) % capacity_ == writePtr_;
        }
        bool isEmpty() {
            return readPtr_ == writePtr_;
        }
        ~CircularBuffer() {
            delete buf_;
        }
    };

    class ThreadSafeLogger {
        std::ofstream ofs_;
        bool isOfsWriting_;
        std::mutex mutex_;
        std::condition_variable cv_;
        // CircularBuffer<std::stringbuf> queue_;

        void logTime(std::stringbuf& buf) {
            auto now = std::chrono::system_clock::now();
            time_t nowTt = std::chrono::system_clock::to_time_t(now);
            tm local_tm = *localtime(&nowTt);

            buf.sputc('[');
            putLong(local_tm.tm_year + 1900, buf);
            buf.sputc('/');
            putLong(local_tm.tm_mon, 2, buf);
            buf.sputc('/');
            putLong(local_tm.tm_mday, 2, buf);
            buf.sputc('-');
            putLong(local_tm.tm_hour, 2, buf);
            buf.sputc(':');
            putLong(local_tm.tm_min, 2, buf);
            buf.sputc(':');
            putLong(local_tm.tm_sec, 2, buf);
            buf.sputc('.');
            putLong(std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count() % (long long)1e9, 9, buf);
            buf.sputc(']');
        }

    public:
        ThreadSafeLogger(const std::string& filepath) : ofs_(filepath, std::ofstream::out), isOfsWriting_(false) {}
        ThreadSafeLogger(const Logger&) = delete;
        ThreadSafeLogger(ThreadSafeLogger&& logger) = delete;

        static void putLong(long long num, std::stringbuf& buf) {
            putLong(num, num < 10 ? 1 : (long)ceil(log(num+1)/log(10)), buf);
        }
        static void putLong(long long num, size_t len, std::stringbuf& buf) {
            long long curr = num;
            len = len < 1 ? 1 : len;
            long long base = pow(10, len - 1);
            for (int i = len; i > 0; --i) {
                int curDigit = curr / base;
                curr %= base;
                base /= 10;
                buf.sputc('0' + curDigit);
            }
        }
        static void putString(const char * str, std::stringbuf& buf) {
            buf.sputn(str, strlen(str));
        }

        void info(const char * log, std::stringbuf& buf) { 
            logTime(buf);
            putString(" [-I-] ", buf);
            putString(log, buf);
            buf.sputc('\n');
            tryWriteToOfs(buf);
        }
        void tryWriteToOfs(const std::stringbuf& buf) {
            std::unique_lock<std::mutex> lock(mutex_);
            using namespace std::chrono_literals;

            if (cv_.wait_for(lock, 100ns, [this]{return !isOfsWriting_;})) {
                isOfsWriting_ = true;
                ofs_ << buf.str();
                isOfsWriting_ = false;
            } else {
                std::cerr << "Timeout waiting to write log: " << buf.str();
            };
            cv_.notify_one();
        }

        void consumerThread() {

        }
    };
}



int main() {
    std::string logPath("/Users/Martin/Projects/test-realm/random/logging.log");
    std::string logPath1("/Users/Martin/Projects/test-realm/random/logging1.log");
    std::shared_ptr<Logger::Logger> logger;
    std::shared_ptr<Logger::ThreadSafeLogger> logger1;
    logger = std::make_shared<Logger::Logger>(logPath);
    logger1 = std::make_shared<Logger::ThreadSafeLogger>(logPath1);

    // logger.trace("Hi Trace");
    // logger.debug("Hi Debug");
    // logger.info("Hi Info");
    // logger.warn("Hi Warn");
    // logger.severe("Hi Severe");

    long number = 0;
    long loopCount = 10e6;
    long thread = 10;
    std::stringstream ss;    



    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < loopCount; ++i)
    {   
        ss.str(std::string());
        ss.clear();
        ss << "This is " << i << " run";
        logger->info(ss.str().c_str());
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "time used: " << std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count() <<  "s " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << "ns" << std::endl; 
    
    t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < loopCount; ++i)
    {   
        ss.str(std::string());
        ss.clear();
        ss << "This is " << i << " run";
        logger->checkTime();
    }
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "time used: " << std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count() <<  "s " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << "ns" << std::endl; 

    t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < loopCount; ++i)
    {   
        ss.str(std::string());
        ss.clear();
        ss << "This is " << i << " run";
    }
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "time used: " << std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count() <<  "s " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << "ns" << std::endl; 

    std::vector<std::thread> threadVec;
    // std::thread loggerThread([logger1](){
    //     logger1->consumerThread();
    // });
    t1 = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < thread; ++j) {
        threadVec.emplace_back([logger1, loopCount, thread, j](){
            std::stringbuf buf, buf1;
            std::string emptyStr;
            long loop = loopCount / thread;
            long offset = loop * j;
            for (int i = 0; i < loop; ++i) {
                buf.str(std::string());
                buf1.str(std::string());
                Logger::ThreadSafeLogger::putString("This is ", buf1);
                Logger::ThreadSafeLogger::putLong(i + offset, buf1);
                Logger::ThreadSafeLogger::putString(" run", buf1);
                logger1->info(buf1.str().c_str(), buf);
            }
        });
    }
    for (int i = 0; i < thread; ++i) {
        threadVec[i].join();
    }
    // loggerThread.join();
    t2 = std::chrono::high_resolution_clock::now();
    std::cout << "time used: " << std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count() <<  "s " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << "ns" << std::endl; 


    return 0;
}