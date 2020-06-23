#include <chrono>

#include <cstdio>
#include <cmath>
#include <cerrno>
#include <cstring>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


int main(int argc, const char * argv[]) {

    int fd = -1;
    // write to file or stdout
    if (argc >= 2) {
        fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC);
        if (fd < 0) {
            perror("Failed to open file");
            return EXIT_FAILURE;
        }
    } else {
        fd = STDOUT_FILENO;
    }
    // nonblocking
#if 0
    int ret = fcntl(fd, F_GETFL, 0);
    if (ret < 0) {
        perror("Failed to get file flags");            
        return EXIT_FAILURE;
    }
    ret = fcntl(fd, F_SETFL, ret | O_NONBLOCK);
    if (ret < 0) {
        perror("Failed to set non blocking");            
        return EXIT_FAILURE;
    }
#endif
    // buffer to write
    size_t buffer_size = 1024; // 1 MiB
    uint8_t * buffer = new uint8_t[buffer_size];
    memset(buffer, 0xab, buffer_size);
    // statistics counters
    uint64_t  writes = 1000'000;
    uint64_t  errors = 0;
    uint64_t  blocks = 0;
    double sum  = 0;
    double sqsum  = 0;
    // run job
    auto start = std::chrono::system_clock::now();    
    for (uint64_t i = 0; i < writes; ++i) {
        ssize_t outbytes = write(fd, buffer, buffer_size);
        if (outbytes < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                ++blocks;
            } else {
                ++errors;
            }
        } else {
            sum += outbytes;
            sqsum += (outbytes*outbytes);
        }
    }
    auto end = std::chrono::system_clock::now();
    // calculate stats
    uint64_t actual_writes = writes - (errors + blocks);
    double mean = sum / actual_writes;
    double sd = sqrt((sqsum / actual_writes) - (mean * mean));
    std::chrono::duration<double, std::chrono::seconds::period> timediff = end - start;
    double througput = ((sum / timediff.count()) * 8) / (1000 * 1000 * 1000);
    // print stats
    fprintf(stderr, "througput_Gbps=%f mean=%f sd=%f errors=%lu blocks=%lu time_sec=%f\n", 
            througput, mean, sd, errors, blocks, timediff.count());
    // try cleanup
    if (argc >= 2) {
        delete[] buffer;
        close(fd);
        unlink(argv[1]);
    }
    return EXIT_SUCCESS;
}
