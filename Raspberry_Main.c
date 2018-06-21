//#ifdef RaspberryPi

#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<mysql/mysql.h>


//Wiring Pi
#include<wiringPi.h>
#include<wiringSerial.h>

char device[]="/dev/ttyACM0";//arduino port
char MacNumber[18]="";//mac address
int MacCount = 0;//mac adress size check
int fd;//serial connect flag
int ff;//

unsigned long baud = 115200;//serial transport speed
unsigned long time = 0;
char parkingcheck1[18] = "kkkkkkkkkkkkkk1";//slot1 check
char parkingcheck2[18] = "kkkkkkkkkkkkkk2";//slot2 check

MYSQL *conn_ptr;//db conn
MYSQL_RES *res_ptr;//db
MYSQL_ROW sqlrow;//db

int main(void);
void loop(void);
void setup(void);
int db_init();
int search(MYSQL *,char *);
void parking(MYSQL * , char *);
void parking_init(MYSQL *);

void setup(){
	printf("%s \n","Parking StartUp!");//init_print
	db_init();//db_init
	parking_init(conn_ptr);//parking db conn	
	fflush(stdout);

	if((fd = serialOpen(device, baud))<0){//serial open
		fprintf(stderr,"Unable to open serial device: %s\n",strerror(errno));
		exit(1);
	}
	if(wiringPiSetup()==-1){//serial open
		fprintf(stdout,"Unable to start wiringPi: %s\n",strerror(errno));
		exit(1);
	}
	memset(MacNumber,'\0',sizeof(MacNumber));//memory reset
}

void loop(){
	int count = 0;
	if(serialDataAvail(fd)){//serial available
		char newChar = serialGetchar(fd);//get data
		fflush(stdout);
		if(MacCount==17){//mac address length equal 17
			MacNumber[MacCount]='\0';
			if(!strncmp(MacNumber,parkingcheck1,15) && ff == 1)//parking slot1 check
			{
				parking(conn_ptr,MacNumber);//db change
			}
			else if(!strncmp(MacNumber,parkingcheck2,15) && ff == 1)//parking slot2 check
			{
				parking(conn_ptr,MacNumber);//db change
			}
			else{//mac address check
				count =	search(conn_ptr,MacNumber);//mac address db matching
				if(count != 0 )//found mac address
				{
					printf("find MacAddress\n");
					ff=1;//find db flag
					serialPutchar(fd,'1');//send to arduino 1
				}
				else{
					ff=0;//not fing db flag
					serialPutchar(fd,'0');//send to arduino 0
				}
				puts(MacNumber);//print mac address
			}//end strncmp else
			fflush(stdout);
			MacCount=0;//count reset
			memset(MacNumber,'\0',sizeof(MacNumber));//memory reset
		} // end MacCount == 17
		if(MacCount<17){//make mac address or slot string
			MacNumber[MacCount++]=newChar;
		}
	}//serialDataAvail() end
} // loop end

int db_init(){//db connect
	conn_ptr=mysql_init(NULL);
	
	conn_ptr=mysql_real_connect(conn_ptr,"localhost","root","kkkk","KKKK",0,NULL,0);
	if(!conn_ptr){
		printf("error\n");
		return 0;
	}
	if(conn_ptr){
		printf("success\n");
		return 1;
	}
}

int main(){//main
	setup();
	while(1){
		loop();
	}
	return 0;
}

int search(MYSQL *con,char *MacAddress )//db search
{
	char temp[255];	
	MYSQL_RES *sql_result;
	MYSQL_ROW row;

	int count = 0;
	int field;
	sprintf(temp,"select MACADDR from MACADDR where MACADDR = '%s';",MacAddress);

	mysql_query(con,temp);

	sql_result = mysql_store_result(con);
	field = mysql_num_fields(sql_result);

	while((row = mysql_fetch_row(sql_result))){
		count++;
	}
	if(count == 0)
	{
		return 0;
	}	
	return count;
}

void parking(MYSQL *con, char *MacAddress )//update parking db
{
	int j;
	char temp[255];
	char parkingNumber;
	char parkingDo;
	parkingNumber = MacAddress[15];
	parkingDo = MacAddress[16];		
	sprintf(temp,"update PARKING set DO = '%c' where PARKINGPLACE = '%c'",parkingDo,parkingNumber);  
	mysql_query(con,temp);
	printf("PARKINGPLACE%c = %c\n",parkingNumber,parkingDo);
}

void parking_init(MYSQL *con)//parking db init
{
	char temp[255];
	int j ;
	for(j = 0 ; j < 2 ; j++)
	{
		sprintf(temp,"update PARKING set DO = '%d' where PARKINGPLACE = '%d'",0,j+1);//first time set db 0
	}
	mysql_query(con,temp);
	printf("PARKING_INIT\n");
	delay(50);
}
