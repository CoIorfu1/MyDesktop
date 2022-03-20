#include <cstring>
#include "PingPongBuffer.h"
    
std::shared_ptr<Buffer> PingPongBuffer_GetReadBuf(PingPongBuffer_t* ppbuf){
    return ppbuf->buffers_[ppbuf->read_index];
}

std::shared_ptr<Buffer> PingPongBuffer_GetWriteBuf(PingPongBuffer_t* ppbuf){
    int write_index = 1 - ppbuf->read_index;
    while(ppbuf->buffers_[write_index].use_count() > 1){
        continue;
    }
    return ppbuf->buffers_[write_index];
}

void PingPongBuffer_SetWriteDone(PingPongBuffer_t* ppbuf){
    ppbuf->read_index = 1 - ppbuf->read_index;
}

Buffer::Buffer(uint32_t bufSize) : BufferSize(bufSize){
    Buf = new uint8_t[BufferSize];
    memset(Buf, 0, BufferSize);
}

Buffer::~Buffer(){
    delete[] Buf;
}

void Buffer::WriteBuffer(const void* data_p, uint32_t size){
    memcpy(Buf, data_p, size);
}

void Buffer::ReadBuffer(void* des_p, uint32_t size){
    memcpy(des_p, Buf, size);
}