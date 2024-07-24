#include <mutex>
#include <thread>
#include <condition_variable>
#include <iostream>
#include <list>

template<typename T>
class SyncQueue
{
    bool isFull() const
    {
        return m_queue.size() == m_maxSize;
    }
    bool isEmpty() const
    {
        return m_queue.empty();
    }
public:
    SyncQueue(int maxSize) : m_maxSize(maxSize)
    {
    }

    void Put(const T& x)
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        while (isFull())
        {
            std::cout << "缓冲区已经满了，需要等待..." << std::endl;
            m_notFull.wait(m_mutex);
        }
        m_queue.push_back(x);
        m_notEmpty.notify_one();
    }

    void Task2(T& x)
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        m_notEmpty.wait(locker, [this] {return !isFull(); }); // 也能支持lambda表达式来处理等待事件；
        x = m_queue.front();
        m_queue.pop_front();
        m_notFull.notify_one();
    }
    void Take(T& x)
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        while (isEmpty())
        {
            std::cout << "缓冲区已空了，需要等待..." << std::endl;
            m_notEmpty.wait(m_mutex);
        }
        x = m_queue.front();
        m_queue.pop_front();
        m_notFull.notify_one();
    }

    bool Empty()
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        return m_queue.empty();
    }
    bool Full()
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        return m_queue.size() == m_maxSize;
    }
    std::size_t Size()
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        return m_queue.size();
    }

    int Count()
    {
        return m_queue.size();
    }
private:
    std::list<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable_any m_notEmpty;
    std::condition_variable_any m_notFull;
    int m_maxSize;
};

template<typename T>
class SimpleSyncQueue
{
    bool isFull() const
    {
        return m_queue.size() == m_maxSize;
    }
    bool isEmpty() const
    {
        return m_queue.empty();
    }
public:
    SimpleSyncQueue() 
    {
    }
    void Put(const T& x)
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        while (isFull())
        {
            std::cout << "缓冲区已经满了，需要等待..." << std::endl;
            m_notFull.wait(m_mutex);
        }
        m_queue.push_back(x);
        m_notEmpty.notify_one();
    }

    void Take(T& x)
    {
        std::unique_lock<std::mutex> locker(m_mutex);
        m_notEmpty.wait(locker, [this] {return !m_queue.empty(); }); // 也能支持lambda表达式来处理等待事件；
        x = m_queue.front();
        m_queue.pop_front();
    }

    bool Empty()
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        return m_queue.empty();
    }
    bool Full()
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        return m_queue.size() == m_maxSize;
    }
    std::size_t Size()
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        return m_queue.size();
    }

private:
    std::list<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_notEmpty;
    std::condition_variable_any m_notFull;
    int m_maxSize;
};

int main(int argn,char* argc[])
{
    return 0;
}
