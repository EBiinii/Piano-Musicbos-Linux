


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




#define PORT    8081            //10000번이후가 좋음

#define MAXBUF    20                /* 클라이언트와 길이를 맞추어준다. */







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










int gpiopins[4] = {4, 26, 16, 15};     /* D, C, B, A : 23 12 15 14 */        // FND 출력을 위한 핀 설정

int number[10][4] = { {0,0,0,0},      /* 0 */                        // FND 번호 출력을 위한 배열

    {0,0,0,1},      /* 1 */

    {0,0,1,0},      /* 2 */

    {0,0,1,1},      /* 3 */

    {0,1,0,0},      /* 4 */

    {0,1,0,1},      /* 5 */

    {0,1,1,0},      /* 6 */

    {0,1,1,1},      /* 7 */

    {1,0,0,0},      /* 8 */

    {1,0,0,1} };    /* 9 */




#define TOTAL    47    /* 학교종의 전체 계이름의 수 */




int notes[] = {        /* 학교종을 연주하기 위한 계이름 */

146.83, 195, 233.08, 293.66, 293.66, 293.66, 261.63, 233.08, 220, 233.08, 233.08, 0, \

195, 233.08, 293.66, 391, 391, 391, 440, 349.22, 311.12, 349.22, 349.22, 0, \

220, 293.66, 349.22, 440, 440, 391, 349.22, 329.63, 349.22, 391, 391, 349.22, \

329.63, 329.63, 293.66, 261.63, 233.08, 261.63, 293.66, 261.63, 195, 220, 0

};




pthread_mutex_t music_lock;

pthread_mutex_t cds_lock;

pthread_mutex_t switch_lock;




static int is_run = 1; /* 스레드 종료를 위한 플래그 */




void *cdsfunction(void *arg)

{

    int i;




    pinMode(CDS, INPUT);             /* 핀의 모드를 입력으로 설정 */

  for (i = 0; ; i++) {

        if(digitalRead(CDS) == LOW) {     /* 빛이 없으면(LOW) */

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

    pthread_mutex_init(&music_lock, NULL); /* 뮤텍스 초기화 */




    pthread_mutex_init(&switch_lock, NULL); /* 뮤텍스 초기화 */




    wiringPiSetup();

    

    pinMode(SW_do, INPUT);             /* 핀의 모드를 입력으로 설정 */

    pinMode(LED_do, OUTPUT);




    pinMode(SW_rae, INPUT);             /* 핀의 모드를 입력으로 설정 */

    pinMode(LED_rae, OUTPUT);




    pinMode(SW_me, INPUT);             /* 핀의 모드를 입력으로 설정 */

    pinMode(LED_me, OUTPUT); 




    pinMode(SW_pa, INPUT);             /* 핀의 모드를 입력으로 설정 */

    pinMode(LED_pa, OUTPUT); 




    pinMode(SW_sol, INPUT);             /* 핀의 모드를 입력으로 설정 */

    pinMode(LED_sol, OUTPUT); 




    pinMode(SW_ra, INPUT);             /* 핀의 모드를 입력으로 설정 */

    pinMode(LED_ra, OUTPUT); 




    pinMode(SW_ti, INPUT);             /* 핀의 모드를 입력으로 설정 */

    pinMode(LED_ti, OUTPUT); 




    pinMode(SW_Do, INPUT);             /* 핀의 모드를 입력으로 설정 */

    pinMode(LED_Do, OUTPUT);




 for (is_run;;) {                // 무한 루프

        if(digitalRead(SW_do) == LOW) {     /* Push 버튼이 눌러지면(LOW) */

            digitalWrite(LED_do, HIGH);         /* LED 켜기(On) */

        sprintf(state,"%s\n", "1");

        //pthread_create(&ptMusic_do, NULL, musicfunction_do, NULL);

        musicPlay_do();

        delay(500);

        digitalWrite(LED_do, LOW);         /* LED 끄기(Off) */

        break;                        // 한번 스위치 작동하면 끝냄

    }




  if(digitalRead(SW_rae) == LOW) {     /* Push 버튼이 눌러지면(LOW) */

            digitalWrite(LED_rae, HIGH);         /* LED 켜기(On) */

        sprintf(state,"%s\n", "2");

        //pthread_create(&ptMusic_rae, NULL, musicfunction_rae, NULL);

        musicPlay_rae();

        delay(500);

        digitalWrite(LED_rae, LOW);         /* LED 끄기(Off) */

        break;                        // 한번 스위치 작동하면 끝냄

    }




 if(digitalRead(SW_me) == LOW) {     /* Push 버튼이 눌러지면(LOW) */

            digitalWrite(LED_me, HIGH);         /* LED 켜기(On) */

        sprintf(state,"%s\n", "3");

        //pthread_create(&ptMusic_me, NULL, musicfunction_me, NULL);

        musicPlay_me();

        delay(500);

        digitalWrite(LED_me, LOW);         /* LED 끄기(Off) */

        break;                        // 한번 스위치 작동하면 끝냄

    }




 if(digitalRead(SW_pa) == LOW) {     /* Push 버튼이 눌러지면(LOW) */

            digitalWrite(LED_pa, HIGH);         /* LED 켜기(On) */

        sprintf(state,"%s\n", "4");

        //pthread_create(&ptMusic_pa, NULL, musicfunction_pa, NULL);

        musicPlay_pa();

        delay(500);

        digitalWrite(LED_pa, LOW);         /* LED 끄기(Off) */

        break;                        // 한번 스위치 작동하면 끝냄

    }




 if(digitalRead(SW_sol) == LOW) {     /* Push 버튼이 눌러지면(LOW) */

            digitalWrite(LED_sol, HIGH);         /* LED 켜기(On) */

        sprintf(state,"%s\n", "5");

        //pthread_create(&ptMusic_sol, NULL, musicfunction_sol, NULL);

        musicPlay_sol();

        delay(500);

        digitalWrite(LED_sol, LOW);         /* LED 끄기(Off) */

        break;                        // 한번 스위치 작동하면 끝냄

    }




 if(digitalRead(SW_ra) == LOW) {     /* Push 버튼이 눌러지면(LOW) */

            digitalWrite(LED_ra, HIGH);         /* LED 켜기(On) */

        sprintf(state,"%s\n", "6");

        //pthread_create(&ptMusic_ra, NULL, musicfunction_ra, NULL);

        musicPlay_ra();

        delay(500);

        digitalWrite(LED_ra, LOW);         /* LED 끄기(Off) */

        break;                        // 한번 스위치 작동하면 끝냄

    }




 if(digitalRead(SW_ti) == LOW) {     /* Push 버튼이 눌러지면(LOW) */

            digitalWrite(LED_ti, HIGH);         /* LED 켜기(On) */

        sprintf(state,"%s\n", "7");

       //pthread_create(&ptMusic_ti, NULL, musicfunction_ti, NULL);

        musicPlay_ti();

        delay(500);

        digitalWrite(LED_ti, LOW);         /* LED 끄기(Off) */

        break;                        // 한번 스위치 작동하면 끝냄

    }




 if(digitalRead(SW_Do) == LOW) {     /* Push 버튼이 눌러지면(LOW) */

            digitalWrite(LED_Do, HIGH);         /* LED 켜기(On) */

        sprintf(state,"%s\n", "8");

        //pthread_create(&ptMusic_Do, NULL, musicfunction_Do, NULL);

        musicPlay_Do();

        delay(500);

        digitalWrite(LED_Do, LOW);         /* LED 끄기(Off) */

        break;                        // 한번 스위치 작동하면 끝냄

    }

    };




    return 0;

} 










int musicPlay_do()

{

    int i ;

    if(pthread_mutex_trylock(&music_lock) != EBUSY) { /* 임계 구역 설정 */

        softToneCreate(SPKR) ;             /* 톤 출력을 위한 GPIO 설정 */

            //for (i = 0; i < 1; ++i) {

                softToneWrite(SPKR, 261.63);         /* 톤 출력 : 학교종 연주 */

                delay(300);                 /* 음의 전체 길이만큼 출력되도록 대기 */

            //}

    softToneWrite(SPKR, 0);

    pthread_mutex_unlock(&music_lock); /* 임계 구역 해제 */

        }

    return 0;

}










int musicPlay_rae()

{

    int i ;

    if(pthread_mutex_trylock(&music_lock) != EBUSY) { /* 임계 구역 설정 */

        softToneCreate(SPKR) ;             /* 톤 출력을 위한 GPIO 설정 */

            //for (i = 0; i < 1; ++i) {

                softToneWrite(SPKR, 293.66);         /* 톤 출력 : 학교종 연주 */

                delay(300);                 /* 음의 전체 길이만큼 출력되도록 대기 */

            //}

    softToneWrite(SPKR, 0);

        pthread_mutex_unlock(&music_lock); /* 임계 구역 해제 */

        }

    return 0;

}













int musicPlay_me()

{

    int i ;

    if(pthread_mutex_trylock(&music_lock) != EBUSY) { /* 임계 구역 설정 */

        softToneCreate(SPKR) ;             /* 톤 출력을 위한 GPIO 설정 */

            //for (i = 0; i < 1; ++i) {

                softToneWrite(SPKR, 329.63);         /* 톤 출력 : 학교종 연주 */

                delay(300);                 /* 음의 전체 길이만큼 출력되도록 대기 */

            //}

    softToneWrite(SPKR, 0);

        pthread_mutex_unlock(&music_lock); /* 임계 구역 해제 */

        }

    return 0;

}







int musicPlay_pa()

{

    int i ;

    if(pthread_mutex_trylock(&music_lock) != EBUSY) { /* 임계 구역 설정 */

        softToneCreate(SPKR) ;             /* 톤 출력을 위한 GPIO 설정 */

            //for (i = 0; i < 1; ++i) {

                softToneWrite(SPKR,  349.22);         /* 톤 출력 : 학교종 연주 */

                delay(300);                 /* 음의 전체 길이만큼 출력되도록 대기 */

            //}

    softToneWrite(SPKR, 0);

        pthread_mutex_unlock(&music_lock); /* 임계 구역 해제 */

        }

    return 0;

}













int musicPlay_sol()

{

    int i ;

    if(pthread_mutex_trylock(&music_lock) != EBUSY) { /* 임계 구역 설정 */

        softToneCreate(SPKR) ;             /* 톤 출력을 위한 GPIO 설정 */

            //for (i = 0; i < 1; ++i) {

                softToneWrite(SPKR,  391);         /* 톤 출력 : 학교종 연주 */

                delay(300);                 /* 음의 전체 길이만큼 출력되도록 대기 */

            //}

    softToneWrite(SPKR, 0);

        pthread_mutex_unlock(&music_lock); /* 임계 구역 해제 */

        }

    return 0;

}







int musicPlay_ra()

{

    int i ;

    if(pthread_mutex_trylock(&music_lock) != EBUSY) { /* 임계 구역 설정 */

        softToneCreate(SPKR) ;             /* 톤 출력을 위한 GPIO 설정 */

            //for (i = 0; i < 1; ++i) {

                softToneWrite(SPKR,  440);         /* 톤 출력 : 학교종 연주 */

                delay(300);                 /* 음의 전체 길이만큼 출력되도록 대기 */

            //}

    softToneWrite(SPKR, 0);

        pthread_mutex_unlock(&music_lock); /* 임계 구역 해제 */

        }

    return 0;

}













int musicPlay_ti()

{

    int i ;

    if(pthread_mutex_trylock(&music_lock) != EBUSY) { /* 임계 구역 설정 */

        softToneCreate(SPKR) ;             /* 톤 출력을 위한 GPIO 설정 */

            //for (i = 0; i < 1; ++i) {

                softToneWrite(SPKR,  493.88);         /* 톤 출력 : 학교종 연주 */

                delay(300);                 /* 음의 전체 길이만큼 출력되도록 대기 */

            //}

    softToneWrite(SPKR, 0);

        pthread_mutex_unlock(&music_lock); /* 임계 구역 해제 */

        }

    return 0;

}




int musicPlay_Do()

{

    int i ;

    if(pthread_mutex_trylock(&music_lock) != EBUSY) { /* 임계 구역 설정 */

        softToneCreate(SPKR) ;             /* 톤 출력을 위한 GPIO 설정 */

            //for (i = 0; i < 1; ++i) {

                softToneWrite(SPKR,  523.25);         /* 톤 출력 : 학교종 연주 */

                delay(300);                 /* 음의 전체 길이만큼 출력되도록 대기 */

            //}

    softToneWrite(SPKR, 0);

        pthread_mutex_unlock(&music_lock); /* 임계 구역 해제 */

        }

    return 0;

}




void *musicfunction(void *arg)

{

    if(pthread_mutex_trylock(&music_lock) != EBUSY) { /* 임계 구역 설정 */

        musicPlay();

        pthread_mutex_unlock(&music_lock); /* 임계 구역 해제 */

    }




    return NULL;

}




int musicPlay()

{

    int i ;

    softToneCreate(SPKR) ;             /* 톤 출력을 위한 GPIO 설정 */

    for (i = 0; i < TOTAL; ++i) {

        softToneWrite(SPKR, notes[i]);         /* 톤 출력 : 학교종 연주 */

      delay(300);                 /* 음의 전체 길이만큼 출력되도록 대기 */

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

    //밝아지면 끝

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

    struct termios oldt, newt;             /* 터미널에 대한 구조체 */

    int ch, oldf;




    tcgetattr(0, &oldt);             /* 현재 터미널에 설정된 정보를 가져온다. */

    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);         /* 정규 모드 입력과 에코를 해제한다. */

    tcsetattr(0, TCSANOW, &newt);         /* 새로 값으로 터미널을 설정한다. */

    oldf = fcntl(0, F_GETFL, 0);

    fcntl(0, F_SETFL, oldf | O_NONBLOCK);     /* 입력을 논블로킹 모드로 설정한다. */




    ch = getchar();




    tcsetattr(0, TCSANOW, &oldt);         /* 기존의 값으로 터미널의 속성을 바로 적용한다. */

    fcntl(0, F_SETFL, oldf);

    if(ch != EOF) {

        ungetc(ch, stdin);             /* 앞에서 읽은 위치로 이전으로 포인터를 돌려준다. */

        return 1;

    }




    return 0;

}




int main(int argc, char **argv) {

    int server_sockfd, client_sockfd;     // 소켓

    int choice;

    char buf[MAXBUF];

    char dummy[MAXBUF];

    struct sockaddr_in serveraddr, clientaddr;  // 서버와 클라이언트의 소켓 정보

    int client_len;                        // 클라이언트 소켓의 바이트 크기

    int chk_bind;                     // 연결 확인 변수

    int read_len;




    int i = 0;




    pthread_t ptSwitch, ptCds, ptMusic, ptLed, ptDisp;

    pthread_mutex_init(&music_lock, NULL); /* 뮤텍스 초기화 */

    pthread_mutex_init(&switch_lock, NULL); /* 뮤텍스 초기화 */

    pthread_mutex_init(&cds_lock, NULL); /* 뮤텍스 초기화 */

    wiringPiSetup();




    client_len = sizeof(clientaddr);




    /* 서버 socket() 생성  */

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(server_sockfd == -1) {

        perror("socket error : ");

        exit(0);

    }

    /* bind() */

    bzero(&serveraddr, sizeof(serveraddr));     // 해당 메모리 영역 초기화

    serveraddr.sin_family = AF_INET;

    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    serveraddr.sin_port = htons(PORT);        // 포트 번호 설정

    chk_bind = bind(server_sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));    //소켓번호와 구조체와 연결

    if(chk_bind > 0) {

        perror("bind error : ");

        exit(0);

    }




    /* listen() */

    if(listen(server_sockfd, 5)) {    //5는 MAX개수, 5개의 클라이언트

        perror("listen error : ");

    }




    /* 클라이언트 연결 대기 */

    /* accept() */

    client_sockfd = accept(server_sockfd, (struct sockaddr *)&clientaddr, &client_len);    //클라이언트 연결대기

    printf("New Client Connect: %s\n", inet_ntoa(clientaddr.sin_addr));    //클라인언트 연결되면 실행 : 서버쪽에 띄워짐

    sprintf(state,"%s\n", "0");

    while(1) {




           state[100]=0;

        //sprintf(swstate,"%s\n", "1");

        if(write(client_sockfd , state, MAXBUF) <= 0) {

            perror("write( )");

            return -1; 

        }

        

        memset(buf, 0x00, MAXBUF);

        read_len = read(client_sockfd, buf, MAXBUF);            //버퍼의 크기(80)만큼 만듬

        

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







    pthread_join(ptSwitch, NULL); /* 스레드 대기 */    

    pthread_join(ptMusic, NULL); /* 스레드 대기 */

    pthread_join(ptCds, NULL);




    pthread_mutex_destroy(&music_lock); /* 뮤텍스 삭제 */  

    pthread_mutex_destroy(&switch_lock); 

    pthread_mutex_destroy(&cds_lock); 

                    return 0;

}