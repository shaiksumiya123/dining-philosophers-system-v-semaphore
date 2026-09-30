#include"header.h"

int main()
{
        int id=semget(4,5,IPC_CREAT|0664);

        semctl(id,0,SETVAL,1);
        semctl(id,1,SETVAL,1);
        semctl(id,2,SETVAL,1);
        semctl(id,3,SETVAL,1);
        semctl(id,4,SETVAL,1);

        struct sembuf v;

        printf("fork1 is available..\n");
        printf("fork2 is available..\n");
        printf("fork3 is available..\n");
        printf("fork4 is available..\n");
        printf("fork5 is available..\n");

        if(fork()==0)
        {
                printf("philosopher 1 is waiting..\n");

                v.sem_num=0;
                v.sem_op=-1;
                v.sem_flg=0;
                semop(id,&v,1);

                v.sem_num=4;
                v.sem_op=-1;
                v.sem_flg=0;
                semop(id,&v,1);

                printf("philosopher 1 is using fork1 and fork5...\n");

                sleep(3);

                v.sem_num=0;
                v.sem_op=1;
                v.sem_flg=0;
                semop(id,&v,1);

                v.sem_num=4;
                v.sem_op=1;
                v.sem_flg=0;
                semop(id,&v,1);

                printf("philosopher 1 released fork1 and fork5..\n");
                printf("philosopher 1 done..\n");
        }
        else
        {
                if(fork()==0)
                {
                        printf("philosopher 2 is waiting...\n");

                        v.sem_num=1;
                        v.sem_op=-1;
                        v.sem_flg=0;
                        semop(id,&v,1);

                        v.sem_num=0;
                        v.sem_op=-1;
                        v.sem_flg=0;
                        semop(id,&v,1);

                        printf("philosopher 2 is using fork 2 and fork 1...\n");

                        sleep(3);

                        v.sem_num=1;
                        v.sem_op=1;
                        v.sem_flg=0;
                        semop(id,&v,1);

                        v.sem_num=0;
                        v.sem_op=1;
                        v.sem_flg=0;
                        semop(id,&v,1);

                        printf("philosopher 2 release fork 2 and fork 1...\n");
                        printf("philosopher 2 done..\n");
                }
                else
                {
                        if(fork()==0)
                        {
                                printf("philosopher 3 is waiting...\n");

                                v.sem_num=1;
                                v.sem_op=-1;
                                v.sem_flg=0;
                                semop(id,&v,1);

                                v.sem_num=2;
                                v.sem_op=-1;
                                v.sem_flg=0;
                                semop(id,&v,1);

                                printf("philosopher 3 using fork 3 and fork 2...\n");

                                sleep(3);

                                v.sem_num=1;
                                v.sem_op=1;
                                v.sem_flg=0;
                                semop(id,&v,1);

                                v.sem_num=2;
                                v.sem_op=1;
                                v.sem_flg=0;
                                semop(id,&v,1);

                                printf("philosopher 3 released fork 3 and fork 2 ...\n");
                                printf("philosopher 3 done...\n");
                        }
                        else
                        {
                                if(fork()==0)
                                {
                                        printf("philosopher 4 is waiting...\n");

                                        v.sem_num=3;
                                        v.sem_op=-1;
                                        v.sem_flg=0;
                                        semop(id,&v,1);

                                        v.sem_num=2;
                                        v.sem_op=-1;
                                        v.sem_flg=0;
                                        semop(id,&v,1);

                                        printf("philosopher 4 using fork 4 and fork 3...\n");

                                        sleep(3);

                                        v.sem_num=2;
                                        v.sem_op=1;
                                        v.sem_flg=0;
                                        semop(id,&v,1);

                                        v.sem_num=3;
                                        v.sem_op=1;
                                        v.sem_flg=0;
                                        semop(id,&v,1);

                                        printf("philosopher 4 released fork 4 and fork 3 ...\n");
                                        printf("philosopher 4 done...\n");
                                }
                                else
                                {
                                        if(fork()==0)
                                        {
                                                printf("philosopher 5 is waiting...\n");

                                                v.sem_num=4;
                                                v.sem_op=-1;
                                                v.sem_flg=0;
                                                semop(id,&v,1);

                                                v.sem_num=3;
                                                v.sem_op=-1;
                                                v.sem_flg=0;
                                                semop(id,&v,1);

                                                printf("philosopher 5 using fork 4 and fork 5...\n");

                                                sleep(3);

                                                v.sem_num=4;
                                                v.sem_op=1;
                                                v.sem_flg=0;
                                                semop(id,&v,1);

                                                v.sem_num=3;
                                                v.sem_op=1;
                                                v.sem_flg=0;
                                                semop(id,&v,1);

                                                printf("philosopher 5 released fork 4 and fork 5 ...\n");
                                                printf("philosopher 5 done...\n");
                                        }
                                        else
                                        {
                                                printf("parent...\n");

                                                for(int i=0;i<5;i++)
                                                        wait(NULL);

                                                semctl(id,0,IPC_RMID);

                                                printf("all semaphores are deleted..\n");
                                        }
                                }
                        }
                }
        }
}
