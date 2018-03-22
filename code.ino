#include <SoftwareSerial.h>
#include <string.h>
SoftwareSerial mySerial(9, 10);
const int trigPin1 = 2;
const int echoPin1 = 4;
const int trigPin2 = 3;
const int echoPin2 = 5;
int ledr1=13,ledy1=12,ledg1=11,ledr2=7,ledy2=6,ledg2=8;
int IN=99,N=9;
void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
    pinMode(ledr1,OUTPUT);
    pinMode(ledy1,OUTPUT);
    pinMode(ledg1,OUTPUT);
    pinMode(ledr2,OUTPUT);
    pinMode(ledy2,OUTPUT);
    pinMode(ledg2,OUTPUT);
    delay(100);
}
void dijsktra(int cost[9][9],int source,int target)
{
    int dist[N],prev[N],selected[N]={0},i,m,min1,start,d,j,a,target1,x=0;
    char path[N],path1[50],path2[50];
    target1=target;
    for(i=1;i< N;i++)
    {
        dist[i] = IN;
        prev[i] = -1;
    }
    start = source;
    selected[start]=1;
    dist[start] = 0;
    while(selected[target] ==0)
    {
        min1 = IN;
        m = 0;
        for(i=1;i< N;i++)
        {
            d = dist[start] +cost[start][i];
            if(d< dist[i]&&selected[i]==0)
            {
                dist[i] = d;
                prev[i] = start;
            }
            if(min1>dist[i] && selected[i]==0)
            {
                min1 = dist[i];
                m = i;
            }
        }
        start = m;
        selected[start] = 1;
    }
    start = target;
    j = 0;
    while(start != -1)
    {
        path[j++] = start+64;
        start = prev[start];
    }
    path[j]='\0';
    strrev(path);
    printf("\n");
    strcpy(path1,"main-gate");
    for(i=1;i<strlen(path);i++)
    {
        /*if (path[i]=='A')
            Serial.print(" main gate");*/
        if(path[i]=='B')
            strcat(path1,"--->MB");
        else if(path[i]=='C')
            strcat(path1,"--->SMV");
        else if(path[i]=='D')
            strcat(path1,"--->TT");
        else if(path[i]=='E')
            strcat(path1,"--->FOODIES");
        else if(path[i]=='F')
            strcat(path1,"--->E-BLOCK");
        else if(path[i]=='G')
            strcat(path1,"--->H-BLOCK");
        else if(path[i]=='H')
            strcat(path1,"--->A-BLOCK");
    }
    Serial.print(path1);
    if(target1>1 && x<2)
    {
      SendMessage(path1);
      x=x+1;
    }
    
}


void loop()
{
     
  int target=1,x1=0;
  long duration1, cm1;
  pinMode(trigPin1, OUTPUT);
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  pinMode(echoPin1, INPUT);
  duration1 = pulseIn(echoPin1, HIGH);

  cm1 = microsecondsToCentimeters(duration1);
  long duration2, cm2;
  pinMode(trigPin2, OUTPUT);
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  pinMode(echoPin2, INPUT);
  duration2 = pulseIn(echoPin2, HIGH);

  cm2 = microsecondsToCentimeters(duration2);
  

  
  delay(100);
  Serial.println("");
  if(cm1>15)
  {
    digitalWrite(ledr1,LOW);
    digitalWrite(ledy1,LOW);
    digitalWrite(ledg1,HIGH);
  }
  
  else if(cm1>5 && cm1<15)
  {
    digitalWrite(ledr1,LOW);
    digitalWrite(ledg1,LOW);
    digitalWrite(ledy1,HIGH);
  }
  else
  {
    digitalWrite(ledy1,LOW);
    digitalWrite(ledg1,LOW);
    digitalWrite(ledr1,HIGH);
    target=8;
    
  }
  
  if(cm2>15)
  {
    digitalWrite(ledr2,LOW);
    digitalWrite(ledy2,LOW);
    digitalWrite(ledg2,HIGH);
  }
  else if(cm2>5 && cm2<15)
  {
    digitalWrite(ledr2,LOW);
    digitalWrite(ledg2,LOW);
    digitalWrite(ledy2,HIGH);
  }
  else
  {
    digitalWrite(ledy2,LOW);
    digitalWrite(ledg2,LOW);
    digitalWrite(ledr2,HIGH);
    target=6; // plastic container
  }

  int cost[9][9],i,j,w,ch,co;
    int source=1,x,y;
    for(i=1;i< N;i++)
        {for(j=1;j< N;j++)
            {cost[i][j] = IN;}}

    cost[1][2]=cost[2][1]=1;
    cost[1][5]=cost[5][1]=4;
    cost[2][3]=cost[3][2]=3;
    cost[2][8]=cost[8][2]=3;
    cost[3][4]=cost[4][3]=3;
    cost[3][5]=cost[5][3]=1;
    cost[3][7]=cost[7][3]=3;
    cost[4][5]=cost[5][4]=1;
    cost[4][6]=cost[6][4]=2;
    cost[6][7]=cost[7][6]=4;
    cost[7][8]=cost[8][7]=2;

    dijsktra(cost,source,target);

  
}


long microsecondsToCentimeters(long microseconds)
{
 
  return microseconds/29/2;
}

 void SendMessage(char path[50])
{
  mySerial.println("AT+CMGF=1");    
  delay(1000);  
  mySerial.println("AT+CMGS=\"+919555251370\"\r"); 
  delay(1000);
  mySerial.println(path);
  delay(100);
   mySerial.println((char)26);
  delay(1000);
}
