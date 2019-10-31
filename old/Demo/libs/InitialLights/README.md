# Controller Communication Protocol

## Version 1: Original Controller

* Light Controller
  * 4 x PWM channels
  * 2 x 0-10V analog channels
  * 1 x PWM + 1 x RGB channels
  * (?) 1 x RGBW channel

| Request | Command | Notes / Responses
|---|---|---
| get state | `U?` | `*3230300002` - 2 x 0-10V Analogic
|  |  | `*FFFF000002` - max analogic channel state
|  |  | `*2020202003` - 4 x PWM
|  |  | `*191A1B1C01` - 1 x PWM + 1 x RGB
| set state | `US191A1B1C03` | set 4 x PWM Channels
|  | `US1F1F000003` | set 2 x 0-10V Analog Channels
| save scene | `UT0` ... `UT6`
| read scene | `UV0` ... `UV6` | `*....`
| invoke scene | `UI0` ... `UI6` | `*....`
| blink channel 0...3 | `UB0` ... `UB3` | blink times 1-9 ?

* All numbers values are encoded as hex strings
* 1 value byte -> 2 hex chars


## Version 2: TI Based Controller

* Light Controller
* 4 x PWM channels
* 2 x 0-10V analog channels
* 1 x PWM + 1 x RGB channels
* 1 x RGBW channel
* 1 X CW + 1 x WW channels

Protocol TBD
