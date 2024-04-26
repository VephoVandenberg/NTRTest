struct CircularBuffer 
{
    char *buffer;
    int capacity;
    int front;
    int rear;
    int count;

    CircularBuffer(int size) 
    {
        capacity = size;
        buffer = new char[capacity];
        front = 0;
        rear = 0;
        count = 0;
    }

    ~CircularBuffer() 
    {
        delete[] buffer;
    }

    void write(const char *data, int length) 
    {
        for (int i = 0; i < length; ++i) 
        {
            buffer[rear] = data[i];
            rear = (rear + 1) % capacity;
            if (count == capacity) 
            {
                front = (front + 1) % capacity;
            } 
            else 
            {
                ++count;
            }
        }
    }

    int read(char *data, int length) 
    {
        int bytesRead = 0;
        while (bytesRead < length && count > 0) 
        {
            data[bytesRead] = buffer[front];
            front = (front + 1) % capacity;
            ++bytesRead;
            --count;
        }
        return bytesRead;
    }
};
