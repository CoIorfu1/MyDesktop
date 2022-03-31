#ifndef _PINGPONG_H_
#define _PINGPONG_H_

#include <atomic>
#include <memory>

class Buffer{
    public:
    Buffer(uint32_t bufSize);
    ~Buffer();
    // write data_p to WBuf
    void WriteBuffer(const void* data_p, uint32_t size);
    //read RBuf to des_p
    void ReadBuffer(void* des_p, uint32_t size);
    private:
    uint32_t BufferSize;
    uint8_t *Buf;
};

typedef struct{
    std::shared_ptr<Buffer> buffers_[2];
    std::atomic<int> read_index;
}PingPongBuffer_t;

std::shared_ptr<Buffer> PingPongBuffer_GetReadBuf(PingPongBuffer_t* ppbuf);
std::shared_ptr<Buffer> PingPongBuffer_GetWriteBuf(PingPongBuffer_t* ppbuf);
void PingPongBuffer_SetWriteDone(PingPongBuffer_t* ppbuf);


#endif // _PINGPONG_H
