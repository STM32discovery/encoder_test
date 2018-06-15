# encoder_test


I failed to receive encoder data using STM32F4 Discovery board

Gurley Encoder is using SSI interface so I needed transceiver to read the value

I used the transceiver on the slug board but it showes me a weird value

I gave up and do something different from now.

(I can try different thing using new transceiver)

I uploaded encoder.h and encoder.c that fixed the function which can use HAL libraries
