


#include <sys/socket.h>

#include <sys/stat.h>

#include <arpa/inet.h>

#include <stdio.h>

#include <string.h>

#include <unistd.h>

#include <termios.h>

#include <wiringPi.h>

#include <softTone.h>

#include <errno.h>

#include <pthread.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <fcntl.h>

#include <errno.h>

#include <stdlib.h>




#define PORT    8081            //10000�����İ� ����

#define MAXBUF    20                /* Ŭ���̾�Ʈ�� ���̸� ���߾��ش�. */







#define START    0

#define NIGHT    1

#define LEFT        2

#define EXIT        6




#define    CDS    0    /* GPIO17 */    




#define    SPKR    6    /* GPIO25 */




#define LED_do    29     /*GPIO21*/

#define LED_rae    28     /*GPIO20*/

#define LED_me    27     /*GPIO16*/

#define LED_pa    26     /*GPIO12*/

#define LED_sol    31     /*GPIO-*/

#define LED_ra    11     /*GPIO7*/

#define LED_ti    10     /*GPIO8*/

#define LED_Do    1     /*GPIO18*/




#define SW_do    25     /*GPIO26*/

#define SW_rae    24     /*GPIO19*/

#define SW_me    23     /*GPIO13*/

#define SW_pa    22     /*GPIO6*/

#define SW_sol    21     /*GPIO5*/

#define SW_ra    2     /*GPIO13*/

#define SW_ti    3     /*GPIO3*/

#define SW_Do    12     /*GPIO10*/







char state[100];










int gpiopins[4] = {4, 26, 16, 15};     /* D, C, B, A : 23 12 15 14 */        // FND ����� ���� �� ����

int number[10][4] = { {0,0,0,0},      /* 0 */                        // FND ��ȣ ����� ���� �迭

    {0,0,0,1},      /* 1 */

    {0,0,1,0},      /* 2 */

    {0,0,1,1},      /* 3 */

    {0,1,0,0},      /* 4 */

    {0,1,0,1},      /* 5 */

    {0,1,1,0},      /* 6 */

    {0,1,1,1},      /* 7 */

    {1,0,0,0},      /* 8 */

    {1,0,0,1} };    /* 9 */




#define TOTAL    47    /* �б����� ��ü ���̸��� �� */




int notes[] = {        /* �б����� �����ϱ� ���� ���̸� */

146.83, 195, 233.08, 293.66, 293.66, 293.66, 261.63, 233.08, 220, 233.08, 233.08, 0, \

195, 233.08, 293.66, 391, 391, 391, 440, 349.22, 311.12, 349.22, 349.22, 0, \

220, 293.66, 349.22, 440, 440, 391, 349.22, 329.63, 349.22, 391, 391, 349.22, \

329.63, 329.63, 293.66, 261.63, 233.08, 261.63, 293.66, 261.63, 195, 220, 0

};




pthread_mutex_t music_lock;

pthread_mutex_t cds_lock;

pthread_mutex_t switch_lock;




static int is_run = 1; /* ������ ���Ḧ ���� �÷��� */




void *cdsfunction(void *arg)

{

    int i;




    pinMode(CDS, INPUT);             /* ���� ��带 �Է����� ���� */

  for (i = 0; ; i++) {

        if(digitalRead(CDS) == LOW) {     /* ���� ������(LOW) */

             musicPlay();

                delay(100);

        break;

        }

    };

    return 0;

}




void *switchfunction(void *arg)

{

    int i;




    pthread_t ptSwitch,ptMusic, ptMusic_do, ptMusic_rae, ptMusic_me, ptMusic_pa, ptMusic_sol, ptMusic_ra, ptMusic_ti, ptMusic_Do;

    pthread_mutex_init(&music_lock, NULL); /* ���ؽ� �ʱ�ȭ */




    pthread_mutex_init(&switch_lock, NULL); /* ���ؽ� �ʱ�ȭ */




    wiringPiSetup();

    

    pinMode(SW_do, INPUT);             /* ���� ��带 �Է����� ���� */

    pinMode(LED_do, OUTPUT);




    pinMode(SW_rae, INPUT);             /* ���� ��带 �Է����� ���� */

    pinMode(LED_rae, OUTPUT);




    pinMode(SW_me, INPUT);             /* ���� ��带 �Է����� ���� */

    pinMode(LED_me, OUTPUT); 




    pinMode(SW_pa, INPUT);             /* ���� ��带 �Է����� ���� */

    pinMode(LED_pa, OUTPUT); 




    pinMode(SW_sol, INPUT);             /* ���� ��带 �Է����� ���� */

    pinMode(LED_sol, OUTPUT); 




    pinMode(SW_ra, INPUT);             /* ���� ��带 �Է����� ���� */

    pinMode(LED_ra, OUTPUT); 




    pinMode(SW_ti, INPUT);             /* ���� ��带 �Է����� ���� */

    pinMode(LED_ti, OUTPUT); 




    pinMode(SW_Do, INPUT);             /* ���� ��带 �Է����� ���� */

    pinMode(LED_Do, OUTPUT);




 for (is_run;;) {                // ���� ����

        if(digitalRead(SW_do) == LOW) {     /* Push ��ư�� ��������(LOW) */

            digitalWrite(LED_do, HIGH);         /* LED �ѱ�(On) */

        sprintf(state,"%s\n", "1");

        //pthread_create(&ptMusic_do, NULL, musicfunction_do, NULL);

        musicPlay_do();

        delay(500);

        digitalWrite(LED_do, LOW);         /* LED ����(Off) */

        break;                        // �ѹ� ����ġ �۵��ϸ� ����

    }




  if(digitalRead(SW_rae) == LOW) {     /* Push ��ư�� ��������(LOW) */

            digitalWrite(LED_rae, HIGH);         /* LED �ѱ�(On) */

        sprintf(state,"%s\n", "2");

        //pthread_create(&ptMusic_rae, NULL, musicfunction_rae, NULL);

        musicPlay_rae();

        delay(500);

        digitalWrite(LED_rae, LOW);         /* LED ����(Off) */

        break;                        // �ѹ� ����ġ �۵��ϸ� ����

    }




 if(digitalRead(SW_me) == LOW) {     /* Push ��ư�� ��������(LOW) */

            digitalWrite(LED_me, HIGH);         /* LED �ѱ�(On) */

        sprintf(state,"%s\n", "3");

        //pthread_create(&ptMusic_me, NULL, musicfunction_me, NULL);

        musicPlay_me();

        delay(500);

        digitalWrite(LED_me, LOW);         /* LED ����(Off) */

        break;                        // �ѹ� ����ġ �۵��ϸ� ����

    }




 if(digitalRead(SW_pa) == LOW) {     /* Push ��ư�� ��������(LOW) */

            digitalWrite(LED_pa, HIGH);         /* LED �ѱ�(On) */

        sprintf(state,"%s\n", "4");

        //pthread_create(&ptMusic_pa, NULL, musicfunction_pa, NULL);

        musicPlay_pa();

        delay(500);

        digitalWrite(LED_pa, LOW);         /* LED ����(Off) */

        break;                        // �ѹ� ����ġ �۵��ϸ� ����

    }




 if(digitalRead(SW_sol) == LOW) {     /* Push ��ư�� ��������(LOW) */

            digitalWrite(LED_sol, HIGH);         /* LED �ѱ�(On) */

        sprintf(state,"%s\n", "5");

        //pthread_create(&ptMusic_sol, NULL, musicfunction_sol, NULL);

        musicPlay_sol();

        delay(500);

        digitalWrite(LED_sol, LOW);         /* LED ����(Off) */

        break;                        // �ѹ� ����ġ �۵��ϸ� ����

    }




 if(digitalRead(SW_ra) == LOW) {     /* Push ��ư�� ��������(LOW) */

            digitalWrite(LED_ra, HIGH);         /* LED �ѱ�(On) */

        sprintf(state,"%s\n", "6");

        //pthread_create(&ptMusic_ra, NULL, musicfunction_ra, NULL);

        musicPlay_ra();

        delay(500);

        digitalWrite(LED_ra, LOW);         /* LED ����(Off) */

        break;                        // �ѹ� ����ġ �۵��ϸ� ����

    }




 if(digitalRead(SW_ti) == LOW) {     /* Push ��ư�� ��������(LOW) */

            digitalWrite(LED_ti, HIGH);         /* LED �ѱ�(On) */

        sprintf(state,"%s\n", "7");

       //pthread_create(&ptMusic_ti, NULL, musicfunction_ti, NULL);

        musicPlay_ti();

        delay(500);

        digitalWrite(LED_ti, LOW);         /* LED ����(Off) */

        break;                        // �ѹ� ����ġ �۵��ϸ� ����

    }




 if(digitalRead(SW_Do) == LOW) {     /* Push ��ư�� ��������(LOW) */

            digitalWrite(LED_Do, HIGH);         /* LED �ѱ�(On) */

        sprintf(state,"%s\n", "8");

        //pthread_create(&ptMusic_Do, NULL, musicfunction_Do, NULL);

        musicPlay_Do();

        delay(500);

        digitalWrite(LED_Do, LOW);         /* LED ����(Off) */

        break;                        // �ѹ� ����ġ �۵��ϸ� ����

    }

    };




    return 0;

} 










int musicPlay_do()

{

    int i ;

    if(pthread_mutex_trylock(&music_lock) != EBUSY) { /* �Ӱ� ���� ���� */

        softToneCreate(SPKR) ;             /* �� ����� ���� GPIO ���� */

            //for (i = 0; i < 1; ++i) {

                softToneWrite(SPKR, 261.63);         /* �� ��� : �б��� ���� */

                delay(300);                 /* ���� ��ü ���̸�ŭ ��µǵ��� ��� */

            //}

    softToneWrite(SPKR, 0);

    pthread_mutex_unlock(&music_lock); /* �Ӱ� ���� ���� */

        }

    return 0;

}










int musicPlay_rae()

{

    int i ;

    if(pthread_mutex_trylock(&music_lock) != EBUSY) { /* �Ӱ� ���� ���� */

        softToneCreate(SPKR) ;             /* �� ����� ���� GPIO ���� */

            //for (i = 0; i < 1; ++i) {

                softToneWrite(SPKR, 293.66);         /* �� ��� : �б��� ���� */

                delay(300);                 /* ���� ��ü ���̸�ŭ ��µǵ��� ��� */

            //}

    softToneWrite(SPKR, 0);

        pthread_mutex_unlock(&music_lock); /* �Ӱ� ���� ���� */

        }

    return 0;

}













int musicPlay_me()

{

    int i ;

    if(pthread_mutex_trylock(&music_lock) != EBUSY) { /* �Ӱ� ���� ���� */

        softToneCreate(SPKR) ;             /* �� ����� ���� GPIO ���� */

            //for (i = 0; i < 1; ++i) {

                softToneWrite(SPKR, 329.63);         /* �� ��� : �б��� ���� */

                delay(300);                 /* ���� ��ü ���̸�ŭ ��µǵ��� ��� */

            //}

    softToneWrite(SPKR, 0);

        pthread_mutex_unlock(&music_lock); /* �Ӱ� ���� ���� */

        }

    return 0;

}







int musicPlay_pa()

{

    int i ;

    if(pthread_mutex_trylock(&music_lock) != EBUSY) { /* �Ӱ� ���� ���� */

        softToneCreate(SPKR) ;             /* �� ����� ���� GPIO ���� */

            //for (i = 0; i < 1; ++i) {

                softToneWrite(SPKR,  349.22);         /* �� ��� : �б��� ���� */

                delay(300);                 /* ���� ��ü ���̸�ŭ ��µǵ��� ��� */

            //}

    softToneWrite(SPKR, 0);

        pthread_mutex_unlock(&music_lock); /* �Ӱ� ���� ���� */

        }

    return 0;

}













int musicPlay_sol()

{

    int i ;

    if(pthread_mutex_trylock(&music_lock) != EBUSY) { /* �Ӱ� ���� ���� */

        softToneCreate(SPKR) ;             /* �� ����� ���� GPIO ���� */

            //for (i = 0; i < 1; ++i) {

                softToneWrite(SPKR,  391);         /* �� ��� : �б��� ���� */

                delay(300);                 /* ���� ��ü ���̸�ŭ ��µǵ��� ��� */

            //}

    softToneWrite(SPKR, 0);

        pthread_mutex_unlock(&music_lock); /* �Ӱ� ���� ���� */

        }

    return 0;

}







int musicPlay_ra()

{

    int i ;

    if(pthread_mutex_trylock(&music_lock) != EBUSY) { /* �Ӱ� ���� ���� */

        softToneCreate(SPKR) ;             /* �� ����� ���� GPIO ���� */

            //for (i = 0; i < 1; ++i) {

                softToneWrite(SPKR,  440);         /* �� ��� : �б��� ���� */

                delay(300);                 /* ���� ��ü ���̸�ŭ ��µǵ��� ��� */

            //}

    softToneWrite(SPKR, 0);

        pthread_mutex_unlock(&music_lock); /* �Ӱ� ���� ���� */

        }

    return 0;

}













int musicPlay_ti()

{

    int i ;

    if(pthread_mutex_trylock(&music_lock) != EBUSY) { /* �Ӱ� ���� ���� */

        softToneCreate(SPKR) ;             /* �� ����� ���� GPIO ���� */

            //for (i = 0; i < 1; ++i) {

                softToneWrite(SPKR,  493.88);         /* �� ��� : �б��� ���� */

                delay(300);                 /* ���� ��ü ���̸�ŭ ��µǵ��� ��� */

            //}

    softToneWrite(SPKR, 0);

        pthread_mutex_unlock(&music_lock); /* �Ӱ� ���� ���� */

        }

    return 0;

}




int musicPlay_Do()

{

    int i ;

    if(pthread_mutex_trylock(&music_lock) != EBUSY) { /* �Ӱ� ���� ���� */

        softToneCreate(SPKR) ;             /* �� ����� ���� GPIO ���� */

            //for (i = 0; i < 1; ++i) {

                softToneWrite(SPKR,  523.25);         /* �� ��� : �б��� ���� */

                delay(300);                 /* ���� ��ü ���̸�ŭ ��µǵ��� ��� */

            //}

    softToneWrite(SPKR, 0);

        pthread_mutex_unlock(&music_lock); /* �Ӱ� ���� ���� */

        }

    return 0;

}




void *musicfunction(void *arg)

{

    if(pthread_mutex_trylock(&music_lock) != EBUSY) { /* �Ӱ� ���� ���� */

        musicPlay();

        pthread_mutex_unlock(&music_lock); /* �Ӱ� ���� ���� */

    }




    return NULL;

}




int musicPlay()

{

    int i ;

    softToneCreate(SPKR) ;             /* �� ����� ���� GPIO ���� */

    for (i = 0; i < TOTAL; ++i) {

        softToneWrite(SPKR, notes[i]);         /* �� ��� : �б��� ���� */

      delay(300);                 /* ���� ��ü ���̸�ŭ ��µǵ��� ��� */

    digitalWrite(LED_do, HIGH);        

    delay(10);

    digitalWrite(LED_rae, HIGH);         

    delay(10);

    digitalWrite(LED_me, HIGH); 

    delay(10);

    digitalWrite(LED_pa, HIGH);

    delay(10);

    digitalWrite(LED_sol, HIGH);     

    delay(10);

    digitalWrite(LED_ra, HIGH);         

    delay(10);

    digitalWrite(LED_ti, HIGH); 

    delay(10);

    digitalWrite(LED_Do, HIGH); 

    delay(200);

    digitalWrite(LED_Do, LOW);

    digitalWrite(LED_ra, LOW); 

    digitalWrite(LED_me, LOW); 

    digitalWrite(LED_do, LOW); 

    digitalWrite(LED_pa, LOW);

    digitalWrite(LED_sol, LOW); 

    digitalWrite(LED_ti, LOW);

    digitalWrite(LED_rae, LOW); 

        //delay(500);         

    //������� ��

    if(digitalRead(CDS)==HIGH){    

     softToneWrite(SPKR, 0);

    state[100]=0;

    break;

    }     

    }




    return 0;

}

int kbhit()

{

    struct termios oldt, newt;             /* �͹̳ο� ���� ����ü */

    int ch, oldf;




    tcgetattr(0, &oldt);             /* ���� �͹̳ο� ������ ������ �����´�. */

    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);         /* ���� ��� �Է°� ���ڸ� �����Ѵ�. */

    tcsetattr(0, TCSANOW, &newt);         /* ���� ������ �͹̳��� �����Ѵ�. */

    oldf = fcntl(0, F_GETFL, 0);

    fcntl(0, F_SETFL, oldf | O_NONBLOCK);     /* �Է��� ����ŷ ���� �����Ѵ�. */




    ch = getchar();




    tcsetattr(0, TCSANOW, &oldt);         /* ������ ������ �͹̳��� �Ӽ��� �ٷ� �����Ѵ�. */

    fcntl(0, F_SETFL, oldf);

    if(ch != EOF) {

        ungetc(ch, stdin);             /* �տ��� ���� ��ġ�� �������� �����͸� �����ش�. */

        return 1;

    }




    return 0;

}




int main(int argc, char **argv) {

    int server_sockfd, client_sockfd;     // ����

    int choice;

    char buf[MAXBUF];

    char dummy[MAXBUF];

    struct sockaddr_in serveraddr, clientaddr;  // ������ Ŭ���̾�Ʈ�� ���� ����

    int client_len;                        // Ŭ���̾�Ʈ ������ ����Ʈ ũ��

    int chk_bind;                     // ���� Ȯ�� ����

    int read_len;




    int i = 0;




    pthread_t ptSwitch, ptCds, ptMusic, ptLed, ptDisp;

    pthread_mutex_init(&music_lock, NULL); /* ���ؽ� �ʱ�ȭ */

    pthread_mutex_init(&switch_lock, NULL); /* ���ؽ� �ʱ�ȭ */

    pthread_mutex_init(&cds_lock, NULL); /* ���ؽ� �ʱ�ȭ */

    wiringPiSetup();




    client_len = sizeof(clientaddr);




    /* ���� socket() ����  */

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(server_sockfd == -1) {

        perror("socket error : ");

        exit(0);

    }

    /* bind() */

    bzero(&serveraddr, sizeof(serveraddr));     // �ش� �޸� ���� �ʱ�ȭ

    serveraddr.sin_family = AF_INET;

    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    serveraddr.sin_port = htons(PORT);        // ��Ʈ ��ȣ ����

    chk_bind = bind(server_sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));    //���Ϲ�ȣ�� ����ü�� ����

    if(chk_bind > 0) {

        perror("bind error : ");

        exit(0);

    }




    /* listen() */

    if(listen(server_sockfd, 5)) {    //5�� MAX����, 5���� Ŭ���̾�Ʈ

        perror("listen error : ");

    }




    /* Ŭ���̾�Ʈ ���� ��� */

    /* accept() */

    client_sockfd = accept(server_sockfd, (struct sockaddr *)&clientaddr, &client_len);    //Ŭ���̾�Ʈ ������

    printf("New Client Connect: %s\n", inet_ntoa(clientaddr.sin_addr));    //Ŭ���ξ�Ʈ ����Ǹ� ���� : �����ʿ� �����

    sprintf(state,"%s\n", "0");

    while(1) {




           state[100]=0;

        //sprintf(swstate,"%s\n", "1");

        if(write(client_sockfd , state, MAXBUF) <= 0) {

            perror("write( )");

            return -1; 

        }

        

        memset(buf, 0x00, MAXBUF);

        read_len = read(client_sockfd, buf, MAXBUF);            //������ ũ��(80)��ŭ ����

        

        choice =atoi(buf);




        if  (digitalRead(CDS)==LOW)

        {    

            sprintf(state,"%s\n", "9");

            printf ("CDS = %d\n", choice);

            //pthread_create(&ptMusic, NULL, musicfunction, NULL);

            musicPlay();

            delay(600);

            state[100]=0;

        } 




        




        switch(choice) {

            case START:    //0

                printf ("SW = %d\n", choice);

                //switchfunction(&ptSwitch);

                pthread_create(&ptSwitch, NULL, switchfunction, NULL);

                break;

                

            case EXIT :    //6

                printf ("END = %d\n", choice);

                  close(client_sockfd);

                close(server_sockfd);

                is_run=0;

                




        

        }//switch




    }//while

    is_run = 0;







    pthread_join(ptSwitch, NULL); /* ������ ��� */    

    pthread_join(ptMusic, NULL); /* ������ ��� */

    pthread_join(ptCds, NULL);




    pthread_mutex_destroy(&music_lock); /* ���ؽ� ���� */  

    pthread_mutex_destroy(&switch_lock); 

    pthread_mutex_destroy(&cds_lock); 

                    return 0;

}