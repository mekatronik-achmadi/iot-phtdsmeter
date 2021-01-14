#ifndef MUX_H
#define MUX_H

#define MUX_S0 BIT15 //MTDO_U //GPIO15
#define MUX_S1 BIT13 //MTCK_U //GPIO13
#define MUX_S2 BIT12 //MTDI_U //GPIO12
#define MUX_S3 BIT14 //MTMS_U //GPIO14

#define MUX_PIN_1(PIN_NUM) gpio_output_set(PIN_NUM, 0, PIN_NUM, 0)
#define MUX_PIN_0(PIN_NUM) gpio_output_set(0, PIN_NUM, PIN_NUM, 0)

void mux_init(void);
void mux_channel(uint8 channel);

#endif // MUX_H
