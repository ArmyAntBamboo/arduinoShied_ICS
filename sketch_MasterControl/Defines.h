/*
 * 定义了出液计量系统中球阀的位置点对应的管脚
 * in1进口总，in2进口去罐1，in3进口去罐2
 * out4出口总，out5罐1出口，out6罐2出口
 */
#define point_BallValve_In1 2
#define point_BallValve_In2 3
#define point_BallValve_In3 4
#define point_BallValve_Out4 5
#define point_BallValve_Out5 6
#define point_BallValve_Out6 7
/*
 * 定义了控制控制球阀继电器对应的管脚
 * 进口球阀控制Delay_in
 * 出口球阀控制Delay_out
 */
#define Delay_inFWD 8//Forward正转
#define Delay_outFWD 9
#define Delay_inREV 10//reversal反转
#define Delay_outREV 11
/*
 * 定义了称重传感器对应的管脚
 * 罐1的传感器Sensor1
 * 罐2的传感器Sensor2
 * 注意：购买的传感器必须通过变送器将信号转化为0-5V的电压
 */
#define Sensor1 A1
#define Sensor2 A2
#define sensorFS 50.0//full scale 满量程值，是个常数值，暂时定义为50kg
#define weightFull 45.0//满桶时的重量*******需要在实际中测试*******
#define weightEmpty 1.0//空桶时的重量*******需要在实际中测试*******
#define PerVolume 44//每桶液体的体积*******需要在实际中测试*******
/*
 * 
 */
#define PUL 27//输出脉冲
#define DIR 28//输出方向
#define ENA 29//输出使能
const unsigned int PluseCount=0;//需要步进电机执行的脉冲数
/* 接口定义
  CE(DS1302 pin5) -> Arduino D44
  IO(DS1302 pin6) -> Arduino D45
  SCLK(DS1302 pin7) -> Arduino D46
*/
uint8_t CE_PIN   = 44;
uint8_t IO_PIN   = 45;
uint8_t SCLK_PIN = 46;
/*
 * 触摸屏通讯中，定义的全局变量
 */
float targetpress=3.0;//目标套压
float presentpress=4.0;//当前套压
int targetflow=2500;//目标瞬流
int presentflow=2300;//当前瞬流
unsigned int totalflow=400000;//累计流量
int dailyflow=10000;//日产气量
int cycle=600;//采样周期
float stepRange=0.5;//调节幅度
int storage=30;//数据存储量
bool power=0;//供电模式
float instantLP=4.0;//瞬时产液量
float totalLP=4.0;//累计产液量
float previousLP=4.0;//前一日产液量
int bottleUsed=2;//目前正在进行排液计量的罐
int valvelift=40;//阀门开度
float DLPS=10;//日产液量
boolean models=0;//控制模式，0为定压模式，1为定流量模式
/*
 * 每个事件唤醒时间间隔定义，如触摸屏刷新，SD卡数据写入，阀门调整
 */
uint8_t TFT_Every = 10;  // 触摸屏刷新,10S
uint8_t SD_Every = 20; // SD卡数据写入,20分钟
uint8_t Stepper_Every = 20; // 步进电机执行间隔时间
/* 创建 DS1302 对象 */
DS1302 rtc(CE_PIN, IO_PIN, SCLK_PIN);
Time t_TFT= rtc.time();
Time t_SD= rtc.time(); 
Time t_Stepper= rtc.time();
