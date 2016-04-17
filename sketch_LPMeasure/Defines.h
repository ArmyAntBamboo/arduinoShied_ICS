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
