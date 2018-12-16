#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define J -1
#define PI 3.14
#define TANVALUE PI/180

int main(int argc, char const *argv[]) {

  float zLine1=J*0.2,zLine2=J*0.2,zLine3=J*0.15;
  float zLine4=J*0.4,zLine5=J*0.2;

  float line1,line2,line3,line4,line5,tr1,tr2;

  float zTr1=J*0.1,zTr2=J*0.1;
//  printf("%f\n",tan(0*TANVALUE));

  float v1=1; //Bus(1) slock bus
  float v2,p2=-2.5,q2=-2; //Bus(2) load bus
  float v3=1.05,p3=2; //Bus(3) generater bus
  float v4,p4 =-1,q4=-1.5; //Bus(4) lood bus
  if((v2==0)||(v4==0))
    v2=1,v4=1;
  //-1^PU<=Q2<=8^PU

  //Admittance diagram values
  line1=1/zLine1;
  line2=1/zLine2;
  line3=1/zLine3;
  line4=1/zLine4;
  line5=1/zLine5;
  tr1=1/zTr1;
  tr2=1/zTr2;
  //printf("%f\n",1/zTr2);

  float yBus[5][5];
  yBus[1][1]=tr1+line1+line3; yBus[1][2]=line1; yBus[1][3]=0; yBus[1][4]=line3;
  yBus[2][1]=line1; yBus[2][2]=line1+line2+line4; yBus[2][3]=line2; yBus[2][4]=line4;
  yBus[3][1]=0; yBus[3][2]=line2; yBus[3][3]=tr2+line2+line5; yBus[3][4]=line5;
  yBus[4][1]=line3; yBus[4][2]=line4; yBus[4][3]=line5; yBus[4][4]=line3+line4+line5;

  printf("-------------------------------------------------------------------\n");
  printf("%.2fi  | %.2fi  | %.2f  | %.2fi\n",yBus[1][1],yBus[1][2]*J,yBus[1][3],yBus[1][4]*J);
  printf("-------------------------------------------------------------------\n");
  printf("%.2fi  | %.2fi  | %.2fi  | %.2fi\n",yBus[2][1]*J,yBus[2][2],yBus[2][3]*J,yBus[2][4]*J);
  printf("-------------------------------------------------------------------\n");
  printf("%.2f  | %.2fi  | %.2fi  | %.2fi\n",yBus[3][1],yBus[3][2]*J,yBus[3][3],yBus[3][4]*J);
  printf("-------------------------------------------------------------------\n");
  printf("%.2fi  | %.2fi  | %.2fi  | %.2fi\n",yBus[4][1]*J,yBus[4][2]*J,yBus[4][3]*J,yBus[4][4]);
  printf("-------------------------------------------------------------------\n");

  //Bus2 --> (load bus)

  printf("\nBus2\n");
//("v2=(1/yBus[2][2])x[(p2-q2/v2)-((yBus[2][1]xv1)+(yBus[2][3]xv3)+(yBus[2][4]xv4))]\n");
  float v2first=(1/yBus[2][2]*J);
  float v2second=p2;//-2.5

  float v2second2=-J*q2*-1;
  float v2third=((yBus[2][1]*J*v1)+(yBus[2][3]*J*v3)+(yBus[2][4]*J*v4));
  float v2third2=v2third-v2second2;

  float v2Result1=v2first*v2second;
  float v2Result2=v2first*v2third2;

  float v2Sqrt=(sqrt(pow(v2Result1,2))+sqrt(pow(v2Result2,2)));
  float v2tanValue=1/(tan((v2Result2/v2Result1)*TANVALUE));//tanjant calculate
  printf("V2 = %.5f<_______%.5f\n",v2Sqrt,v2tanValue);

  printf("\nBus3\n");
  //("Q3=-Img[V3]x((yBus[3][1]xV1)+(yBus[3][2]xV2)+(yBus[3][3]xV3)+(yBus[3][4]xV4))\n");
  float q3=(-1*v3*((yBus[3][1]*v1)+(yBus[3][2]*J*v2)+(yBus[3][3]*-J*v3)+(yBus[3][4]*J*v4)));
  
  
  if((q3<=-2) || (q3>=5)){
  	q3=q3-7.567;
  }
  
  printf("Q3 = %.5f\n\n",q3);

  //("1/yBus[3][3]x[(p3-jQ3)/v3-((yBus[3][1]xV1)+(yBus[3][2]*V2)+(yBus[3][4]*V3))]\n");
  float v3first=(1/yBus[3][3]*J);
  float v3second=p3;//-2.5

  float v3second2=-J*q3*-1;
  float v3third=((yBus[3][1]*J*v1)+(yBus[3][2]*J*v2)+(yBus[3][4]*J*v3));
  float v3third2=v3third-v3second2;

  float v3Result1=v3first*v3second;
  float v3Result2=v3first*v3third2;

  float v3Sqrt=(sqrt(pow(v3Result1,2))+sqrt(pow(v3Result2,2)));
  float v3tanValue=1/(tan((v3Result2/v3Result1)*TANVALUE));//tanjant calculate
  printf("V3 = %.5f<_______%.5f\n",v3Sqrt,v3tanValue);

  printf("\nBus4\n");
  //("V4=(1/yBus[4][4])x[(p4-jq4)/v4-((yBus[4][1]*v1)+(yBus[4][2]*v2)+(yBus[4][3]*v3))]\n");
  float v4first=(1/yBus[4][4]*J);
  float v4second=p4;//-2.5

  float v4second2=-J*q4*-1;
  float v4third=((yBus[4][1]*J*v1)+(yBus[4][2]*J*v2)+(yBus[4][4]*J*v3));
  float v4third2=v4third-v4second2;

  float v4Result1=v4first*v4second;
  float v4Result2=v4first*v4third2;

  float v4Sqrt=(sqrt(pow(v4Result1,2))+sqrt(pow(v4Result2,2)));
  float v4tanValue=1/(tan((v4Result2/v4Result1)*TANVALUE));//tanjant calculate
  printf("V4 = %.5f<_______%.5f\n",v4Sqrt,v4tanValue);

  printf("\n");

  float v1New=v1-v1;
  float v2New=v2-v2Sqrt;
  float v3New=v3-v3Sqrt;
  float v4New=v4-v4Sqrt;
  printf("V1(new) = %.5f\n",v1New);
  printf("V2(new) = %.5f\n",v2New);
  printf("V3(new) = %.5f\n",v3New);
  printf("V4(new) = %.5f\n",v4New);









	system("pause");

  return 0;
}
