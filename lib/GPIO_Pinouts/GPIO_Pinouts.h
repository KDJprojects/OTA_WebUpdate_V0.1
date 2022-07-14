#define RED_LED         25
#define GREEN_LED       26
#define BLUE_LED        27
#define I2C_SDA         22
#define I2C_SCL         21
#define AUX_ENABLE      13
#define BoardID_1       34
#define BoardID_2       35
#define BATTERY_ENABLE  12
#define V_BATT          36
#define GAS_SENSOR      32

void Define_Pins(void);
void Activate_AUX_Power(void);
void Deactivate_AUX_Power(void);