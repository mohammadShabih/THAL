#define NUM_SUB_SYSTEMS 9

enum eLogLevel {
    NONE, INFO_ONLY, DBG, WRNG, ERR, CRTCL
};

enum eLogSubSystem {
    MOTOR_MCU, ELCTR_MGNT_MCU, OV7670_MCU, IR_MCU, ULTR_MCU, OV7670_PER, IR_PER,
    ULTR_PER, ENCDR_PER
};

struct {
    bool on;
    int outputLevel[NUM_SUB_SYSTEMS];
} sLogStruct;

void Log(enum eLogSubSystem sys, enum eLogLevel, char *msg);

void LogWithNum(enum eLogSubSystem sys, enum eLogLevel, char *msg, int num);

void LogSetOutputLevel(enum eLogSubSystem, enum eLogLevel level);

void LogGlobalOn();

void LogGlobalOff();

void setLogLevel(enum eLogSubSystem sys, enum eLogLevel) {

}
