#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY 0x1234

int main() {
    int shmid;
    char *shared_memory;

    // Locate the shared memory segment
    shmid = shmget(SHM_KEY, 1024, 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach to the shared memory segment
    shared_memory = (char *)shmat(shmid, NULL, 0);
    if (shared_memory == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    // Read from the shared memory
    printf("Reader: Data read from shared memory: %s\n", shared_memory);

    // Detach from the shared memory segment
    shmdt(shared_memory);

    // Destroy the shared memory segment
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}

